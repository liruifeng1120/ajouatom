#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_6620113396710350830) {
   out_6620113396710350830[0] = delta_x[0] + nom_x[0];
   out_6620113396710350830[1] = delta_x[1] + nom_x[1];
   out_6620113396710350830[2] = delta_x[2] + nom_x[2];
   out_6620113396710350830[3] = delta_x[3] + nom_x[3];
   out_6620113396710350830[4] = delta_x[4] + nom_x[4];
   out_6620113396710350830[5] = delta_x[5] + nom_x[5];
   out_6620113396710350830[6] = delta_x[6] + nom_x[6];
   out_6620113396710350830[7] = delta_x[7] + nom_x[7];
   out_6620113396710350830[8] = delta_x[8] + nom_x[8];
   out_6620113396710350830[9] = delta_x[9] + nom_x[9];
   out_6620113396710350830[10] = delta_x[10] + nom_x[10];
   out_6620113396710350830[11] = delta_x[11] + nom_x[11];
   out_6620113396710350830[12] = delta_x[12] + nom_x[12];
   out_6620113396710350830[13] = delta_x[13] + nom_x[13];
   out_6620113396710350830[14] = delta_x[14] + nom_x[14];
   out_6620113396710350830[15] = delta_x[15] + nom_x[15];
   out_6620113396710350830[16] = delta_x[16] + nom_x[16];
   out_6620113396710350830[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3901415459874751196) {
   out_3901415459874751196[0] = -nom_x[0] + true_x[0];
   out_3901415459874751196[1] = -nom_x[1] + true_x[1];
   out_3901415459874751196[2] = -nom_x[2] + true_x[2];
   out_3901415459874751196[3] = -nom_x[3] + true_x[3];
   out_3901415459874751196[4] = -nom_x[4] + true_x[4];
   out_3901415459874751196[5] = -nom_x[5] + true_x[5];
   out_3901415459874751196[6] = -nom_x[6] + true_x[6];
   out_3901415459874751196[7] = -nom_x[7] + true_x[7];
   out_3901415459874751196[8] = -nom_x[8] + true_x[8];
   out_3901415459874751196[9] = -nom_x[9] + true_x[9];
   out_3901415459874751196[10] = -nom_x[10] + true_x[10];
   out_3901415459874751196[11] = -nom_x[11] + true_x[11];
   out_3901415459874751196[12] = -nom_x[12] + true_x[12];
   out_3901415459874751196[13] = -nom_x[13] + true_x[13];
   out_3901415459874751196[14] = -nom_x[14] + true_x[14];
   out_3901415459874751196[15] = -nom_x[15] + true_x[15];
   out_3901415459874751196[16] = -nom_x[16] + true_x[16];
   out_3901415459874751196[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6339358362171484689) {
   out_6339358362171484689[0] = 1.0;
   out_6339358362171484689[1] = 0.0;
   out_6339358362171484689[2] = 0.0;
   out_6339358362171484689[3] = 0.0;
   out_6339358362171484689[4] = 0.0;
   out_6339358362171484689[5] = 0.0;
   out_6339358362171484689[6] = 0.0;
   out_6339358362171484689[7] = 0.0;
   out_6339358362171484689[8] = 0.0;
   out_6339358362171484689[9] = 0.0;
   out_6339358362171484689[10] = 0.0;
   out_6339358362171484689[11] = 0.0;
   out_6339358362171484689[12] = 0.0;
   out_6339358362171484689[13] = 0.0;
   out_6339358362171484689[14] = 0.0;
   out_6339358362171484689[15] = 0.0;
   out_6339358362171484689[16] = 0.0;
   out_6339358362171484689[17] = 0.0;
   out_6339358362171484689[18] = 0.0;
   out_6339358362171484689[19] = 1.0;
   out_6339358362171484689[20] = 0.0;
   out_6339358362171484689[21] = 0.0;
   out_6339358362171484689[22] = 0.0;
   out_6339358362171484689[23] = 0.0;
   out_6339358362171484689[24] = 0.0;
   out_6339358362171484689[25] = 0.0;
   out_6339358362171484689[26] = 0.0;
   out_6339358362171484689[27] = 0.0;
   out_6339358362171484689[28] = 0.0;
   out_6339358362171484689[29] = 0.0;
   out_6339358362171484689[30] = 0.0;
   out_6339358362171484689[31] = 0.0;
   out_6339358362171484689[32] = 0.0;
   out_6339358362171484689[33] = 0.0;
   out_6339358362171484689[34] = 0.0;
   out_6339358362171484689[35] = 0.0;
   out_6339358362171484689[36] = 0.0;
   out_6339358362171484689[37] = 0.0;
   out_6339358362171484689[38] = 1.0;
   out_6339358362171484689[39] = 0.0;
   out_6339358362171484689[40] = 0.0;
   out_6339358362171484689[41] = 0.0;
   out_6339358362171484689[42] = 0.0;
   out_6339358362171484689[43] = 0.0;
   out_6339358362171484689[44] = 0.0;
   out_6339358362171484689[45] = 0.0;
   out_6339358362171484689[46] = 0.0;
   out_6339358362171484689[47] = 0.0;
   out_6339358362171484689[48] = 0.0;
   out_6339358362171484689[49] = 0.0;
   out_6339358362171484689[50] = 0.0;
   out_6339358362171484689[51] = 0.0;
   out_6339358362171484689[52] = 0.0;
   out_6339358362171484689[53] = 0.0;
   out_6339358362171484689[54] = 0.0;
   out_6339358362171484689[55] = 0.0;
   out_6339358362171484689[56] = 0.0;
   out_6339358362171484689[57] = 1.0;
   out_6339358362171484689[58] = 0.0;
   out_6339358362171484689[59] = 0.0;
   out_6339358362171484689[60] = 0.0;
   out_6339358362171484689[61] = 0.0;
   out_6339358362171484689[62] = 0.0;
   out_6339358362171484689[63] = 0.0;
   out_6339358362171484689[64] = 0.0;
   out_6339358362171484689[65] = 0.0;
   out_6339358362171484689[66] = 0.0;
   out_6339358362171484689[67] = 0.0;
   out_6339358362171484689[68] = 0.0;
   out_6339358362171484689[69] = 0.0;
   out_6339358362171484689[70] = 0.0;
   out_6339358362171484689[71] = 0.0;
   out_6339358362171484689[72] = 0.0;
   out_6339358362171484689[73] = 0.0;
   out_6339358362171484689[74] = 0.0;
   out_6339358362171484689[75] = 0.0;
   out_6339358362171484689[76] = 1.0;
   out_6339358362171484689[77] = 0.0;
   out_6339358362171484689[78] = 0.0;
   out_6339358362171484689[79] = 0.0;
   out_6339358362171484689[80] = 0.0;
   out_6339358362171484689[81] = 0.0;
   out_6339358362171484689[82] = 0.0;
   out_6339358362171484689[83] = 0.0;
   out_6339358362171484689[84] = 0.0;
   out_6339358362171484689[85] = 0.0;
   out_6339358362171484689[86] = 0.0;
   out_6339358362171484689[87] = 0.0;
   out_6339358362171484689[88] = 0.0;
   out_6339358362171484689[89] = 0.0;
   out_6339358362171484689[90] = 0.0;
   out_6339358362171484689[91] = 0.0;
   out_6339358362171484689[92] = 0.0;
   out_6339358362171484689[93] = 0.0;
   out_6339358362171484689[94] = 0.0;
   out_6339358362171484689[95] = 1.0;
   out_6339358362171484689[96] = 0.0;
   out_6339358362171484689[97] = 0.0;
   out_6339358362171484689[98] = 0.0;
   out_6339358362171484689[99] = 0.0;
   out_6339358362171484689[100] = 0.0;
   out_6339358362171484689[101] = 0.0;
   out_6339358362171484689[102] = 0.0;
   out_6339358362171484689[103] = 0.0;
   out_6339358362171484689[104] = 0.0;
   out_6339358362171484689[105] = 0.0;
   out_6339358362171484689[106] = 0.0;
   out_6339358362171484689[107] = 0.0;
   out_6339358362171484689[108] = 0.0;
   out_6339358362171484689[109] = 0.0;
   out_6339358362171484689[110] = 0.0;
   out_6339358362171484689[111] = 0.0;
   out_6339358362171484689[112] = 0.0;
   out_6339358362171484689[113] = 0.0;
   out_6339358362171484689[114] = 1.0;
   out_6339358362171484689[115] = 0.0;
   out_6339358362171484689[116] = 0.0;
   out_6339358362171484689[117] = 0.0;
   out_6339358362171484689[118] = 0.0;
   out_6339358362171484689[119] = 0.0;
   out_6339358362171484689[120] = 0.0;
   out_6339358362171484689[121] = 0.0;
   out_6339358362171484689[122] = 0.0;
   out_6339358362171484689[123] = 0.0;
   out_6339358362171484689[124] = 0.0;
   out_6339358362171484689[125] = 0.0;
   out_6339358362171484689[126] = 0.0;
   out_6339358362171484689[127] = 0.0;
   out_6339358362171484689[128] = 0.0;
   out_6339358362171484689[129] = 0.0;
   out_6339358362171484689[130] = 0.0;
   out_6339358362171484689[131] = 0.0;
   out_6339358362171484689[132] = 0.0;
   out_6339358362171484689[133] = 1.0;
   out_6339358362171484689[134] = 0.0;
   out_6339358362171484689[135] = 0.0;
   out_6339358362171484689[136] = 0.0;
   out_6339358362171484689[137] = 0.0;
   out_6339358362171484689[138] = 0.0;
   out_6339358362171484689[139] = 0.0;
   out_6339358362171484689[140] = 0.0;
   out_6339358362171484689[141] = 0.0;
   out_6339358362171484689[142] = 0.0;
   out_6339358362171484689[143] = 0.0;
   out_6339358362171484689[144] = 0.0;
   out_6339358362171484689[145] = 0.0;
   out_6339358362171484689[146] = 0.0;
   out_6339358362171484689[147] = 0.0;
   out_6339358362171484689[148] = 0.0;
   out_6339358362171484689[149] = 0.0;
   out_6339358362171484689[150] = 0.0;
   out_6339358362171484689[151] = 0.0;
   out_6339358362171484689[152] = 1.0;
   out_6339358362171484689[153] = 0.0;
   out_6339358362171484689[154] = 0.0;
   out_6339358362171484689[155] = 0.0;
   out_6339358362171484689[156] = 0.0;
   out_6339358362171484689[157] = 0.0;
   out_6339358362171484689[158] = 0.0;
   out_6339358362171484689[159] = 0.0;
   out_6339358362171484689[160] = 0.0;
   out_6339358362171484689[161] = 0.0;
   out_6339358362171484689[162] = 0.0;
   out_6339358362171484689[163] = 0.0;
   out_6339358362171484689[164] = 0.0;
   out_6339358362171484689[165] = 0.0;
   out_6339358362171484689[166] = 0.0;
   out_6339358362171484689[167] = 0.0;
   out_6339358362171484689[168] = 0.0;
   out_6339358362171484689[169] = 0.0;
   out_6339358362171484689[170] = 0.0;
   out_6339358362171484689[171] = 1.0;
   out_6339358362171484689[172] = 0.0;
   out_6339358362171484689[173] = 0.0;
   out_6339358362171484689[174] = 0.0;
   out_6339358362171484689[175] = 0.0;
   out_6339358362171484689[176] = 0.0;
   out_6339358362171484689[177] = 0.0;
   out_6339358362171484689[178] = 0.0;
   out_6339358362171484689[179] = 0.0;
   out_6339358362171484689[180] = 0.0;
   out_6339358362171484689[181] = 0.0;
   out_6339358362171484689[182] = 0.0;
   out_6339358362171484689[183] = 0.0;
   out_6339358362171484689[184] = 0.0;
   out_6339358362171484689[185] = 0.0;
   out_6339358362171484689[186] = 0.0;
   out_6339358362171484689[187] = 0.0;
   out_6339358362171484689[188] = 0.0;
   out_6339358362171484689[189] = 0.0;
   out_6339358362171484689[190] = 1.0;
   out_6339358362171484689[191] = 0.0;
   out_6339358362171484689[192] = 0.0;
   out_6339358362171484689[193] = 0.0;
   out_6339358362171484689[194] = 0.0;
   out_6339358362171484689[195] = 0.0;
   out_6339358362171484689[196] = 0.0;
   out_6339358362171484689[197] = 0.0;
   out_6339358362171484689[198] = 0.0;
   out_6339358362171484689[199] = 0.0;
   out_6339358362171484689[200] = 0.0;
   out_6339358362171484689[201] = 0.0;
   out_6339358362171484689[202] = 0.0;
   out_6339358362171484689[203] = 0.0;
   out_6339358362171484689[204] = 0.0;
   out_6339358362171484689[205] = 0.0;
   out_6339358362171484689[206] = 0.0;
   out_6339358362171484689[207] = 0.0;
   out_6339358362171484689[208] = 0.0;
   out_6339358362171484689[209] = 1.0;
   out_6339358362171484689[210] = 0.0;
   out_6339358362171484689[211] = 0.0;
   out_6339358362171484689[212] = 0.0;
   out_6339358362171484689[213] = 0.0;
   out_6339358362171484689[214] = 0.0;
   out_6339358362171484689[215] = 0.0;
   out_6339358362171484689[216] = 0.0;
   out_6339358362171484689[217] = 0.0;
   out_6339358362171484689[218] = 0.0;
   out_6339358362171484689[219] = 0.0;
   out_6339358362171484689[220] = 0.0;
   out_6339358362171484689[221] = 0.0;
   out_6339358362171484689[222] = 0.0;
   out_6339358362171484689[223] = 0.0;
   out_6339358362171484689[224] = 0.0;
   out_6339358362171484689[225] = 0.0;
   out_6339358362171484689[226] = 0.0;
   out_6339358362171484689[227] = 0.0;
   out_6339358362171484689[228] = 1.0;
   out_6339358362171484689[229] = 0.0;
   out_6339358362171484689[230] = 0.0;
   out_6339358362171484689[231] = 0.0;
   out_6339358362171484689[232] = 0.0;
   out_6339358362171484689[233] = 0.0;
   out_6339358362171484689[234] = 0.0;
   out_6339358362171484689[235] = 0.0;
   out_6339358362171484689[236] = 0.0;
   out_6339358362171484689[237] = 0.0;
   out_6339358362171484689[238] = 0.0;
   out_6339358362171484689[239] = 0.0;
   out_6339358362171484689[240] = 0.0;
   out_6339358362171484689[241] = 0.0;
   out_6339358362171484689[242] = 0.0;
   out_6339358362171484689[243] = 0.0;
   out_6339358362171484689[244] = 0.0;
   out_6339358362171484689[245] = 0.0;
   out_6339358362171484689[246] = 0.0;
   out_6339358362171484689[247] = 1.0;
   out_6339358362171484689[248] = 0.0;
   out_6339358362171484689[249] = 0.0;
   out_6339358362171484689[250] = 0.0;
   out_6339358362171484689[251] = 0.0;
   out_6339358362171484689[252] = 0.0;
   out_6339358362171484689[253] = 0.0;
   out_6339358362171484689[254] = 0.0;
   out_6339358362171484689[255] = 0.0;
   out_6339358362171484689[256] = 0.0;
   out_6339358362171484689[257] = 0.0;
   out_6339358362171484689[258] = 0.0;
   out_6339358362171484689[259] = 0.0;
   out_6339358362171484689[260] = 0.0;
   out_6339358362171484689[261] = 0.0;
   out_6339358362171484689[262] = 0.0;
   out_6339358362171484689[263] = 0.0;
   out_6339358362171484689[264] = 0.0;
   out_6339358362171484689[265] = 0.0;
   out_6339358362171484689[266] = 1.0;
   out_6339358362171484689[267] = 0.0;
   out_6339358362171484689[268] = 0.0;
   out_6339358362171484689[269] = 0.0;
   out_6339358362171484689[270] = 0.0;
   out_6339358362171484689[271] = 0.0;
   out_6339358362171484689[272] = 0.0;
   out_6339358362171484689[273] = 0.0;
   out_6339358362171484689[274] = 0.0;
   out_6339358362171484689[275] = 0.0;
   out_6339358362171484689[276] = 0.0;
   out_6339358362171484689[277] = 0.0;
   out_6339358362171484689[278] = 0.0;
   out_6339358362171484689[279] = 0.0;
   out_6339358362171484689[280] = 0.0;
   out_6339358362171484689[281] = 0.0;
   out_6339358362171484689[282] = 0.0;
   out_6339358362171484689[283] = 0.0;
   out_6339358362171484689[284] = 0.0;
   out_6339358362171484689[285] = 1.0;
   out_6339358362171484689[286] = 0.0;
   out_6339358362171484689[287] = 0.0;
   out_6339358362171484689[288] = 0.0;
   out_6339358362171484689[289] = 0.0;
   out_6339358362171484689[290] = 0.0;
   out_6339358362171484689[291] = 0.0;
   out_6339358362171484689[292] = 0.0;
   out_6339358362171484689[293] = 0.0;
   out_6339358362171484689[294] = 0.0;
   out_6339358362171484689[295] = 0.0;
   out_6339358362171484689[296] = 0.0;
   out_6339358362171484689[297] = 0.0;
   out_6339358362171484689[298] = 0.0;
   out_6339358362171484689[299] = 0.0;
   out_6339358362171484689[300] = 0.0;
   out_6339358362171484689[301] = 0.0;
   out_6339358362171484689[302] = 0.0;
   out_6339358362171484689[303] = 0.0;
   out_6339358362171484689[304] = 1.0;
   out_6339358362171484689[305] = 0.0;
   out_6339358362171484689[306] = 0.0;
   out_6339358362171484689[307] = 0.0;
   out_6339358362171484689[308] = 0.0;
   out_6339358362171484689[309] = 0.0;
   out_6339358362171484689[310] = 0.0;
   out_6339358362171484689[311] = 0.0;
   out_6339358362171484689[312] = 0.0;
   out_6339358362171484689[313] = 0.0;
   out_6339358362171484689[314] = 0.0;
   out_6339358362171484689[315] = 0.0;
   out_6339358362171484689[316] = 0.0;
   out_6339358362171484689[317] = 0.0;
   out_6339358362171484689[318] = 0.0;
   out_6339358362171484689[319] = 0.0;
   out_6339358362171484689[320] = 0.0;
   out_6339358362171484689[321] = 0.0;
   out_6339358362171484689[322] = 0.0;
   out_6339358362171484689[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4513120832515025974) {
   out_4513120832515025974[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4513120832515025974[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4513120832515025974[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4513120832515025974[3] = dt*state[12] + state[3];
   out_4513120832515025974[4] = dt*state[13] + state[4];
   out_4513120832515025974[5] = dt*state[14] + state[5];
   out_4513120832515025974[6] = state[6];
   out_4513120832515025974[7] = state[7];
   out_4513120832515025974[8] = state[8];
   out_4513120832515025974[9] = state[9];
   out_4513120832515025974[10] = state[10];
   out_4513120832515025974[11] = state[11];
   out_4513120832515025974[12] = state[12];
   out_4513120832515025974[13] = state[13];
   out_4513120832515025974[14] = state[14];
   out_4513120832515025974[15] = state[15];
   out_4513120832515025974[16] = state[16];
   out_4513120832515025974[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6824255030541141050) {
   out_6824255030541141050[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6824255030541141050[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6824255030541141050[2] = 0;
   out_6824255030541141050[3] = 0;
   out_6824255030541141050[4] = 0;
   out_6824255030541141050[5] = 0;
   out_6824255030541141050[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6824255030541141050[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6824255030541141050[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6824255030541141050[9] = 0;
   out_6824255030541141050[10] = 0;
   out_6824255030541141050[11] = 0;
   out_6824255030541141050[12] = 0;
   out_6824255030541141050[13] = 0;
   out_6824255030541141050[14] = 0;
   out_6824255030541141050[15] = 0;
   out_6824255030541141050[16] = 0;
   out_6824255030541141050[17] = 0;
   out_6824255030541141050[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6824255030541141050[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6824255030541141050[20] = 0;
   out_6824255030541141050[21] = 0;
   out_6824255030541141050[22] = 0;
   out_6824255030541141050[23] = 0;
   out_6824255030541141050[24] = 0;
   out_6824255030541141050[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6824255030541141050[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6824255030541141050[27] = 0;
   out_6824255030541141050[28] = 0;
   out_6824255030541141050[29] = 0;
   out_6824255030541141050[30] = 0;
   out_6824255030541141050[31] = 0;
   out_6824255030541141050[32] = 0;
   out_6824255030541141050[33] = 0;
   out_6824255030541141050[34] = 0;
   out_6824255030541141050[35] = 0;
   out_6824255030541141050[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6824255030541141050[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6824255030541141050[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6824255030541141050[39] = 0;
   out_6824255030541141050[40] = 0;
   out_6824255030541141050[41] = 0;
   out_6824255030541141050[42] = 0;
   out_6824255030541141050[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6824255030541141050[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6824255030541141050[45] = 0;
   out_6824255030541141050[46] = 0;
   out_6824255030541141050[47] = 0;
   out_6824255030541141050[48] = 0;
   out_6824255030541141050[49] = 0;
   out_6824255030541141050[50] = 0;
   out_6824255030541141050[51] = 0;
   out_6824255030541141050[52] = 0;
   out_6824255030541141050[53] = 0;
   out_6824255030541141050[54] = 0;
   out_6824255030541141050[55] = 0;
   out_6824255030541141050[56] = 0;
   out_6824255030541141050[57] = 1;
   out_6824255030541141050[58] = 0;
   out_6824255030541141050[59] = 0;
   out_6824255030541141050[60] = 0;
   out_6824255030541141050[61] = 0;
   out_6824255030541141050[62] = 0;
   out_6824255030541141050[63] = 0;
   out_6824255030541141050[64] = 0;
   out_6824255030541141050[65] = 0;
   out_6824255030541141050[66] = dt;
   out_6824255030541141050[67] = 0;
   out_6824255030541141050[68] = 0;
   out_6824255030541141050[69] = 0;
   out_6824255030541141050[70] = 0;
   out_6824255030541141050[71] = 0;
   out_6824255030541141050[72] = 0;
   out_6824255030541141050[73] = 0;
   out_6824255030541141050[74] = 0;
   out_6824255030541141050[75] = 0;
   out_6824255030541141050[76] = 1;
   out_6824255030541141050[77] = 0;
   out_6824255030541141050[78] = 0;
   out_6824255030541141050[79] = 0;
   out_6824255030541141050[80] = 0;
   out_6824255030541141050[81] = 0;
   out_6824255030541141050[82] = 0;
   out_6824255030541141050[83] = 0;
   out_6824255030541141050[84] = 0;
   out_6824255030541141050[85] = dt;
   out_6824255030541141050[86] = 0;
   out_6824255030541141050[87] = 0;
   out_6824255030541141050[88] = 0;
   out_6824255030541141050[89] = 0;
   out_6824255030541141050[90] = 0;
   out_6824255030541141050[91] = 0;
   out_6824255030541141050[92] = 0;
   out_6824255030541141050[93] = 0;
   out_6824255030541141050[94] = 0;
   out_6824255030541141050[95] = 1;
   out_6824255030541141050[96] = 0;
   out_6824255030541141050[97] = 0;
   out_6824255030541141050[98] = 0;
   out_6824255030541141050[99] = 0;
   out_6824255030541141050[100] = 0;
   out_6824255030541141050[101] = 0;
   out_6824255030541141050[102] = 0;
   out_6824255030541141050[103] = 0;
   out_6824255030541141050[104] = dt;
   out_6824255030541141050[105] = 0;
   out_6824255030541141050[106] = 0;
   out_6824255030541141050[107] = 0;
   out_6824255030541141050[108] = 0;
   out_6824255030541141050[109] = 0;
   out_6824255030541141050[110] = 0;
   out_6824255030541141050[111] = 0;
   out_6824255030541141050[112] = 0;
   out_6824255030541141050[113] = 0;
   out_6824255030541141050[114] = 1;
   out_6824255030541141050[115] = 0;
   out_6824255030541141050[116] = 0;
   out_6824255030541141050[117] = 0;
   out_6824255030541141050[118] = 0;
   out_6824255030541141050[119] = 0;
   out_6824255030541141050[120] = 0;
   out_6824255030541141050[121] = 0;
   out_6824255030541141050[122] = 0;
   out_6824255030541141050[123] = 0;
   out_6824255030541141050[124] = 0;
   out_6824255030541141050[125] = 0;
   out_6824255030541141050[126] = 0;
   out_6824255030541141050[127] = 0;
   out_6824255030541141050[128] = 0;
   out_6824255030541141050[129] = 0;
   out_6824255030541141050[130] = 0;
   out_6824255030541141050[131] = 0;
   out_6824255030541141050[132] = 0;
   out_6824255030541141050[133] = 1;
   out_6824255030541141050[134] = 0;
   out_6824255030541141050[135] = 0;
   out_6824255030541141050[136] = 0;
   out_6824255030541141050[137] = 0;
   out_6824255030541141050[138] = 0;
   out_6824255030541141050[139] = 0;
   out_6824255030541141050[140] = 0;
   out_6824255030541141050[141] = 0;
   out_6824255030541141050[142] = 0;
   out_6824255030541141050[143] = 0;
   out_6824255030541141050[144] = 0;
   out_6824255030541141050[145] = 0;
   out_6824255030541141050[146] = 0;
   out_6824255030541141050[147] = 0;
   out_6824255030541141050[148] = 0;
   out_6824255030541141050[149] = 0;
   out_6824255030541141050[150] = 0;
   out_6824255030541141050[151] = 0;
   out_6824255030541141050[152] = 1;
   out_6824255030541141050[153] = 0;
   out_6824255030541141050[154] = 0;
   out_6824255030541141050[155] = 0;
   out_6824255030541141050[156] = 0;
   out_6824255030541141050[157] = 0;
   out_6824255030541141050[158] = 0;
   out_6824255030541141050[159] = 0;
   out_6824255030541141050[160] = 0;
   out_6824255030541141050[161] = 0;
   out_6824255030541141050[162] = 0;
   out_6824255030541141050[163] = 0;
   out_6824255030541141050[164] = 0;
   out_6824255030541141050[165] = 0;
   out_6824255030541141050[166] = 0;
   out_6824255030541141050[167] = 0;
   out_6824255030541141050[168] = 0;
   out_6824255030541141050[169] = 0;
   out_6824255030541141050[170] = 0;
   out_6824255030541141050[171] = 1;
   out_6824255030541141050[172] = 0;
   out_6824255030541141050[173] = 0;
   out_6824255030541141050[174] = 0;
   out_6824255030541141050[175] = 0;
   out_6824255030541141050[176] = 0;
   out_6824255030541141050[177] = 0;
   out_6824255030541141050[178] = 0;
   out_6824255030541141050[179] = 0;
   out_6824255030541141050[180] = 0;
   out_6824255030541141050[181] = 0;
   out_6824255030541141050[182] = 0;
   out_6824255030541141050[183] = 0;
   out_6824255030541141050[184] = 0;
   out_6824255030541141050[185] = 0;
   out_6824255030541141050[186] = 0;
   out_6824255030541141050[187] = 0;
   out_6824255030541141050[188] = 0;
   out_6824255030541141050[189] = 0;
   out_6824255030541141050[190] = 1;
   out_6824255030541141050[191] = 0;
   out_6824255030541141050[192] = 0;
   out_6824255030541141050[193] = 0;
   out_6824255030541141050[194] = 0;
   out_6824255030541141050[195] = 0;
   out_6824255030541141050[196] = 0;
   out_6824255030541141050[197] = 0;
   out_6824255030541141050[198] = 0;
   out_6824255030541141050[199] = 0;
   out_6824255030541141050[200] = 0;
   out_6824255030541141050[201] = 0;
   out_6824255030541141050[202] = 0;
   out_6824255030541141050[203] = 0;
   out_6824255030541141050[204] = 0;
   out_6824255030541141050[205] = 0;
   out_6824255030541141050[206] = 0;
   out_6824255030541141050[207] = 0;
   out_6824255030541141050[208] = 0;
   out_6824255030541141050[209] = 1;
   out_6824255030541141050[210] = 0;
   out_6824255030541141050[211] = 0;
   out_6824255030541141050[212] = 0;
   out_6824255030541141050[213] = 0;
   out_6824255030541141050[214] = 0;
   out_6824255030541141050[215] = 0;
   out_6824255030541141050[216] = 0;
   out_6824255030541141050[217] = 0;
   out_6824255030541141050[218] = 0;
   out_6824255030541141050[219] = 0;
   out_6824255030541141050[220] = 0;
   out_6824255030541141050[221] = 0;
   out_6824255030541141050[222] = 0;
   out_6824255030541141050[223] = 0;
   out_6824255030541141050[224] = 0;
   out_6824255030541141050[225] = 0;
   out_6824255030541141050[226] = 0;
   out_6824255030541141050[227] = 0;
   out_6824255030541141050[228] = 1;
   out_6824255030541141050[229] = 0;
   out_6824255030541141050[230] = 0;
   out_6824255030541141050[231] = 0;
   out_6824255030541141050[232] = 0;
   out_6824255030541141050[233] = 0;
   out_6824255030541141050[234] = 0;
   out_6824255030541141050[235] = 0;
   out_6824255030541141050[236] = 0;
   out_6824255030541141050[237] = 0;
   out_6824255030541141050[238] = 0;
   out_6824255030541141050[239] = 0;
   out_6824255030541141050[240] = 0;
   out_6824255030541141050[241] = 0;
   out_6824255030541141050[242] = 0;
   out_6824255030541141050[243] = 0;
   out_6824255030541141050[244] = 0;
   out_6824255030541141050[245] = 0;
   out_6824255030541141050[246] = 0;
   out_6824255030541141050[247] = 1;
   out_6824255030541141050[248] = 0;
   out_6824255030541141050[249] = 0;
   out_6824255030541141050[250] = 0;
   out_6824255030541141050[251] = 0;
   out_6824255030541141050[252] = 0;
   out_6824255030541141050[253] = 0;
   out_6824255030541141050[254] = 0;
   out_6824255030541141050[255] = 0;
   out_6824255030541141050[256] = 0;
   out_6824255030541141050[257] = 0;
   out_6824255030541141050[258] = 0;
   out_6824255030541141050[259] = 0;
   out_6824255030541141050[260] = 0;
   out_6824255030541141050[261] = 0;
   out_6824255030541141050[262] = 0;
   out_6824255030541141050[263] = 0;
   out_6824255030541141050[264] = 0;
   out_6824255030541141050[265] = 0;
   out_6824255030541141050[266] = 1;
   out_6824255030541141050[267] = 0;
   out_6824255030541141050[268] = 0;
   out_6824255030541141050[269] = 0;
   out_6824255030541141050[270] = 0;
   out_6824255030541141050[271] = 0;
   out_6824255030541141050[272] = 0;
   out_6824255030541141050[273] = 0;
   out_6824255030541141050[274] = 0;
   out_6824255030541141050[275] = 0;
   out_6824255030541141050[276] = 0;
   out_6824255030541141050[277] = 0;
   out_6824255030541141050[278] = 0;
   out_6824255030541141050[279] = 0;
   out_6824255030541141050[280] = 0;
   out_6824255030541141050[281] = 0;
   out_6824255030541141050[282] = 0;
   out_6824255030541141050[283] = 0;
   out_6824255030541141050[284] = 0;
   out_6824255030541141050[285] = 1;
   out_6824255030541141050[286] = 0;
   out_6824255030541141050[287] = 0;
   out_6824255030541141050[288] = 0;
   out_6824255030541141050[289] = 0;
   out_6824255030541141050[290] = 0;
   out_6824255030541141050[291] = 0;
   out_6824255030541141050[292] = 0;
   out_6824255030541141050[293] = 0;
   out_6824255030541141050[294] = 0;
   out_6824255030541141050[295] = 0;
   out_6824255030541141050[296] = 0;
   out_6824255030541141050[297] = 0;
   out_6824255030541141050[298] = 0;
   out_6824255030541141050[299] = 0;
   out_6824255030541141050[300] = 0;
   out_6824255030541141050[301] = 0;
   out_6824255030541141050[302] = 0;
   out_6824255030541141050[303] = 0;
   out_6824255030541141050[304] = 1;
   out_6824255030541141050[305] = 0;
   out_6824255030541141050[306] = 0;
   out_6824255030541141050[307] = 0;
   out_6824255030541141050[308] = 0;
   out_6824255030541141050[309] = 0;
   out_6824255030541141050[310] = 0;
   out_6824255030541141050[311] = 0;
   out_6824255030541141050[312] = 0;
   out_6824255030541141050[313] = 0;
   out_6824255030541141050[314] = 0;
   out_6824255030541141050[315] = 0;
   out_6824255030541141050[316] = 0;
   out_6824255030541141050[317] = 0;
   out_6824255030541141050[318] = 0;
   out_6824255030541141050[319] = 0;
   out_6824255030541141050[320] = 0;
   out_6824255030541141050[321] = 0;
   out_6824255030541141050[322] = 0;
   out_6824255030541141050[323] = 1;
}
void h_4(double *state, double *unused, double *out_634066535336441633) {
   out_634066535336441633[0] = state[6] + state[9];
   out_634066535336441633[1] = state[7] + state[10];
   out_634066535336441633[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8833163632747117674) {
   out_8833163632747117674[0] = 0;
   out_8833163632747117674[1] = 0;
   out_8833163632747117674[2] = 0;
   out_8833163632747117674[3] = 0;
   out_8833163632747117674[4] = 0;
   out_8833163632747117674[5] = 0;
   out_8833163632747117674[6] = 1;
   out_8833163632747117674[7] = 0;
   out_8833163632747117674[8] = 0;
   out_8833163632747117674[9] = 1;
   out_8833163632747117674[10] = 0;
   out_8833163632747117674[11] = 0;
   out_8833163632747117674[12] = 0;
   out_8833163632747117674[13] = 0;
   out_8833163632747117674[14] = 0;
   out_8833163632747117674[15] = 0;
   out_8833163632747117674[16] = 0;
   out_8833163632747117674[17] = 0;
   out_8833163632747117674[18] = 0;
   out_8833163632747117674[19] = 0;
   out_8833163632747117674[20] = 0;
   out_8833163632747117674[21] = 0;
   out_8833163632747117674[22] = 0;
   out_8833163632747117674[23] = 0;
   out_8833163632747117674[24] = 0;
   out_8833163632747117674[25] = 1;
   out_8833163632747117674[26] = 0;
   out_8833163632747117674[27] = 0;
   out_8833163632747117674[28] = 1;
   out_8833163632747117674[29] = 0;
   out_8833163632747117674[30] = 0;
   out_8833163632747117674[31] = 0;
   out_8833163632747117674[32] = 0;
   out_8833163632747117674[33] = 0;
   out_8833163632747117674[34] = 0;
   out_8833163632747117674[35] = 0;
   out_8833163632747117674[36] = 0;
   out_8833163632747117674[37] = 0;
   out_8833163632747117674[38] = 0;
   out_8833163632747117674[39] = 0;
   out_8833163632747117674[40] = 0;
   out_8833163632747117674[41] = 0;
   out_8833163632747117674[42] = 0;
   out_8833163632747117674[43] = 0;
   out_8833163632747117674[44] = 1;
   out_8833163632747117674[45] = 0;
   out_8833163632747117674[46] = 0;
   out_8833163632747117674[47] = 1;
   out_8833163632747117674[48] = 0;
   out_8833163632747117674[49] = 0;
   out_8833163632747117674[50] = 0;
   out_8833163632747117674[51] = 0;
   out_8833163632747117674[52] = 0;
   out_8833163632747117674[53] = 0;
}
void h_10(double *state, double *unused, double *out_6697639128282696940) {
   out_6697639128282696940[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_6697639128282696940[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_6697639128282696940[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5834408245444951106) {
   out_5834408245444951106[0] = 0;
   out_5834408245444951106[1] = 9.8100000000000005*cos(state[1]);
   out_5834408245444951106[2] = 0;
   out_5834408245444951106[3] = 0;
   out_5834408245444951106[4] = -state[8];
   out_5834408245444951106[5] = state[7];
   out_5834408245444951106[6] = 0;
   out_5834408245444951106[7] = state[5];
   out_5834408245444951106[8] = -state[4];
   out_5834408245444951106[9] = 0;
   out_5834408245444951106[10] = 0;
   out_5834408245444951106[11] = 0;
   out_5834408245444951106[12] = 1;
   out_5834408245444951106[13] = 0;
   out_5834408245444951106[14] = 0;
   out_5834408245444951106[15] = 1;
   out_5834408245444951106[16] = 0;
   out_5834408245444951106[17] = 0;
   out_5834408245444951106[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5834408245444951106[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5834408245444951106[20] = 0;
   out_5834408245444951106[21] = state[8];
   out_5834408245444951106[22] = 0;
   out_5834408245444951106[23] = -state[6];
   out_5834408245444951106[24] = -state[5];
   out_5834408245444951106[25] = 0;
   out_5834408245444951106[26] = state[3];
   out_5834408245444951106[27] = 0;
   out_5834408245444951106[28] = 0;
   out_5834408245444951106[29] = 0;
   out_5834408245444951106[30] = 0;
   out_5834408245444951106[31] = 1;
   out_5834408245444951106[32] = 0;
   out_5834408245444951106[33] = 0;
   out_5834408245444951106[34] = 1;
   out_5834408245444951106[35] = 0;
   out_5834408245444951106[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5834408245444951106[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5834408245444951106[38] = 0;
   out_5834408245444951106[39] = -state[7];
   out_5834408245444951106[40] = state[6];
   out_5834408245444951106[41] = 0;
   out_5834408245444951106[42] = state[4];
   out_5834408245444951106[43] = -state[3];
   out_5834408245444951106[44] = 0;
   out_5834408245444951106[45] = 0;
   out_5834408245444951106[46] = 0;
   out_5834408245444951106[47] = 0;
   out_5834408245444951106[48] = 0;
   out_5834408245444951106[49] = 0;
   out_5834408245444951106[50] = 1;
   out_5834408245444951106[51] = 0;
   out_5834408245444951106[52] = 0;
   out_5834408245444951106[53] = 1;
}
void h_13(double *state, double *unused, double *out_2024418455697663562) {
   out_2024418455697663562[0] = state[3];
   out_2024418455697663562[1] = state[4];
   out_2024418455697663562[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6401306615630101141) {
   out_6401306615630101141[0] = 0;
   out_6401306615630101141[1] = 0;
   out_6401306615630101141[2] = 0;
   out_6401306615630101141[3] = 1;
   out_6401306615630101141[4] = 0;
   out_6401306615630101141[5] = 0;
   out_6401306615630101141[6] = 0;
   out_6401306615630101141[7] = 0;
   out_6401306615630101141[8] = 0;
   out_6401306615630101141[9] = 0;
   out_6401306615630101141[10] = 0;
   out_6401306615630101141[11] = 0;
   out_6401306615630101141[12] = 0;
   out_6401306615630101141[13] = 0;
   out_6401306615630101141[14] = 0;
   out_6401306615630101141[15] = 0;
   out_6401306615630101141[16] = 0;
   out_6401306615630101141[17] = 0;
   out_6401306615630101141[18] = 0;
   out_6401306615630101141[19] = 0;
   out_6401306615630101141[20] = 0;
   out_6401306615630101141[21] = 0;
   out_6401306615630101141[22] = 1;
   out_6401306615630101141[23] = 0;
   out_6401306615630101141[24] = 0;
   out_6401306615630101141[25] = 0;
   out_6401306615630101141[26] = 0;
   out_6401306615630101141[27] = 0;
   out_6401306615630101141[28] = 0;
   out_6401306615630101141[29] = 0;
   out_6401306615630101141[30] = 0;
   out_6401306615630101141[31] = 0;
   out_6401306615630101141[32] = 0;
   out_6401306615630101141[33] = 0;
   out_6401306615630101141[34] = 0;
   out_6401306615630101141[35] = 0;
   out_6401306615630101141[36] = 0;
   out_6401306615630101141[37] = 0;
   out_6401306615630101141[38] = 0;
   out_6401306615630101141[39] = 0;
   out_6401306615630101141[40] = 0;
   out_6401306615630101141[41] = 1;
   out_6401306615630101141[42] = 0;
   out_6401306615630101141[43] = 0;
   out_6401306615630101141[44] = 0;
   out_6401306615630101141[45] = 0;
   out_6401306615630101141[46] = 0;
   out_6401306615630101141[47] = 0;
   out_6401306615630101141[48] = 0;
   out_6401306615630101141[49] = 0;
   out_6401306615630101141[50] = 0;
   out_6401306615630101141[51] = 0;
   out_6401306615630101141[52] = 0;
   out_6401306615630101141[53] = 0;
}
void h_14(double *state, double *unused, double *out_7328828287226735843) {
   out_7328828287226735843[0] = state[6];
   out_7328828287226735843[1] = state[7];
   out_7328828287226735843[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5650339584622949413) {
   out_5650339584622949413[0] = 0;
   out_5650339584622949413[1] = 0;
   out_5650339584622949413[2] = 0;
   out_5650339584622949413[3] = 0;
   out_5650339584622949413[4] = 0;
   out_5650339584622949413[5] = 0;
   out_5650339584622949413[6] = 1;
   out_5650339584622949413[7] = 0;
   out_5650339584622949413[8] = 0;
   out_5650339584622949413[9] = 0;
   out_5650339584622949413[10] = 0;
   out_5650339584622949413[11] = 0;
   out_5650339584622949413[12] = 0;
   out_5650339584622949413[13] = 0;
   out_5650339584622949413[14] = 0;
   out_5650339584622949413[15] = 0;
   out_5650339584622949413[16] = 0;
   out_5650339584622949413[17] = 0;
   out_5650339584622949413[18] = 0;
   out_5650339584622949413[19] = 0;
   out_5650339584622949413[20] = 0;
   out_5650339584622949413[21] = 0;
   out_5650339584622949413[22] = 0;
   out_5650339584622949413[23] = 0;
   out_5650339584622949413[24] = 0;
   out_5650339584622949413[25] = 1;
   out_5650339584622949413[26] = 0;
   out_5650339584622949413[27] = 0;
   out_5650339584622949413[28] = 0;
   out_5650339584622949413[29] = 0;
   out_5650339584622949413[30] = 0;
   out_5650339584622949413[31] = 0;
   out_5650339584622949413[32] = 0;
   out_5650339584622949413[33] = 0;
   out_5650339584622949413[34] = 0;
   out_5650339584622949413[35] = 0;
   out_5650339584622949413[36] = 0;
   out_5650339584622949413[37] = 0;
   out_5650339584622949413[38] = 0;
   out_5650339584622949413[39] = 0;
   out_5650339584622949413[40] = 0;
   out_5650339584622949413[41] = 0;
   out_5650339584622949413[42] = 0;
   out_5650339584622949413[43] = 0;
   out_5650339584622949413[44] = 1;
   out_5650339584622949413[45] = 0;
   out_5650339584622949413[46] = 0;
   out_5650339584622949413[47] = 0;
   out_5650339584622949413[48] = 0;
   out_5650339584622949413[49] = 0;
   out_5650339584622949413[50] = 0;
   out_5650339584622949413[51] = 0;
   out_5650339584622949413[52] = 0;
   out_5650339584622949413[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_6620113396710350830) {
  err_fun(nom_x, delta_x, out_6620113396710350830);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3901415459874751196) {
  inv_err_fun(nom_x, true_x, out_3901415459874751196);
}
void pose_H_mod_fun(double *state, double *out_6339358362171484689) {
  H_mod_fun(state, out_6339358362171484689);
}
void pose_f_fun(double *state, double dt, double *out_4513120832515025974) {
  f_fun(state,  dt, out_4513120832515025974);
}
void pose_F_fun(double *state, double dt, double *out_6824255030541141050) {
  F_fun(state,  dt, out_6824255030541141050);
}
void pose_h_4(double *state, double *unused, double *out_634066535336441633) {
  h_4(state, unused, out_634066535336441633);
}
void pose_H_4(double *state, double *unused, double *out_8833163632747117674) {
  H_4(state, unused, out_8833163632747117674);
}
void pose_h_10(double *state, double *unused, double *out_6697639128282696940) {
  h_10(state, unused, out_6697639128282696940);
}
void pose_H_10(double *state, double *unused, double *out_5834408245444951106) {
  H_10(state, unused, out_5834408245444951106);
}
void pose_h_13(double *state, double *unused, double *out_2024418455697663562) {
  h_13(state, unused, out_2024418455697663562);
}
void pose_H_13(double *state, double *unused, double *out_6401306615630101141) {
  H_13(state, unused, out_6401306615630101141);
}
void pose_h_14(double *state, double *unused, double *out_7328828287226735843) {
  h_14(state, unused, out_7328828287226735843);
}
void pose_H_14(double *state, double *unused, double *out_5650339584622949413) {
  H_14(state, unused, out_5650339584622949413);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
