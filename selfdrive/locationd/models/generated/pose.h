#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6620113396710350830);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3901415459874751196);
void pose_H_mod_fun(double *state, double *out_6339358362171484689);
void pose_f_fun(double *state, double dt, double *out_4513120832515025974);
void pose_F_fun(double *state, double dt, double *out_6824255030541141050);
void pose_h_4(double *state, double *unused, double *out_634066535336441633);
void pose_H_4(double *state, double *unused, double *out_8833163632747117674);
void pose_h_10(double *state, double *unused, double *out_6697639128282696940);
void pose_H_10(double *state, double *unused, double *out_5834408245444951106);
void pose_h_13(double *state, double *unused, double *out_2024418455697663562);
void pose_H_13(double *state, double *unused, double *out_6401306615630101141);
void pose_h_14(double *state, double *unused, double *out_7328828287226735843);
void pose_H_14(double *state, double *unused, double *out_5650339584622949413);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}