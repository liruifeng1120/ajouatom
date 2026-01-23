
#!/usr/bin/env python3
import time
import os
from collections import deque
from typing import Dict, Optional, Tuple

import numpy as np

from opendbc.car.interfaces import RadarInterfaceBase
from opendbc.car import Bus, structs
from opendbc.can.parser import CANParser
from opendbc.car.byd.values import DBC, CanBus

# -------------------------
#  简易输出一阶低通滤波器（用于 vRel 输出平滑，不反哺 KF）
# -------------------------
class LowPassFilter:
    def __init__(self, x0: float = 0.0):
        self.x = float(x0)

    def update(self, value: float, dt: float, tau: float):
        if dt <= 0:
            return self.x
        alpha = dt / (tau + dt)
        self.x = (1.0 - alpha) * self.x + alpha * float(value)
        return self.x

# --------------------------------------------------------------
#  简单的一维卡尔曼滤波（distance + relative speed）
#  支持可选的伪速度观测 v_meas，用马氏距离门控
# --------------------------------------------------------------
class SimpleKalmanFilter:
    """
    状态向量   x = [d, v_rel]^T
    观测模型   支持:
      - 仅距离观测 z = d + noise
      - 距离+速度观测 z = [d, v_rel]^T + noise
    过程噪声   加速度噪声 σ_a
    观测噪声   R (distance variance), Rv (velocity variance) 可选
    """

    def __init__(
        self,
        initial_d: float,
        initial_time: float,
        sigma_a: float = 0.15,
        R: float = 0.5,
        distance_scale: float = 1.0,
        distance_offset: float = 0.0,
    ):
        # calibration params (frozen; avoid aggressive online adaptation)
        self.distance_scale = distance_scale
        self.distance_offset = distance_offset

        # 状态
        self.d = float(initial_d)
        self.v_rel = 0.0
        self.last_v_rel = 0.0  # 用于加速度限幅

        # 初始协方差：让速度有较大不确定性
        self.P = np.array([[2.0, 0.0],
                           [0.0, 5.0]])

        # 噪声
        self.sigma_a = sigma_a
        self.R = float(R)  # distance variance

        # 计时
        self.last_time = float(initial_time)

        # 统计 / 健康检查
        self.invalid_count = 0
        self.measurement_history = deque(maxlen=5)

        # 最小/最大协方差下界（数值稳定）
        self._min_P = 1e-6

    # -------------------------
    # 辅助：预测步骤（匀速模型）
    # -------------------------
    def predict(self, dt: float) -> None:
        if dt <= 0:
            return

        # 状态预测
        self.d += self.v_rel * dt

        # 过程噪声 Q（标准离散化：右下为 dt**2）
        q = self.sigma_a ** 2
        Q = np.array([[dt ** 4 / 4.0, dt ** 3 / 2.0],
                      [dt ** 3 / 2.0, dt ** 2       ]]) * q

        F = np.array([[1.0, dt],
                      [0.0, 1.0]])
        self.P = F @ self.P @ F.T + Q
        # 数值下界
        self.P = np.maximum(self.P, self._min_P)

    # -------------------------
    # 更新步骤：支持可选速度观测 v_meas 与门控
    # -------------------------
    def update(self, d_meas: float, v_meas: Optional[float] = None, Rv: float = 1.0) -> Tuple[bool, float]:
        """
        返回 (was_updated, md2) 表示是否做了更新以及用于门控的马氏距离平方
        如果 v_meas is None -> 做 1D 更新（仅距离）
        否则做 2D 更新（距离+速度）并使用马氏门控（2 DOF）
        """
        # 基本合法性
        if not (0.5 <= d_meas <= 200.0):
            return False, float('inf')

        # 经验标定（静态）
        z_d = d_meas * self.distance_scale + self.distance_offset

        # 预测后的状态与 P 应在外部 predict() 已更新

        x_pred = np.array([self.d, self.v_rel])
        # 1D distance only
        if v_meas is None:
            H = np.array([[1.0, 0.0]])
            S = H @ self.P @ H.T + self.R  # scalar
            y = np.array([z_d - (H @ x_pred)[0]])
            # 马氏距离 1D: y^2 / S
            md2 = float((y[0] ** 2) / S)
            # 1 DOF chi2 thresholds: 25.0 ~ 99%
            if md2 > 25.0:
                self.last_md2 = md2
                return False, md2
            # 卡尔曼增益
            K = (self.P @ H.T) / S  # (2,1)
            state = x_pred + (K.flatten() * y[0])
            self.d, self.v_rel = float(state[0]), float(state[1])
            # Joseph form for P
            I = np.eye(2)
            self.P = (I - K @ H) @ self.P @ (I - K @ H).T + K * self.R * K.T
            self.P = np.maximum(self.P, self._min_P)
            self.invalid_count = 0
            self.last_md2 = md2
            return True, md2
        else:
            # 2D update
            z = np.array([z_d, float(v_meas)])
            H = np.eye(2)
            R_mat = np.diag([self.R, float(Rv)])
            S = H @ self.P @ H.T + R_mat
            y = z - x_pred
            # 马氏距离 y^T S^-1 y
            try:
                invS = np.linalg.inv(S)
                md2 = float(y.T @ invS @ y)
            except np.linalg.LinAlgError:
                md2 = float('inf')
            # 2 DOF chi2 threshold ~ 25.0 for 99%
            if md2 > 25.0:
                self.last_md2 = md2
                return False, md2
            K = self.P @ H.T @ np.linalg.inv(S)
            state = x_pred + K @ y
            self.d, self.v_rel = float(state[0]), float(state[1])
            # Joseph form
            I = np.eye(2)
            self.P = (I - K @ H) @ self.P @ (I - K @ H).T + K @ R_mat @ K.T
            self.P = np.maximum(self.P, self._min_P)
            self.invalid_count = 0
            self.last_md2 = md2
            return True, md2

    # -------------------------
    # 根据车辆速度简化调整噪声（保守，幅度较小）
    # -------------------------
    def adjust_noise_params(self, v_ego: float) -> None:
        # 基础映射（较保守）
        if v_ego > 25.0:
            base_sigma_a = 0.12
            base_R = 1.2
        elif v_ego > 15.0:
            base_sigma_a = 0.18
            base_R = 1.5
        elif v_ego > 5.0:
            base_sigma_a = 0.16
            base_R = 1
        else:
            base_sigma_a = 0.12
            base_R = 1.2

        # 简单赋值，不做激进自适应以免引入不稳定
        self.sigma_a = base_sigma_a
        self.R = base_R

    # -------------------------
    # 限制相对速度突变（平滑器内使用）
    # -------------------------
    def limit_acceleration(self, dt: float, max_accel: float = 2.0) -> None:
        if dt <= 0:
            return
        accel = (self.v_rel - self.last_v_rel) / dt
        if abs(accel) > max_accel:
            alpha = 0.7
            self.v_rel = self.last_v_rel * alpha + self.v_rel * (1 - alpha)
        self.last_v_rel = self.v_rel

