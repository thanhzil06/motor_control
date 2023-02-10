/*
 * File: pid1_data.c
 *
 * Code generated for Simulink model 'pid1'.
 *
 * Model version                  : 1.29
 * Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
 * C/C++ source code generated on : Wed Jun  1 11:35:02 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "pid1.h"
#include "pid1_private.h"

/* Block parameters (default storage) */
Parameters_pid1 pid1_P = {
  /* Mask Parameter: DiscretePIDController_D
   * Referenced by: '<S25>/Derivative Gain'
   */
  0.0,

  /* Mask Parameter: DiscretePIDController_I
   * Referenced by: '<S28>/Integral Gain'
   */
  0.0001,

  /* Mask Parameter: DiscretePIDController_InitialCo
   * Referenced by: '<S26>/Filter'
   */
  0.0,

  /* Mask Parameter: DiscretePIDController_Initial_d
   * Referenced by: '<S31>/Integrator'
   */
  0.0,

  /* Mask Parameter: DiscretePIDController_N
   * Referenced by: '<S34>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: DiscretePIDController_P
   * Referenced by: '<S36>/Proportional Gain'
   */
  0.08,

  /* Expression: 1000
   * Referenced by: '<Root>/Setpoint (deg)'
   */
  1000.0,

  /* Computed Parameter: Setpointdeg_Period
   * Referenced by: '<Root>/Setpoint (deg)'
   */
  2000.0,

  /* Computed Parameter: Setpointdeg_Duty
   * Referenced by: '<Root>/Setpoint (deg)'
   */
  1000.0,

  /* Expression: 0
   * Referenced by: '<Root>/Setpoint (deg)'
   */
  0.0,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S31>/Integrator'
   */
  0.005,

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S26>/Filter'
   */
  0.005,

  /* Expression: 10
   * Referenced by: '<Root>/Saturation'
   */
  10.0,

  /* Expression: -10
   * Referenced by: '<Root>/Saturation'
   */
  -10.0
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
