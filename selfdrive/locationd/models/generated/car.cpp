#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_8962454530658731827) {
   out_8962454530658731827[0] = delta_x[0] + nom_x[0];
   out_8962454530658731827[1] = delta_x[1] + nom_x[1];
   out_8962454530658731827[2] = delta_x[2] + nom_x[2];
   out_8962454530658731827[3] = delta_x[3] + nom_x[3];
   out_8962454530658731827[4] = delta_x[4] + nom_x[4];
   out_8962454530658731827[5] = delta_x[5] + nom_x[5];
   out_8962454530658731827[6] = delta_x[6] + nom_x[6];
   out_8962454530658731827[7] = delta_x[7] + nom_x[7];
   out_8962454530658731827[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4507608153926057699) {
   out_4507608153926057699[0] = -nom_x[0] + true_x[0];
   out_4507608153926057699[1] = -nom_x[1] + true_x[1];
   out_4507608153926057699[2] = -nom_x[2] + true_x[2];
   out_4507608153926057699[3] = -nom_x[3] + true_x[3];
   out_4507608153926057699[4] = -nom_x[4] + true_x[4];
   out_4507608153926057699[5] = -nom_x[5] + true_x[5];
   out_4507608153926057699[6] = -nom_x[6] + true_x[6];
   out_4507608153926057699[7] = -nom_x[7] + true_x[7];
   out_4507608153926057699[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2863448119937815941) {
   out_2863448119937815941[0] = 1.0;
   out_2863448119937815941[1] = 0.0;
   out_2863448119937815941[2] = 0.0;
   out_2863448119937815941[3] = 0.0;
   out_2863448119937815941[4] = 0.0;
   out_2863448119937815941[5] = 0.0;
   out_2863448119937815941[6] = 0.0;
   out_2863448119937815941[7] = 0.0;
   out_2863448119937815941[8] = 0.0;
   out_2863448119937815941[9] = 0.0;
   out_2863448119937815941[10] = 1.0;
   out_2863448119937815941[11] = 0.0;
   out_2863448119937815941[12] = 0.0;
   out_2863448119937815941[13] = 0.0;
   out_2863448119937815941[14] = 0.0;
   out_2863448119937815941[15] = 0.0;
   out_2863448119937815941[16] = 0.0;
   out_2863448119937815941[17] = 0.0;
   out_2863448119937815941[18] = 0.0;
   out_2863448119937815941[19] = 0.0;
   out_2863448119937815941[20] = 1.0;
   out_2863448119937815941[21] = 0.0;
   out_2863448119937815941[22] = 0.0;
   out_2863448119937815941[23] = 0.0;
   out_2863448119937815941[24] = 0.0;
   out_2863448119937815941[25] = 0.0;
   out_2863448119937815941[26] = 0.0;
   out_2863448119937815941[27] = 0.0;
   out_2863448119937815941[28] = 0.0;
   out_2863448119937815941[29] = 0.0;
   out_2863448119937815941[30] = 1.0;
   out_2863448119937815941[31] = 0.0;
   out_2863448119937815941[32] = 0.0;
   out_2863448119937815941[33] = 0.0;
   out_2863448119937815941[34] = 0.0;
   out_2863448119937815941[35] = 0.0;
   out_2863448119937815941[36] = 0.0;
   out_2863448119937815941[37] = 0.0;
   out_2863448119937815941[38] = 0.0;
   out_2863448119937815941[39] = 0.0;
   out_2863448119937815941[40] = 1.0;
   out_2863448119937815941[41] = 0.0;
   out_2863448119937815941[42] = 0.0;
   out_2863448119937815941[43] = 0.0;
   out_2863448119937815941[44] = 0.0;
   out_2863448119937815941[45] = 0.0;
   out_2863448119937815941[46] = 0.0;
   out_2863448119937815941[47] = 0.0;
   out_2863448119937815941[48] = 0.0;
   out_2863448119937815941[49] = 0.0;
   out_2863448119937815941[50] = 1.0;
   out_2863448119937815941[51] = 0.0;
   out_2863448119937815941[52] = 0.0;
   out_2863448119937815941[53] = 0.0;
   out_2863448119937815941[54] = 0.0;
   out_2863448119937815941[55] = 0.0;
   out_2863448119937815941[56] = 0.0;
   out_2863448119937815941[57] = 0.0;
   out_2863448119937815941[58] = 0.0;
   out_2863448119937815941[59] = 0.0;
   out_2863448119937815941[60] = 1.0;
   out_2863448119937815941[61] = 0.0;
   out_2863448119937815941[62] = 0.0;
   out_2863448119937815941[63] = 0.0;
   out_2863448119937815941[64] = 0.0;
   out_2863448119937815941[65] = 0.0;
   out_2863448119937815941[66] = 0.0;
   out_2863448119937815941[67] = 0.0;
   out_2863448119937815941[68] = 0.0;
   out_2863448119937815941[69] = 0.0;
   out_2863448119937815941[70] = 1.0;
   out_2863448119937815941[71] = 0.0;
   out_2863448119937815941[72] = 0.0;
   out_2863448119937815941[73] = 0.0;
   out_2863448119937815941[74] = 0.0;
   out_2863448119937815941[75] = 0.0;
   out_2863448119937815941[76] = 0.0;
   out_2863448119937815941[77] = 0.0;
   out_2863448119937815941[78] = 0.0;
   out_2863448119937815941[79] = 0.0;
   out_2863448119937815941[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8331107966104169540) {
   out_8331107966104169540[0] = state[0];
   out_8331107966104169540[1] = state[1];
   out_8331107966104169540[2] = state[2];
   out_8331107966104169540[3] = state[3];
   out_8331107966104169540[4] = state[4];
   out_8331107966104169540[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8331107966104169540[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8331107966104169540[7] = state[7];
   out_8331107966104169540[8] = state[8];
}
void F_fun(double *state, double dt, double *out_9160760222570051709) {
   out_9160760222570051709[0] = 1;
   out_9160760222570051709[1] = 0;
   out_9160760222570051709[2] = 0;
   out_9160760222570051709[3] = 0;
   out_9160760222570051709[4] = 0;
   out_9160760222570051709[5] = 0;
   out_9160760222570051709[6] = 0;
   out_9160760222570051709[7] = 0;
   out_9160760222570051709[8] = 0;
   out_9160760222570051709[9] = 0;
   out_9160760222570051709[10] = 1;
   out_9160760222570051709[11] = 0;
   out_9160760222570051709[12] = 0;
   out_9160760222570051709[13] = 0;
   out_9160760222570051709[14] = 0;
   out_9160760222570051709[15] = 0;
   out_9160760222570051709[16] = 0;
   out_9160760222570051709[17] = 0;
   out_9160760222570051709[18] = 0;
   out_9160760222570051709[19] = 0;
   out_9160760222570051709[20] = 1;
   out_9160760222570051709[21] = 0;
   out_9160760222570051709[22] = 0;
   out_9160760222570051709[23] = 0;
   out_9160760222570051709[24] = 0;
   out_9160760222570051709[25] = 0;
   out_9160760222570051709[26] = 0;
   out_9160760222570051709[27] = 0;
   out_9160760222570051709[28] = 0;
   out_9160760222570051709[29] = 0;
   out_9160760222570051709[30] = 1;
   out_9160760222570051709[31] = 0;
   out_9160760222570051709[32] = 0;
   out_9160760222570051709[33] = 0;
   out_9160760222570051709[34] = 0;
   out_9160760222570051709[35] = 0;
   out_9160760222570051709[36] = 0;
   out_9160760222570051709[37] = 0;
   out_9160760222570051709[38] = 0;
   out_9160760222570051709[39] = 0;
   out_9160760222570051709[40] = 1;
   out_9160760222570051709[41] = 0;
   out_9160760222570051709[42] = 0;
   out_9160760222570051709[43] = 0;
   out_9160760222570051709[44] = 0;
   out_9160760222570051709[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_9160760222570051709[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_9160760222570051709[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_9160760222570051709[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_9160760222570051709[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_9160760222570051709[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_9160760222570051709[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_9160760222570051709[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_9160760222570051709[53] = -9.8100000000000005*dt;
   out_9160760222570051709[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_9160760222570051709[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_9160760222570051709[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9160760222570051709[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9160760222570051709[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_9160760222570051709[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_9160760222570051709[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_9160760222570051709[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9160760222570051709[62] = 0;
   out_9160760222570051709[63] = 0;
   out_9160760222570051709[64] = 0;
   out_9160760222570051709[65] = 0;
   out_9160760222570051709[66] = 0;
   out_9160760222570051709[67] = 0;
   out_9160760222570051709[68] = 0;
   out_9160760222570051709[69] = 0;
   out_9160760222570051709[70] = 1;
   out_9160760222570051709[71] = 0;
   out_9160760222570051709[72] = 0;
   out_9160760222570051709[73] = 0;
   out_9160760222570051709[74] = 0;
   out_9160760222570051709[75] = 0;
   out_9160760222570051709[76] = 0;
   out_9160760222570051709[77] = 0;
   out_9160760222570051709[78] = 0;
   out_9160760222570051709[79] = 0;
   out_9160760222570051709[80] = 1;
}
void h_25(double *state, double *unused, double *out_5595677784588520775) {
   out_5595677784588520775[0] = state[6];
}
void H_25(double *state, double *unused, double *out_226891194922389747) {
   out_226891194922389747[0] = 0;
   out_226891194922389747[1] = 0;
   out_226891194922389747[2] = 0;
   out_226891194922389747[3] = 0;
   out_226891194922389747[4] = 0;
   out_226891194922389747[5] = 0;
   out_226891194922389747[6] = 1;
   out_226891194922389747[7] = 0;
   out_226891194922389747[8] = 0;
}
void h_24(double *state, double *unused, double *out_3287452291782623794) {
   out_3287452291782623794[0] = state[4];
   out_3287452291782623794[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8612136553906176180) {
   out_8612136553906176180[0] = 0;
   out_8612136553906176180[1] = 0;
   out_8612136553906176180[2] = 0;
   out_8612136553906176180[3] = 0;
   out_8612136553906176180[4] = 1;
   out_8612136553906176180[5] = 0;
   out_8612136553906176180[6] = 0;
   out_8612136553906176180[7] = 0;
   out_8612136553906176180[8] = 0;
   out_8612136553906176180[9] = 0;
   out_8612136553906176180[10] = 0;
   out_8612136553906176180[11] = 0;
   out_8612136553906176180[12] = 0;
   out_8612136553906176180[13] = 0;
   out_8612136553906176180[14] = 1;
   out_8612136553906176180[15] = 0;
   out_8612136553906176180[16] = 0;
   out_8612136553906176180[17] = 0;
}
void h_30(double *state, double *unused, double *out_5870871846873026664) {
   out_5870871846873026664[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2745224153429638374) {
   out_2745224153429638374[0] = 0;
   out_2745224153429638374[1] = 0;
   out_2745224153429638374[2] = 0;
   out_2745224153429638374[3] = 0;
   out_2745224153429638374[4] = 1;
   out_2745224153429638374[5] = 0;
   out_2745224153429638374[6] = 0;
   out_2745224153429638374[7] = 0;
   out_2745224153429638374[8] = 0;
}
void h_26(double *state, double *unused, double *out_8251043219507245013) {
   out_8251043219507245013[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3514612123951666477) {
   out_3514612123951666477[0] = 0;
   out_3514612123951666477[1] = 0;
   out_3514612123951666477[2] = 0;
   out_3514612123951666477[3] = 0;
   out_3514612123951666477[4] = 0;
   out_3514612123951666477[5] = 0;
   out_3514612123951666477[6] = 0;
   out_3514612123951666477[7] = 1;
   out_3514612123951666477[8] = 0;
}
void h_27(double *state, double *unused, double *out_6972780801562315753) {
   out_6972780801562315753[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4968818224613581591) {
   out_4968818224613581591[0] = 0;
   out_4968818224613581591[1] = 0;
   out_4968818224613581591[2] = 0;
   out_4968818224613581591[3] = 1;
   out_4968818224613581591[4] = 0;
   out_4968818224613581591[5] = 0;
   out_4968818224613581591[6] = 0;
   out_4968818224613581591[7] = 0;
   out_4968818224613581591[8] = 0;
}
void h_29(double *state, double *unused, double *out_4270747315161249893) {
   out_4270747315161249893[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3255455497744030558) {
   out_3255455497744030558[0] = 0;
   out_3255455497744030558[1] = 1;
   out_3255455497744030558[2] = 0;
   out_3255455497744030558[3] = 0;
   out_3255455497744030558[4] = 0;
   out_3255455497744030558[5] = 0;
   out_3255455497744030558[6] = 0;
   out_3255455497744030558[7] = 0;
   out_3255455497744030558[8] = 0;
}
void h_28(double *state, double *unused, double *out_5255483816363335857) {
   out_5255483816363335857[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1826943519325500016) {
   out_1826943519325500016[0] = 1;
   out_1826943519325500016[1] = 0;
   out_1826943519325500016[2] = 0;
   out_1826943519325500016[3] = 0;
   out_1826943519325500016[4] = 0;
   out_1826943519325500016[5] = 0;
   out_1826943519325500016[6] = 0;
   out_1826943519325500016[7] = 0;
   out_1826943519325500016[8] = 0;
}
void h_31(double *state, double *unused, double *out_4211188812402488957) {
   out_4211188812402488957[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4140820226185017953) {
   out_4140820226185017953[0] = 0;
   out_4140820226185017953[1] = 0;
   out_4140820226185017953[2] = 0;
   out_4140820226185017953[3] = 0;
   out_4140820226185017953[4] = 0;
   out_4140820226185017953[5] = 0;
   out_4140820226185017953[6] = 0;
   out_4140820226185017953[7] = 0;
   out_4140820226185017953[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_8962454530658731827) {
  err_fun(nom_x, delta_x, out_8962454530658731827);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4507608153926057699) {
  inv_err_fun(nom_x, true_x, out_4507608153926057699);
}
void car_H_mod_fun(double *state, double *out_2863448119937815941) {
  H_mod_fun(state, out_2863448119937815941);
}
void car_f_fun(double *state, double dt, double *out_8331107966104169540) {
  f_fun(state,  dt, out_8331107966104169540);
}
void car_F_fun(double *state, double dt, double *out_9160760222570051709) {
  F_fun(state,  dt, out_9160760222570051709);
}
void car_h_25(double *state, double *unused, double *out_5595677784588520775) {
  h_25(state, unused, out_5595677784588520775);
}
void car_H_25(double *state, double *unused, double *out_226891194922389747) {
  H_25(state, unused, out_226891194922389747);
}
void car_h_24(double *state, double *unused, double *out_3287452291782623794) {
  h_24(state, unused, out_3287452291782623794);
}
void car_H_24(double *state, double *unused, double *out_8612136553906176180) {
  H_24(state, unused, out_8612136553906176180);
}
void car_h_30(double *state, double *unused, double *out_5870871846873026664) {
  h_30(state, unused, out_5870871846873026664);
}
void car_H_30(double *state, double *unused, double *out_2745224153429638374) {
  H_30(state, unused, out_2745224153429638374);
}
void car_h_26(double *state, double *unused, double *out_8251043219507245013) {
  h_26(state, unused, out_8251043219507245013);
}
void car_H_26(double *state, double *unused, double *out_3514612123951666477) {
  H_26(state, unused, out_3514612123951666477);
}
void car_h_27(double *state, double *unused, double *out_6972780801562315753) {
  h_27(state, unused, out_6972780801562315753);
}
void car_H_27(double *state, double *unused, double *out_4968818224613581591) {
  H_27(state, unused, out_4968818224613581591);
}
void car_h_29(double *state, double *unused, double *out_4270747315161249893) {
  h_29(state, unused, out_4270747315161249893);
}
void car_H_29(double *state, double *unused, double *out_3255455497744030558) {
  H_29(state, unused, out_3255455497744030558);
}
void car_h_28(double *state, double *unused, double *out_5255483816363335857) {
  h_28(state, unused, out_5255483816363335857);
}
void car_H_28(double *state, double *unused, double *out_1826943519325500016) {
  H_28(state, unused, out_1826943519325500016);
}
void car_h_31(double *state, double *unused, double *out_4211188812402488957) {
  h_31(state, unused, out_4211188812402488957);
}
void car_H_31(double *state, double *unused, double *out_4140820226185017953) {
  H_31(state, unused, out_4140820226185017953);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