# --------------------------------------------------------------
#  RadarInterface（集成伪速度观测、马氏门控、输出低通、per-target历史）
# --------------------------------------------------------------
class RadarInterface(RadarInterfaceBase):
    def __init__(self, CP):
        super().__init__(CP)

        # ---------- 基础 CAN ----------
        if CP.radarUnavailable:
            self.rcp = None
        else:
            messages = [('RADAR_MRR', 60)]
            self.rcp = CANParser(DBC[CP.carFingerprint][Bus.pt], messages, CanBus.MPC)
            self.trigger_msg = 0x374

        # ---------- 数据结构 ----------
        self.pts: Dict[int, structs.RadarData.RadarPoint] = {}
        self.kalman_filters: Dict[int, SimpleKalmanFilter] = {}

        # per-target helpers
        self.dist_hist: Dict[int, deque] = {}       # (t, d) deque for pseudo velocity
        self._dist_bufs: Dict[int, deque] = {}      # per-target median buffer for preprocess
        self.last_valid_long: Dict[int, float] = {}
        self.vrel_filters: Dict[int, LowPassFilter] = {}

        # ---------- 统计 ----------
        self.updated_messages = set()

        # ---------- 日志 ----------
        self.log_path = "~/.comma/byd_debug/byd_radar_complete_data.log"
        
        os.makedirs(os.path.dirname(self.log_path), exist_ok=True)

        # ---------- 参数 ----------
        self.max_distance = 200.0
        self.min_distance = 0.5
        self.max_lat_offset = 4.0
        self.max_speed_change = 30.0
        self.max_dist_jump = 10.0
        self.filter_invalid_frames = 6     # 保守一点
        self.filter_delete_timeout = 1.5   # 秒

    # -----------------------------------------------------------------
    #  前处理：per-target 中值 + EMA
    # -----------------------------------------------------------------
    def preprocess_radar_data(self, target_id: int, raw_dist: float, msg_mrr: dict) -> Optional[float]:
        # per-target median buffer
        buf = self._dist_bufs.setdefault(target_id, deque(maxlen=5))
        buf.append(raw_dist)
        sorted_buf = sorted(list(buf))
        median = sorted_buf[len(sorted_buf) // 2]

        # per-target EMA state stored in attribute
        ema_attr = f"_dist_ema_{target_id}"
        if not hasattr(self, ema_attr):
            setattr(self, ema_attr, float(median))
            return float(median)
        else:
            prev = getattr(self, ema_attr)
            change = abs(median - prev)
            alpha = 0.4 if change < 0.5 else 0.2
            new = alpha * median + (1 - alpha) * prev
            setattr(self, ema_attr, float(new))
            return float(new)

    # -----------------------------------------------------------------
    #  生成伪速度（最小二乘线性拟合）
    # -----------------------------------------------------------------
    def compute_pseudo_velocity(self, target_id: int, current_ts: float, d_meas: float) -> Optional[float]:
        h = self.dist_hist.setdefault(target_id, deque(maxlen=6))
        h.append((current_ts, float(d_meas)))
        if len(h) < 3:
            return None
        ts = np.array([x[0] for x in h])
        ds = np.array([x[1] for x in h])
        t0 = ts[0]
        A = np.vstack([ts - t0, np.ones_like(ts)]).T
        try:
            slope, _ = np.linalg.lstsq(A, ds, rcond=None)[0]
            # slope = d(distance)/dt, which equals lead_speed - ego_speed (i.e. relative speed)
            return float(slope)
        except Exception:
            return None

    # -----------------------------------------------------------------
    #  主循环（每帧 CAN 数据）
    # -----------------------------------------------------------------
    def update(self, can_strings):
        if self.rcp is None:
            return super().update(None)

        # 使用单调时钟
        current_ts = time.monotonic()

        values = self.rcp.update_strings(can_strings)
        if self.trigger_msg not in values:
            # no radar MRR in this frame
            return None

        msg_mrr = self.rcp.vl['RADAR_MRR']
        target_id = int(msg_mrr['TargetID'])  # 1:left, 2:front, 3:right

        # 仅处理前向目标
        if target_id != 2:
            return None

        # 创建/获取 RadarPoint
        if target_id not in self.pts:
            self.pts[target_id] = structs.RadarData.RadarPoint()
        rp = self.pts[target_id]
        rp.trackId = target_id

        # 原始测量
        raw_long = float(msg_mrr['LongDist'])
        raw_lat = float(msg_mrr['LatDist'])
        is_valid = raw_long > 0 or bool(msg_mrr['IsValid'])

        # 基本合法性检查
        if not (self.min_distance <= raw_long <= self.max_distance):
            is_valid = False
        if abs(raw_lat) > self.max_lat_offset:
            is_valid = False
        if not bool(msg_mrr['IsValid']):
            is_valid = False

        # 连续性检查（per-target last_valid_long）
        if target_id in self.last_valid_long:
            if is_valid:
                jump = abs(raw_long - self.last_valid_long[target_id])
                if jump > self.max_dist_jump:
                    is_valid = False
                else:
                    self.last_valid_long[target_id] = raw_long
        else:
            if is_valid:
                self.last_valid_long[target_id] = raw_long

        # 预处理
        if is_valid:
            processed_long = self.preprocess_radar_data(target_id, raw_long, msg_mrr)
            if processed_long is None:
                is_valid = False
            else:
                raw_long = processed_long

        # Default dt_for_log
        dt_for_log = 0.0

        # 卡尔曼滤波器管理
        if is_valid:
            if target_id not in self.kalman_filters:
                kf = SimpleKalmanFilter(
                    initial_d=raw_long,
                    initial_time=current_ts,
                    sigma_a=0.15,
                    R=0.5,
                    distance_scale=1.0,
                    distance_offset=0.0,
                )
                self.kalman_filters[target_id] = kf
                # create output lowpass
                self.vrel_filters[target_id] = LowPassFilter(0.0)
                # init dist_hist
                self.dist_hist.setdefault(target_id, deque(maxlen=6))
            else:
                kf = self.kalman_filters[target_id]

            # adjust noise conservatively
            kf.adjust_noise_params(self.v_ego)

            # dt compute & clip
            dt = float(current_ts - kf.last_time)
            if dt <= 0 or dt > 0.5:
                dt = max(0.01, min(dt, 0.2))
            dt_for_log = dt  # save for logging before we overwrite last_time

            # predict
            kf.predict(dt)

            # compute pseudo velocity from recent preprocessed distances
            v_meas = self.compute_pseudo_velocity(target_id, current_ts, raw_long)

            # choose Rv (velocity observation variance) conservatively
            Rv = 1.0  # (m/s)^2 baseline; can be tuned
            if v_meas is not None:
                hist_len = len(self.dist_hist.get(target_id, []))
                if hist_len >= 5:
                    Rv = 0.8 ** 2
                elif hist_len >= 3:
                    Rv = 1.0 ** 2
                else:
                    Rv = 1.5 ** 2

            # update with gating
            updated, md2 = kf.update(raw_long, v_meas, Rv) if v_meas is not None else kf.update(raw_long, None)

            # 在update调用后添加重置机制
            if not updated:
                kf.reject_count = getattr(kf, 'reject_count', 0) + 1
                if kf.reject_count > 5:  # 连续5帧被拒绝就重置
                    kf.d = raw_long
                    kf.v_rel = 0.0
                    kf.P = np.array([[2.0, 0.0], [0.0, 5.0]])
                    kf.reject_count = 0
                    print(f"[RadarInterface] Reset KF for target {target_id} due to consecutive rejections")
            else:
                kf.reject_count = 0

            # acceleration / velocity limiting
            max_accel = 3.0 if self.v_ego > 15 else 2.0
            kf.limit_acceleration(dt, max_accel=max_accel)

            # set last_time to now (we did a predict and maybe update)
            kf.last_time = current_ts

            # output smoothing (per-target low-pass)
            v_filter = self.vrel_filters.setdefault(target_id, LowPassFilter(kf.v_rel))
            if self.v_ego < 10.0:
                tau = 0.5
            elif self.v_ego < 20.0:
                tau = 0.3
            else:
                tau = 0.2
            v_smoothed = v_filter.update(kf.v_rel, dt, tau)

            # fill RadarPoint - ensure consistency: use same (smoothed) vRel for both vRel and vLead
            rp.dRel = float(kf.d)
            rp.vRel = float(v_smoothed)
            rp.yRel = raw_lat
            rp.vLead = float(v_smoothed + self.v_ego)  # consistent with rp.vRel
            rp.aRel = float('nan')
            rp.yvRel = float('nan')
            rp.measured = bool(updated)

            # reset invalid counter on successful read
            if updated:
                kf.invalid_count = 0

        else:
            # 无效测量 -> 如果已有滤波器则仅做 predict (不把无效测量更新进来)，并输出预测值
            if target_id in self.kalman_filters:
                kf = self.kalman_filters[target_id]
                dt = float(current_ts - kf.last_time)
                dt = max(0.01, min(dt if dt > 0 else 0.01, 0.2))
                dt_for_log = dt
                kf.predict(dt)
                kf.limit_acceleration(dt, max_accel=3.0 if self.v_ego > 15 else 2.0)
                kf.last_time = current_ts
                kf.invalid_count += 1

                # output smoothed prediction
                v_filter = self.vrel_filters.setdefault(target_id, LowPassFilter(kf.v_rel))
                if self.v_ego < 10.0:
                    tau = 0.6
                elif self.v_ego < 20.0:
                    tau = 0.35
                else:
                    tau = 0.25
                v_smoothed = v_filter.update(kf.v_rel, dt, tau)

                rp.dRel = float(kf.d)
                rp.vRel = float(v_smoothed)
                rp.yRel = raw_lat
                rp.vLead = float(v_smoothed + self.v_ego)  # consistent
                rp.aRel = float('nan')
                rp.yvRel = float('nan')
                rp.measured = False
            else:
                # 没有历史滤波器，保留默认或先不填
                rp.measured = False
                try:
                    rp.dRel = float(raw_long) if raw_long > 0 else 199.0
                except Exception:
                    rp.dRel = 199.0
                rp.vRel = 0.0
                rp.vLead = float(self.v_ego)
                rp.yRel = raw_lat

        # 速度突变保护（对输出值再次防护）
        if hasattr(rp, 'vRel') and rp.vRel is not None:
            if abs(rp.vRel) > self.max_speed_change:
                if target_id in self.kalman_filters:
                    rp.vRel = float(self.kalman_filters[target_id].last_v_rel)
                    # ensure vLead consistent too
                    rp.vLead = float(rp.vRel + self.v_ego)
                else:
                    rp.vRel = 0.0
                    rp.vLead = float(self.v_ego)

        # 日志：记录更多诊断信息（使用 dt_for_log 保存的值）
        try:
            with open(self.log_path, "a") as f:
                kf = self.kalman_filters.get(target_id, None)
                kf_dist = kf.d if kf is not None else 199.0
                kf_vrel = kf.v_rel if kf is not None else 0.0
                dist_diff = abs(raw_long - rp.dRel) if rp.dRel < 199 else 0.0
                timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                v_ego_kmh = self.v_ego * 3.6
                kf_vrel_kmh = kf_vrel * 3.6
                final_vrel_kmh = rp.vRel * 3.6 if rp.vRel is not None else 0.0
                md2_info = getattr(kf, 'last_md2', 0.0) if kf is not None else 0.0
                f.write(
                    f"{timestamp}, dt={dt_for_log:.3f}, "
                    f"raw: dist={raw_long:.2f}, lat={raw_lat:.2f}, valid={is_valid}, "
                    f"kf: dist={kf_dist:.2f}, kf_vrel_raw={kf_vrel_kmh:.1f}km/h, "
                    f"final: dist={rp.dRel:.2f}, vrel={final_vrel_kmh:.1f}km/h, "
                    f"vlead={(rp.vLead)*3.6:.1f}km/h, diff={dist_diff:.2f}, "
                    f"md2={md2_info:.2f}, updated={rp.measured}, v_ego={v_ego_kmh:.1f}km/h\n"
                )
        except Exception as e:
            print(f"[RadarInterface] log error: {e}")

        # 清理：删除长时间未更新的滤波器（按 invalid_count 和时间共同判断）
        to_del = []
        for tid, kf in list(self.kalman_filters.items()):
            age = current_ts - kf.last_time
            if kf.invalid_count >= self.filter_invalid_frames and age > self.filter_delete_timeout:
                to_del.append(tid)
        for tid in to_del:
            self.kalman_filters.pop(tid, None)
            self.pts.pop(tid, None)
            self.dist_hist.pop(tid, None)
            self._dist_bufs.pop(tid, None)
            self.last_valid_long.pop(tid, None)
            self.vrel_filters.pop(tid, None)

        radar_data = structs.RadarData()
        radar_data.points = list(self.pts.values())
        return radar_data
