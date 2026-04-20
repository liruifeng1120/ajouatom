#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_8962454530658731827);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4507608153926057699);
void car_H_mod_fun(double *state, double *out_2863448119937815941);
void car_f_fun(double *state, double dt, double *out_8331107966104169540);
void car_F_fun(double *state, double dt, double *out_9160760222570051709);
void car_h_25(double *state, double *unused, double *out_5595677784588520775);
void car_H_25(double *state, double *unused, double *out_226891194922389747);
void car_h_24(double *state, double *unused, double *out_3287452291782623794);
void car_H_24(double *state, double *unused, double *out_8612136553906176180);
void car_h_30(double *state, double *unused, double *out_5870871846873026664);
void car_H_30(double *state, double *unused, double *out_2745224153429638374);
void car_h_26(double *state, double *unused, double *out_8251043219507245013);
void car_H_26(double *state, double *unused, double *out_3514612123951666477);
void car_h_27(double *state, double *unused, double *out_6972780801562315753);
void car_H_27(double *state, double *unused, double *out_4968818224613581591);
void car_h_29(double *state, double *unused, double *out_4270747315161249893);
void car_H_29(double *state, double *unused, double *out_3255455497744030558);
void car_h_28(double *state, double *unused, double *out_5255483816363335857);
void car_H_28(double *state, double *unused, double *out_1826943519325500016);
void car_h_31(double *state, double *unused, double *out_4211188812402488957);
void car_H_31(double *state, double *unused, double *out_4140820226185017953);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}