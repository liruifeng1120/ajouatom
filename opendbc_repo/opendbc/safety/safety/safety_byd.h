#pragma once

#include "safety_declarations.h"

// 需要处理的CAN消息定义
#define BYD_CANADDR_IPB               0x1F0
#define BYD_CANADDR_ACC_MPC_STATE     0x316
#define BYD_CANADDR_ACC_MPC_STATE_SEAL     0x1E2
#define BYD_CANADDR_ACC_EPS_STATE     0x318
#define BYD_CANADDR_ACC_EPS_STATE_SEAL     0x1FC
#define BYD_CANADDR_ACC_HUD_ADAS      0x32D
#define BYD_CANADDR_ACC_CMD           0x32E
#define BYD_CANADDR_ACC_AEB           0x32F
#define BYD_CANADDR_PCM_BUTTONS       0x3B0
#define BYD_CANADDR_DRIVE_STATE       0x242
#define BYD_CANADDR_PEDAL             0x342
#define BYD_CANADDR_EPS               0x11F
#define BYD_CANADDR_CARSPEED          0x121

// CAN总线编号定义
#define BYD_CANBUS_ESC  0               // ESC总线
#define BYD_CANBUS_MRR  1               // 雷达总线
#define BYD_CANBUS_MPC  2               // MPC总线

static bool byd_eps_cruiseactivated = false;

typedef enum {
  HAN_TANG_DMEV,
  TANG_DMI,
  SONG_PLUS_DMI,
  QIN_PLUS_DMI,
  YUAN_PLUS_DMI_ATTO3,
  SEAL
} BydPlatform;
static BydPlatform byd_platform;


// 接收CAN消息的钩子函数
static void byd_rx_hook(const CANPacket_t *to_push) {
  int bus = GET_BUS(to_push);
  int addr = GET_ADDR(to_push);

  if (bus == BYD_CANBUS_ESC) {
    if (addr == BYD_CANADDR_PEDAL) {
      gas_pressed = (GET_BYTE(to_push, 0) != 0U);
      brake_pressed = (GET_BYTE(to_push, 1) != 0U);
    } else if (addr == BYD_CANADDR_CARSPEED) {
      int speed_raw = ((GET_BYTE(to_push, 1) & 0x0FU) << 8) | GET_BYTE(to_push, 0);
      vehicle_moving = (speed_raw != 0);
    } else if (addr == BYD_CANADDR_ACC_EPS_STATE) {
      byd_eps_cruiseactivated = (GET_BYTE(to_push, 0) & 0x3U) == 2U; // CruiseActivated

      int angle_meas_new = (GET_BYTE(to_push, 3) << 8) | GET_BYTE(to_push, 2);
      angle_meas_new = to_signed(angle_meas_new, 16) * 10;
      update_sample(&angle_meas, angle_meas_new);

    } else if (addr == BYD_CANADDR_ACC_EPS_STATE_SEAL) {
      byd_eps_cruiseactivated = (GET_BYTE(to_push, 0) & 0x3U) == 2U; // CruiseActivated
      int torque_motor = ((GET_BYTE(to_push, 5) & 0x0FU) << 8) | GET_BYTE(to_push, 4); // MainTorque
      torque_motor = to_signed(torque_motor, 12);
      update_sample(&torque_meas, torque_motor);
    }
    else {
      //empty
    }

    generic_rx_checks(addr == BYD_CANADDR_ACC_MPC_STATE);

  } else if (bus == BYD_CANBUS_MPC) {
    if (addr == BYD_CANADDR_ACC_HUD_ADAS) {
      if(byd_platform == SEAL) {
        bool cruise_engaged = GET_BIT(to_push, 22); //AccOn1
        pcm_cruise_check(cruise_engaged);
      } else {
        unsigned int accstate = ((GET_BYTE(to_push, 2) >> 3) & 0x07U);
        bool cruise_engaged = (accstate == 0x3U) || (accstate == 0x5U); // 3=acc_active, 5=user force accel
        pcm_cruise_check(cruise_engaged);
      }
    }

  }else{
    //do nothing.
  }
}


