/*
 * File: controllers.c
 *
 * Code generated for Simulink model 'controllers'.
 *
 * Model version                  : 1.43
 * Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
 * C/C++ source code generated on : Sun Jun 19 13:38:35 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "controllers.h"
#include "controllers_private.h"

/* Exported block signals */
real_T setPoint;                       /* '<Root>/Setpoint' */
real_T mode;                           /* '<Root>/Mode' */
real_T processVar;                     /* '<Root>/PV' */
real_T Udk;                            /* '<Root>/Multiport Switch' */
real_T xi;                             /* '<S53>/xi' */
real_T wn;                             /* '<S53>/wn' */

/* Block signals (default storage) */
BlockIO_controllers controllers_B;

/* Block states (default storage) */
D_Work_controllers controllers_DWork;

/* Real-time model */
RT_MODEL_controllers controllers_M_;
RT_MODEL_controllers *const controllers_M = &controllers_M_;

/* Forward declaration for local functions */
static real_T controllers_eml_rand_mt19937ar(uint32_T state[625]);
static void controllers_rand(real_T r[4]);

/* Function for MATLAB Function: '<S52>/MATLAB Function' */
static real_T controllers_eml_rand_mt19937ar(uint32_T state[625])
{
  real_T r;
  uint32_T u[2];
  uint32_T mti;
  uint32_T y;
  int32_T kk;
  int32_T k;
  boolean_T b_isvalid;
  int32_T exitg1;
  boolean_T exitg2;

  /* ========================= COPYRIGHT NOTICE ============================ */
  /*  This is a uniform (0,1) pseudorandom number generator based on:        */
  /*                                                                         */
  /*  A C-program for MT19937, with initialization improved 2002/1/26.       */
  /*  Coded by Takuji Nishimura and Makoto Matsumoto.                        */
  /*                                                                         */
  /*  Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,      */
  /*  All rights reserved.                                                   */
  /*                                                                         */
  /*  Redistribution and use in source and binary forms, with or without     */
  /*  modification, are permitted provided that the following conditions     */
  /*  are met:                                                               */
  /*                                                                         */
  /*    1. Redistributions of source code must retain the above copyright    */
  /*       notice, this list of conditions and the following disclaimer.     */
  /*                                                                         */
  /*    2. Redistributions in binary form must reproduce the above copyright */
  /*       notice, this list of conditions and the following disclaimer      */
  /*       in the documentation and/or other materials provided with the     */
  /*       distribution.                                                     */
  /*                                                                         */
  /*    3. The names of its contributors may not be used to endorse or       */
  /*       promote products derived from this software without specific      */
  /*       prior written permission.                                         */
  /*                                                                         */
  /*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
  /*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
  /*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
  /*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT  */
  /*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
  /*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
  /*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
  /*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
  /*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
  /*  (INCLUDING  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE */
  /*  OF THIS  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  */
  /*                                                                         */
  /* =============================   END   ================================= */
  do {
    exitg1 = 0;
    for (k = 0; k < 2; k++) {
      mti = state[624] + 1U;
      if (mti >= 625U) {
        for (kk = 0; kk < 227; kk++) {
          y = (state[1 + kk] & 2147483647U) | (state[kk] & 2147483648U);
          if ((y & 1U) == 0U) {
            y >>= 1U;
          } else {
            y = y >> 1U ^ 2567483615U;
          }

          state[kk] = state[kk + 397] ^ y;
        }

        for (kk = 0; kk < 396; kk++) {
          y = (state[kk + 227] & 2147483648U) | (state[228 + kk] & 2147483647U);
          if ((y & 1U) == 0U) {
            y >>= 1U;
          } else {
            y = y >> 1U ^ 2567483615U;
          }

          state[kk + 227] = state[kk] ^ y;
        }

        y = (state[623] & 2147483648U) | (state[0] & 2147483647U);
        if ((y & 1U) == 0U) {
          y >>= 1U;
        } else {
          y = y >> 1U ^ 2567483615U;
        }

        state[623] = state[396] ^ y;
        mti = 1U;
      }

      y = state[(int32_T)mti - 1];
      state[624] = mti;
      y ^= y >> 11U;
      y ^= y << 7U & 2636928640U;
      y ^= y << 15U & 4022730752U;
      u[k] = y >> 18U ^ y;
    }

    r = ((real_T)(u[0] >> 5U) * 6.7108864E+7 + (real_T)(u[1] >> 6U)) *
      1.1102230246251565E-16;
    if (r == 0.0) {
      if ((state[624] >= 1U) && (state[624] < 625U)) {
        b_isvalid = false;
        k = 1;
        exitg2 = false;
        while ((!exitg2) && (k < 625)) {
          if (state[k - 1] == 0U) {
            k++;
          } else {
            b_isvalid = true;
            exitg2 = true;
          }
        }
      } else {
        b_isvalid = false;
      }

      if (!b_isvalid) {
        mti = 5489U;
        state[0] = 5489U;
        for (k = 0; k < 623; k++) {
          mti = ((mti >> 30U ^ mti) * 1812433253U + k) + 1U;
          state[k + 1] = mti;
        }

        state[624] = 624U;
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return r;
}

/* Function for MATLAB Function: '<S52>/MATLAB Function' */
static void controllers_rand(real_T r[4])
{
  uint32_T b_r;
  int32_T hi;
  uint32_T test2;
  if (controllers_DWork.method == 4U) {
    hi = (int32_T)(controllers_DWork.state / 127773U);
    b_r = (controllers_DWork.state - hi * 127773U) * 16807U;
    test2 = 2836U * hi;
    if (b_r < test2) {
      b_r = ~(test2 - b_r) & 2147483647U;
    } else {
      b_r -= test2;
    }

    controllers_DWork.state = b_r;
    r[0] = (real_T)b_r * 4.6566128752457969E-10;
    hi = (int32_T)(controllers_DWork.state / 127773U);
    b_r = (controllers_DWork.state - hi * 127773U) * 16807U;
    test2 = 2836U * hi;
    if (b_r < test2) {
      b_r = ~(test2 - b_r) & 2147483647U;
    } else {
      b_r -= test2;
    }

    controllers_DWork.state = b_r;
    r[1] = (real_T)b_r * 4.6566128752457969E-10;
    hi = (int32_T)(controllers_DWork.state / 127773U);
    b_r = (controllers_DWork.state - hi * 127773U) * 16807U;
    test2 = 2836U * hi;
    if (b_r < test2) {
      b_r = ~(test2 - b_r) & 2147483647U;
    } else {
      b_r -= test2;
    }

    controllers_DWork.state = b_r;
    r[2] = (real_T)b_r * 4.6566128752457969E-10;
    hi = (int32_T)(controllers_DWork.state / 127773U);
    b_r = (controllers_DWork.state - hi * 127773U) * 16807U;
    test2 = 2836U * hi;
    if (b_r < test2) {
      b_r = ~(test2 - b_r) & 2147483647U;
    } else {
      b_r -= test2;
    }

    controllers_DWork.state = b_r;
    r[3] = (real_T)b_r * 4.6566128752457969E-10;
  } else if (controllers_DWork.method == 5U) {
    b_r = 69069U * controllers_DWork.state_i[0] + 1234567U;
    test2 = controllers_DWork.state_i[1] << 13 ^ controllers_DWork.state_i[1];
    test2 ^= test2 >> 17;
    test2 ^= test2 << 5;
    controllers_DWork.state_i[0] = b_r;
    controllers_DWork.state_i[1] = test2;
    r[0] = (real_T)(b_r + test2) * 2.328306436538696E-10;
    b_r = 69069U * controllers_DWork.state_i[0] + 1234567U;
    test2 = controllers_DWork.state_i[1] << 13 ^ controllers_DWork.state_i[1];
    test2 ^= test2 >> 17;
    test2 ^= test2 << 5;
    controllers_DWork.state_i[0] = b_r;
    controllers_DWork.state_i[1] = test2;
    r[1] = (real_T)(b_r + test2) * 2.328306436538696E-10;
    b_r = 69069U * controllers_DWork.state_i[0] + 1234567U;
    test2 = controllers_DWork.state_i[1] << 13 ^ controllers_DWork.state_i[1];
    test2 ^= test2 >> 17;
    test2 ^= test2 << 5;
    controllers_DWork.state_i[0] = b_r;
    controllers_DWork.state_i[1] = test2;
    r[2] = (real_T)(b_r + test2) * 2.328306436538696E-10;
    b_r = 69069U * controllers_DWork.state_i[0] + 1234567U;
    test2 = controllers_DWork.state_i[1] << 13 ^ controllers_DWork.state_i[1];
    test2 ^= test2 >> 17;
    test2 ^= test2 << 5;
    controllers_DWork.state_i[0] = b_r;
    controllers_DWork.state_i[1] = test2;
    r[3] = (real_T)(b_r + test2) * 2.328306436538696E-10;
  } else {
    if (!controllers_DWork.state_not_empty) {
      memset(&controllers_DWork.state_b[0], 0, 625U * sizeof(uint32_T));
      b_r = 5489U;
      controllers_DWork.state_b[0] = 5489U;
      for (hi = 0; hi < 623; hi++) {
        b_r = ((b_r >> 30U ^ b_r) * 1812433253U + hi) + 1U;
        controllers_DWork.state_b[hi + 1] = b_r;
      }

      controllers_DWork.state_b[624] = 624U;
      controllers_DWork.state_not_empty = true;
    }

    r[0] = controllers_eml_rand_mt19937ar(controllers_DWork.state_b);
    r[1] = controllers_eml_rand_mt19937ar(controllers_DWork.state_b);
    r[2] = controllers_eml_rand_mt19937ar(controllers_DWork.state_b);
    r[3] = controllers_eml_rand_mt19937ar(controllers_DWork.state_b);
  }
}

/* Model step function */
void controllers_step(void)
{
  real_T phi[4];
  real_T ek;
  static const int16_T b[16] = { 10000, 0, 0, 0, 0, 10000, 0, 0, 0, 0, 10000, 0,
    0, 0, 0, 10000 };

  real_T d1;
  real_T q2;
  real_T b_gamma;
  real_T rtb_DiscreteTransferFcn;
  real_T rtb_Sum;
  real_T rtb_FilterCoefficient;
  real_T rtb_e1;
  real_T rtb_u1;
  real_T Lk[16];
  real_T tmp[16];
  int32_T i;
  int32_T phi_tmp;
  int32_T tmp_0;
  int32_T tmp_1;

  /* DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn' */
  rtb_DiscreteTransferFcn = controllers_P.DiscreteTransferFcn_NumCoef *
    controllers_DWork.DiscreteTransferFcn_states;

  /* Outputs for Enabled SubSystem: '<Root>/PID Controller' incorporates:
   *  EnablePort: '<S5>/Enable'
   */
  /* RelationalOperator: '<S1>/Compare' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/Mode'
   */
  if (mode == controllers_P.CompareToConstant_const) {
    /* Sum: '<S5>/Sum' incorporates:
     *  Inport: '<Root>/PV'
     */
    rtb_Sum = rtb_DiscreteTransferFcn - processVar;

    /* Gain: '<S40>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S32>/Filter'
     *  Gain: '<S31>/Derivative Gain'
     *  Sum: '<S32>/SumD'
     *  Sum: '<S5>/Sum'
     */
    rtb_FilterCoefficient = (controllers_P.DiscretePIDController_D * rtb_Sum -
      controllers_DWork.Filter_DSTATE) * controllers_P.DiscretePIDController_N;

    /* Sum: '<S46>/Sum' incorporates:
     *  DiscreteIntegrator: '<S37>/Integrator'
     *  Gain: '<S42>/Proportional Gain'
     *  Sum: '<S5>/Sum'
     */
    ek = (controllers_P.DiscretePIDController_P * rtb_Sum +
          controllers_DWork.Integrator_DSTATE) + rtb_FilterCoefficient;

    /* Saturate: '<S5>/Saturation' */
    if (ek > controllers_P.Saturation_UpperSat_c) {
      controllers_B.Saturation_a = controllers_P.Saturation_UpperSat_c;
    } else if (ek < controllers_P.Saturation_LowerSat_l) {
      controllers_B.Saturation_a = controllers_P.Saturation_LowerSat_l;
    } else {
      controllers_B.Saturation_a = ek;
    }

    /* End of Saturate: '<S5>/Saturation' */

    /* Update for DiscreteIntegrator: '<S32>/Filter' */
    controllers_DWork.Filter_DSTATE += controllers_P.Filter_gainval *
      rtb_FilterCoefficient;

    /* Update for DiscreteIntegrator: '<S37>/Integrator' incorporates:
     *  Gain: '<S34>/Integral Gain'
     *  Sum: '<S5>/Sum'
     */
    controllers_DWork.Integrator_DSTATE += controllers_P.DiscretePIDController_I
      * rtb_Sum * controllers_P.Integrator_gainval;
  }

  /* End of RelationalOperator: '<S1>/Compare' */
  /* End of Outputs for SubSystem: '<Root>/PID Controller' */

  /* Outputs for Enabled SubSystem: '<Root>/STR Controller' incorporates:
   *  EnablePort: '<S6>/Enable'
   */
  /* RelationalOperator: '<S2>/Compare' incorporates:
   *  Constant: '<S2>/Constant'
   *  Constant: '<S53>/wn'
   *  Constant: '<S53>/xi'
   *  Inport: '<Root>/Mode'
   */
  if (mode == controllers_P.CompareToConstant1_const) {
    /* UnitDelay: '<S52>/Unit Delay' */
    rtb_Sum = controllers_DWork.UnitDelay_DSTATE_e;

    /* UnitDelay: '<S52>/Unit Delay2' */
    rtb_FilterCoefficient = controllers_DWork.UnitDelay2_DSTATE;

    /* MATLAB Function: '<S52>/MATLAB Function' incorporates:
     *  Inport: '<Root>/PV'
     *  UnitDelay: '<S52>/Unit Delay'
     *  UnitDelay: '<S52>/Unit Delay1'
     *  UnitDelay: '<S52>/Unit Delay2'
     *  UnitDelay: '<S52>/Unit Delay3'
     */
    /* MATLAB Function 'STR Controller/Param Estimation/MATLAB Function': '<S54>:1' */
    /* '<S54>:1:6' */
    if (!controllers_DWork.theta_not_empty) {
      /* '<S54>:1:4' */
      /* '<S54>:1:5' */
      controllers_rand(controllers_DWork.theta);
      controllers_DWork.theta_not_empty = true;

      /* '<S54>:1:6' */
      for (i = 0; i < 16; i++) {
        controllers_DWork.P[i] = b[i];
      }
    }

    /* '<S54>:1:9' */
    /* '<S54>:1:11' */
    phi[0] = -controllers_DWork.UnitDelay_DSTATE_e;
    phi[1] = -controllers_DWork.UnitDelay3_DSTATE;
    phi[2] = controllers_DWork.UnitDelay2_DSTATE;
    phi[3] = controllers_DWork.UnitDelay1_DSTATE;

    /* '<S54>:1:13' */
    ek = 0.0;
    for (i = 0; i < 4; i++) {
      phi_tmp = i << 2;
      rtb_e1 = controllers_DWork.P[phi_tmp + 3] *
        controllers_DWork.UnitDelay1_DSTATE + (controllers_DWork.P[phi_tmp + 2] *
        controllers_DWork.UnitDelay2_DSTATE + (controllers_DWork.P[phi_tmp + 1] *
        -controllers_DWork.UnitDelay3_DSTATE + controllers_DWork.P[phi_tmp] *
        -controllers_DWork.UnitDelay_DSTATE_e));
      ek += rtb_e1 * phi[i];
    }

    /* '<S54>:1:14' */
    for (i = 0; i < 4; i++) {
      rtb_e1 = (((controllers_DWork.P[i + 4] *
                  -controllers_DWork.UnitDelay3_DSTATE + controllers_DWork.P[i] *
                  -controllers_DWork.UnitDelay_DSTATE_e) + controllers_DWork.P[i
                 + 8] * controllers_DWork.UnitDelay2_DSTATE) +
                controllers_DWork.P[i + 12] *
                controllers_DWork.UnitDelay1_DSTATE) / (0.995 + ek);
      Lk[i] = rtb_e1 * -controllers_DWork.UnitDelay_DSTATE_e;
      Lk[i + 4] = rtb_e1 * -controllers_DWork.UnitDelay3_DSTATE;
      Lk[i + 8] = rtb_e1 * controllers_DWork.UnitDelay2_DSTATE;
      Lk[i + 12] = rtb_e1 * controllers_DWork.UnitDelay1_DSTATE;
      for (phi_tmp = 0; phi_tmp < 4; phi_tmp++) {
        tmp_0 = phi_tmp << 2;
        tmp_1 = tmp_0 + i;
        tmp[tmp_1] = controllers_DWork.P[tmp_1] - (((controllers_DWork.P[tmp_0 +
          1] * Lk[i + 4] + controllers_DWork.P[tmp_0] * Lk[i]) +
          controllers_DWork.P[tmp_0 + 2] * Lk[i + 8]) +
          controllers_DWork.P[tmp_0 + 3] * Lk[i + 12]);
      }

      phi[i] = rtb_e1;
    }

    for (i = 0; i < 16; i++) {
      controllers_DWork.P[i] = 1.0050251256281406 * tmp[i];
    }

    /* '<S54>:1:15' */
    ek = processVar - (((-controllers_DWork.UnitDelay_DSTATE_e *
                         controllers_DWork.theta[0] +
                         -controllers_DWork.UnitDelay3_DSTATE *
                         controllers_DWork.theta[1]) +
                        controllers_DWork.UnitDelay2_DSTATE *
                        controllers_DWork.theta[2]) +
                       controllers_DWork.UnitDelay1_DSTATE *
                       controllers_DWork.theta[3]);

    /* '<S54>:1:16' */
    controllers_DWork.theta[0] += phi[0] * ek;
    controllers_DWork.theta[1] += phi[1] * ek;
    controllers_DWork.theta[2] += phi[2] * ek;
    controllers_DWork.theta[3] += phi[3] * ek;

    /* Sum: '<S53>/Sum' incorporates:
     *  Inport: '<Root>/PV'
     */
    /* '<S54>:1:18' */
    ek = rtb_DiscreteTransferFcn - processVar;

    /* UnitDelay: '<S53>/Unit Delay' */
    rtb_e1 = controllers_DWork.UnitDelay_DSTATE_j;

    /* UnitDelay: '<S53>/Unit Delay2' */
    rtb_u1 = controllers_DWork.UnitDelay2_DSTATE_f;
    xi = controllers_P.xi_Value;
    wn = controllers_P.wn_Value;

    /* MATLAB Function: '<S53>/MATLAB Function' incorporates:
     *  Constant: '<S53>/wn'
     *  Constant: '<S53>/xi'
     *  MATLAB Function: '<S52>/MATLAB Function'
     *  Sum: '<S53>/Sum'
     *  UnitDelay: '<S53>/Unit Delay'
     *  UnitDelay: '<S53>/Unit Delay1'
     *  UnitDelay: '<S53>/Unit Delay2'
     *  UnitDelay: '<S53>/Unit Delay3'
     */
    /* MATLAB Function 'STR Controller/Self-tuning Regulator  /MATLAB Function': '<S55>:1' */
    /* '<S55>:1:2' */
    /* '<S55>:1:6' */
    /* '<S55>:1:7' */
    /* '<S55>:1:8' */
    /* '<S55>:1:9' */
    if (xi < 1.0) {
      /* '<S55>:1:11' */
      /* '<S55>:1:12' */
      d1 = exp(-xi * wn * 0.005) * -2.0 * cos(sqrt(1.0 - xi * xi) * (wn * 0.005));
    } else {
      /* '<S55>:1:14' */
      d1 = exp(-xi * wn * 0.005) * -2.0 * cosh(sqrt(xi * xi - 1.0) * (wn * 0.005));
    }

    /* '<S55>:1:16' */
    /* '<S55>:1:17' */
    /* '<S55>:1:18' */
    /* '<S55>:1:19' */
    q2 = controllers_DWork.theta[1] * controllers_DWork.theta[2];
    b_gamma = controllers_DWork.theta[2] + controllers_DWork.theta[3];
    q2 = (((exp(-2.0 * xi * wn * 0.005) * controllers_DWork.theta[2] -
            controllers_DWork.theta[3] * d1) - controllers_DWork.theta[3]) *
          controllers_DWork.theta[3] + (controllers_DWork.theta[0] *
           controllers_DWork.theta[3] - q2) * b_gamma) *
      controllers_DWork.theta[1] / (((controllers_DWork.theta[0] *
      controllers_DWork.theta[2] * controllers_DWork.theta[3] - q2 *
      controllers_DWork.theta[2]) - controllers_DWork.theta[3] *
      controllers_DWork.theta[3]) * b_gamma);

    /* '<S55>:1:20' */
    b_gamma = q2 * controllers_DWork.theta[3] / controllers_DWork.theta[1];

    /* '<S55>:1:21' */
    /* '<S55>:1:22' */
    /* '<S55>:1:24' */
    d1 = ((((controllers_DWork.theta[1] / controllers_DWork.theta[3] -
             ((controllers_DWork.theta[2] / controllers_DWork.theta[3] -
               controllers_DWork.theta[0] / controllers_DWork.theta[1]) + 1.0) *
             q2) * controllers_DWork.UnitDelay_DSTATE_j + (((d1 + 1.0) -
              controllers_DWork.theta[0]) - b_gamma) / controllers_DWork.theta[2]
            * ek) + q2 * controllers_DWork.UnitDelay1_DSTATE_c) + (1.0 - b_gamma)
          * controllers_DWork.UnitDelay2_DSTATE_f) + b_gamma *
      controllers_DWork.UnitDelay3_DSTATE_o;

    /* End of MATLAB Function: '<S53>/MATLAB Function' */

    /* Saturate: '<S53>/Saturation' */
    if (d1 > controllers_P.Saturation_UpperSat_i) {
      q2 = controllers_P.Saturation_UpperSat_i;
    } else if (d1 < controllers_P.Saturation_LowerSat_a) {
      q2 = controllers_P.Saturation_LowerSat_a;
    } else {
      q2 = d1;
    }

    /* End of Saturate: '<S53>/Saturation' */

    /* Saturate: '<S6>/Saturation' */
    if (q2 > controllers_P.Saturation_UpperSat_d) {
      controllers_B.Saturation = controllers_P.Saturation_UpperSat_d;
    } else if (q2 < controllers_P.Saturation_LowerSat_b) {
      controllers_B.Saturation = controllers_P.Saturation_LowerSat_b;
    } else {
      controllers_B.Saturation = q2;
    }

    /* End of Saturate: '<S6>/Saturation' */

    /* Update for UnitDelay: '<S52>/Unit Delay' incorporates:
     *  Inport: '<Root>/PV'
     */
    controllers_DWork.UnitDelay_DSTATE_e = processVar;

    /* Update for UnitDelay: '<S52>/Unit Delay3' */
    controllers_DWork.UnitDelay3_DSTATE = rtb_Sum;

    /* Update for UnitDelay: '<S52>/Unit Delay2' */
    controllers_DWork.UnitDelay2_DSTATE = q2;

    /* Update for UnitDelay: '<S52>/Unit Delay1' */
    controllers_DWork.UnitDelay1_DSTATE = rtb_FilterCoefficient;

    /* Update for UnitDelay: '<S53>/Unit Delay' incorporates:
     *  Sum: '<S53>/Sum'
     */
    controllers_DWork.UnitDelay_DSTATE_j = ek;

    /* Update for UnitDelay: '<S53>/Unit Delay1' */
    controllers_DWork.UnitDelay1_DSTATE_c = rtb_e1;

    /* Update for UnitDelay: '<S53>/Unit Delay2' */
    controllers_DWork.UnitDelay2_DSTATE_f = d1;

    /* Update for UnitDelay: '<S53>/Unit Delay3' */
    controllers_DWork.UnitDelay3_DSTATE_o = rtb_u1;
  }

  /* End of RelationalOperator: '<S2>/Compare' */
  /* End of Outputs for SubSystem: '<Root>/STR Controller' */

  /* Outputs for Enabled SubSystem: '<Root>/LQR Controller' incorporates:
   *  EnablePort: '<S4>/Enable'
   */
  /* RelationalOperator: '<S3>/Compare' incorporates:
   *  Constant: '<S3>/Constant'
   *  Inport: '<Root>/Mode'
   */
  if (mode == controllers_P.CompareToConstant2_const) {
    /* Sum: '<S4>/Add' incorporates:
     *  Gain: '<S4>/K1'
     *  Gain: '<S4>/K2'
     *  Inport: '<Root>/PV'
     *  Sum: '<S4>/Subtract'
     *  UnitDelay: '<Root>/Unit Delay'
     */
    ek = (rtb_DiscreteTransferFcn - processVar) * controllers_P.K1_Gain +
      controllers_P.K2_Gain * controllers_DWork.UnitDelay_DSTATE;

    /* Saturate: '<S4>/Saturation' */
    if (ek > controllers_P.Saturation_UpperSat) {
      controllers_B.Saturation_e = controllers_P.Saturation_UpperSat;
    } else if (ek < controllers_P.Saturation_LowerSat) {
      controllers_B.Saturation_e = controllers_P.Saturation_LowerSat;
    } else {
      controllers_B.Saturation_e = ek;
    }

    /* End of Saturate: '<S4>/Saturation' */
  }

  /* End of RelationalOperator: '<S3>/Compare' */
  /* End of Outputs for SubSystem: '<Root>/LQR Controller' */

  /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
   *  Inport: '<Root>/Mode'
   */
  switch ((int32_T)mode) {
   case 1:
    Udk = controllers_B.Saturation_a;
    break;

   case 2:
    Udk = controllers_B.Saturation;
    break;

   default:
    Udk = controllers_B.Saturation_e;
    break;
  }

  /* End of MultiPortSwitch: '<Root>/Multiport Switch' */

  /* Update for DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn' incorporates:
   *  Inport: '<Root>/Setpoint'
   */
  controllers_DWork.DiscreteTransferFcn_states = (setPoint
    - controllers_P.DiscreteTransferFcn_DenCoef[1] *
    controllers_DWork.DiscreteTransferFcn_states) /
    controllers_P.DiscreteTransferFcn_DenCoef[0];

  /* Update for UnitDelay: '<Root>/Unit Delay' incorporates:
   *  Inport: '<Root>/PV'
   */
  controllers_DWork.UnitDelay_DSTATE = processVar;
}

/* Model initialize function */
void controllers_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(controllers_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &controllers_B), 0,
                sizeof(BlockIO_controllers));

  /* exported global signals */
  Udk = 0.0;
  xi = 0.0;
  wn = 0.0;

  /* states (dwork) */
  (void) memset((void *)&controllers_DWork, 0,
                sizeof(D_Work_controllers));

  /* external inputs */
  setPoint = 0.0;
  mode = 0.0;
  processVar = 0.0;

  /* Start for Enabled SubSystem: '<Root>/STR Controller' */
  /* Start for Constant: '<S53>/xi' */
  xi = controllers_P.xi_Value;

  /* Start for Constant: '<S53>/wn' */
  wn = controllers_P.wn_Value;

  /* End of Start for SubSystem: '<Root>/STR Controller' */

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn' */
  controllers_DWork.DiscreteTransferFcn_states =
    controllers_P.DiscreteTransferFcn_InitialStat;

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay' */
  controllers_DWork.UnitDelay_DSTATE =
    controllers_P.UnitDelay_InitialCondition_p;

  /* SystemInitialize for Enabled SubSystem: '<Root>/PID Controller' */
  /* InitializeConditions for DiscreteIntegrator: '<S32>/Filter' */
  controllers_DWork.Filter_DSTATE =
    controllers_P.DiscretePIDController_InitialCo;

  /* InitializeConditions for DiscreteIntegrator: '<S37>/Integrator' */
  controllers_DWork.Integrator_DSTATE =
    controllers_P.DiscretePIDController_Initial_p;

  /* End of SystemInitialize for SubSystem: '<Root>/PID Controller' */

  /* SystemInitialize for Enabled SubSystem: '<Root>/STR Controller' */
  /* InitializeConditions for UnitDelay: '<S52>/Unit Delay' */
  controllers_DWork.UnitDelay_DSTATE_e =
    controllers_P.UnitDelay_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S52>/Unit Delay3' */
  controllers_DWork.UnitDelay3_DSTATE =
    controllers_P.UnitDelay3_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S52>/Unit Delay2' */
  controllers_DWork.UnitDelay2_DSTATE =
    controllers_P.UnitDelay2_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S52>/Unit Delay1' */
  controllers_DWork.UnitDelay1_DSTATE =
    controllers_P.UnitDelay1_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S53>/Unit Delay' */
  controllers_DWork.UnitDelay_DSTATE_j =
    controllers_P.UnitDelay_InitialCondition_o;

  /* InitializeConditions for UnitDelay: '<S53>/Unit Delay1' */
  controllers_DWork.UnitDelay1_DSTATE_c =
    controllers_P.UnitDelay1_InitialCondition_l;

  /* InitializeConditions for UnitDelay: '<S53>/Unit Delay2' */
  controllers_DWork.UnitDelay2_DSTATE_f =
    controllers_P.UnitDelay2_InitialCondition_j;

  /* InitializeConditions for UnitDelay: '<S53>/Unit Delay3' */
  controllers_DWork.UnitDelay3_DSTATE_o =
    controllers_P.UnitDelay3_InitialCondition_j;

  /* SystemInitialize for MATLAB Function: '<S52>/MATLAB Function' */
  controllers_DWork.theta_not_empty = false;
  controllers_DWork.state_not_empty = false;
  controllers_DWork.method = 7U;
  controllers_DWork.state = 1144108930U;
  controllers_DWork.state_i[0] = 362436069U;
  controllers_DWork.state_i[1] = 521288629U;

  /* End of SystemInitialize for SubSystem: '<Root>/STR Controller' */
}

/* Model terminate function */
void controllers_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