static bool byd_tx_hook(const CANPacket_t *to_send) {
  // 转向限制配置
  const TorqueSteeringLimits BYD_HANDM_STEERING_LIMITS = {
    .max_steer = 300,                     // 最大转向值
    .max_rate_up = 18,                    // 最大上升率
    .max_rate_down = 18,                  // 最大下降率
    .max_rt_delta = 243,                  // 最大实时变化 = 18 * 250/20 = 225 + 18 =
    .max_rt_interval = 250000,            // 最大实时间隔 = 250ms
    .max_torque_error = 80,               // motor torque limits
    .type = TorqueMotorLimited,           // 限制类型
  };

  const AngleSteeringLimits BYD_SEAL_STEERING_LIMITS = {
    .angle_deg_to_can = 100,
    .angle_rate_up_lookup = {
      {0., 5., 15.},
      {5., .8, .15}
    },
    .angle_rate_down_lookup = {
      {0., 5., 15.},
      {5., 3.5, .4}
    },
  };

  bool tx = true;

  if (GET_BUS(to_send) == BYD_CANBUS_ESC) {
    int addr = GET_ADDR(to_send);

    if(byd_platform == SEAL) {
      if (addr == BYD_CANADDR_ACC_MPC_STATE_SEAL) {
        int desired_angle = ((GET_BYTE(to_send, 3) & 0x07U) << 8U) | GET_BYTE(to_send, 2);
        desired_angle = to_signed(desired_angle, 11);
        bool steer_req = GET_BIT(to_send, 28U) || byd_eps_cruiseactivated; //LKAS_Active

        if (steer_angle_cmd_checks(desired_angle, steer_req, BYD_SEAL_STEERING_LIMITS)) {
          tx = true;
        }
      }

    } else {
      if (addr == BYD_CANADDR_ACC_MPC_STATE) {
        int desired_torque = ((GET_BYTE(to_send, 3) & 0x07U) << 8U) | GET_BYTE(to_send, 2);
        desired_torque = to_signed(desired_torque, 11);
        bool steer_req = GET_BIT(to_send, 28U) || byd_eps_cruiseactivated; //LKAS_Active

        const TorqueSteeringLimits limits = BYD_HANDM_STEERING_LIMITS;
        if (steer_torque_cmd_checks(desired_torque, steer_req, limits)) {
          tx = true; //false; disable this
        }
      }
    }

  }

  return tx;
}

static int byd_fwd_hook(int bus, int addr) {
  int bus_fwd = -1; // 初始化转发总线为-1

  if (bus == BYD_CANBUS_ESC) { // if sent from esc
    bool block_esc_msg = (addr == BYD_CANADDR_ACC_EPS_STATE)
                      || (addr == BYD_CANADDR_ACC_EPS_STATE_SEAL);

    if (!block_esc_msg) {
      bus_fwd = BYD_CANBUS_MPC;
    }
  } else if (bus == BYD_CANBUS_MPC) { // if sent from mpc
    bool block_mpc_msg = (addr == BYD_CANADDR_ACC_MPC_STATE)
                      || (addr == BYD_CANADDR_ACC_MPC_STATE_SEAL)
                      || (addr == BYD_CANADDR_ACC_CMD);

    if (!block_mpc_msg) {
      bus_fwd = BYD_CANBUS_ESC;
    }
  }

  return bus_fwd;
}


static safety_config byd_init(uint16_t param) {
  // const uint32_t FLAG_TANG_DMI = 0x2U;
  // const uint32_t FLAG_SONG_PLUS_DMI = 0x4U;
  // const uint32_t FLAG_QIN_PLUS_DMI = 0x8U;
  // const uint32_t FLAG_YUAN_PLUS_DMI_ATTO3 = 0x10U;
  const uint32_t FLAG_SEAL = 0x20U;

  safety_config ret;

  static RxCheck byd_handm_rx_checks[] = {
    {.msg = {{BYD_CANADDR_PEDAL,          BYD_CANBUS_ESC, 8, .ignore_checksum = true, .ignore_counter = true, .frequency = 50U}, { 0 }, { 0 }}},
    {.msg = {{BYD_CANADDR_CARSPEED,       BYD_CANBUS_ESC, 8, .ignore_checksum = true, .ignore_counter = true, .frequency = 50U}, { 0 }, { 0 }}},
    {.msg = {{BYD_CANADDR_ACC_EPS_STATE,  BYD_CANBUS_ESC, 8, .ignore_checksum = true, .ignore_counter = true, .frequency = 50U}, { 0 }, { 0 }}},
    {.msg = {{BYD_CANADDR_ACC_HUD_ADAS,   BYD_CANBUS_MPC, 8, .ignore_checksum = true, .ignore_counter = true, .frequency = 50U}, { 0 }, { 0 }}},
    {.msg = {{BYD_CANADDR_ACC_MPC_STATE,  BYD_CANBUS_MPC, 8, .ignore_checksum = true, .ignore_counter = true, .frequency = 50U}, { 0 }, { 0 }}},
  };

  static RxCheck byd_seal_rx_checks[] = {
    {.msg = {{BYD_CANADDR_PEDAL,              BYD_CANBUS_ESC, 8, .ignore_checksum = true, .ignore_counter = true, .frequency = 50U}, { 0 }, { 0 }}},
    {.msg = {{BYD_CANADDR_CARSPEED,           BYD_CANBUS_ESC, 8, .ignore_checksum = true, .ignore_counter = true, .frequency = 50U}, { 0 }, { 0 }}},
    {.msg = {{BYD_CANADDR_ACC_EPS_STATE_SEAL, BYD_CANBUS_ESC, 8, .ignore_checksum = true, .ignore_counter = true, .frequency = 50U}, { 0 }, { 0 }}},
    {.msg = {{BYD_CANADDR_ACC_HUD_ADAS,       BYD_CANBUS_MPC, 8, .ignore_checksum = true, .ignore_counter = true, .frequency = 50U}, { 0 }, { 0 }}},
    {.msg = {{BYD_CANADDR_ACC_MPC_STATE,      BYD_CANBUS_MPC, 8, .ignore_checksum = true, .ignore_counter = true, .frequency = 50U}, { 0 }, { 0 }}},
    {.msg = {{BYD_CANADDR_ACC_MPC_STATE_SEAL, BYD_CANBUS_MPC, 8, .ignore_checksum = true, .ignore_counter = true, .frequency = 50U}, { 0 }, { 0 }}},
  };

  static const CanMsg BYD_HANDM_TX_MSGS[] = {
    {BYD_CANADDR_ACC_CMD,         BYD_CANBUS_ESC, 8},
    {BYD_CANADDR_ACC_MPC_STATE,   BYD_CANBUS_ESC, 8},
    {BYD_CANADDR_ACC_EPS_STATE,   BYD_CANBUS_MPC, 8},
  };

  static const CanMsg BYD_SEAL_TX_MSGS[] = {
    {BYD_CANADDR_ACC_CMD,            BYD_CANBUS_ESC, 8},
    {BYD_CANADDR_ACC_MPC_STATE,      BYD_CANBUS_ESC, 8},
    {BYD_CANADDR_ACC_MPC_STATE_SEAL, BYD_CANBUS_ESC, 8},
    {BYD_CANADDR_ACC_EPS_STATE_SEAL, BYD_CANBUS_MPC, 8},
  };

  // bool use_han_dm = GET_FLAG(param, FLAG_HAN_TANG_DMEV); this is default option
  // bool use_tang_dmi = GET_FLAG(param, FLAG_TANG_DMI);
  // bool use_song = GET_FLAG(param, FLAG_SONG_PLUS_DMI);
  // bool use_qin = GET_FLAG(param, FLAG_QIN_PLUS_DMI);
  bool use_seal = GET_FLAG(param, FLAG_SEAL);

  if (use_seal) {
    byd_platform = SEAL;
    ret = BUILD_SAFETY_CFG(byd_seal_rx_checks, BYD_SEAL_TX_MSGS);
  } else {
    byd_platform = HAN_TANG_DMEV;
    ret = BUILD_SAFETY_CFG(byd_handm_rx_checks, BYD_HANDM_TX_MSGS);
  }

  return ret;
}

const safety_hooks byd_hooks = {
  .init = byd_init,
  .rx = byd_rx_hook,
  .tx = byd_tx_hook,
  .fwd = byd_fwd_hook,
};