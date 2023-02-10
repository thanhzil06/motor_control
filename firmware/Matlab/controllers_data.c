/*
 * File: controllers_data.c
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

/* Block parameters (default storage) */
Parameters_controllers controllers_P = {
  /* Mask Parameter: DiscretePIDController_D
   * Referenced by: '<S31>/Derivative Gain'
   */
  0.0,

  /* Mask Parameter: DiscretePIDController_I
   * Referenced by: '<S34>/Integral Gain'
   */
  0.002,

  /* Mask Parameter: DiscretePIDController_InitialCo
   * Referenced by: '<S32>/Filter'
   */
  0.0,

  /* Mask Parameter: DiscretePIDController_Initial_p
   * Referenced by: '<S37>/Integrator'
   */
  0.0,

  /* Mask Parameter: DiscretePIDController_N
   * Referenced by: '<S40>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: DiscretePIDController_P
   * Referenced by: '<S42>/Proportional Gain'
   */
  0.1,

  /* Mask Parameter: CompareToConstant_const
   * Referenced by: '<S1>/Constant'
   */
  1.0,

  /* Mask Parameter: CompareToConstant1_const
   * Referenced by: '<S2>/Constant'
   */
  2.0,

  /* Mask Parameter: CompareToConstant2_const
   * Referenced by: '<S3>/Constant'
   */
  3.0,

  /* Expression: 1
   * Referenced by: '<S4>/K1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S4>/K2'
   */
  1.0,

  /* Expression: 10
   * Referenced by: '<S4>/Saturation'
   */
  10.0,

  /* Expression: -10
   * Referenced by: '<S4>/Saturation'
   */
  -10.0,

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S32>/Filter'
   */
  0.005,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S37>/Integrator'
   */
  0.005,

  /* Expression: 10
   * Referenced by: '<S5>/Saturation'
   */
  10.0,

  /* Expression: -10
   * Referenced by: '<S5>/Saturation'
   */
  -10.0,

  /* Expression: 0
   * Referenced by: '<S52>/Unit Delay'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S52>/Unit Delay3'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S52>/Unit Delay2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S52>/Unit Delay1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S53>/Unit Delay'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S53>/Unit Delay1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S53>/Unit Delay2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S53>/Unit Delay3'
   */
  0.0,

  /* Expression: 0.9
   * Referenced by: '<S53>/xi'
   */
  0.9,

  /* Expression: 20
   * Referenced by: '<S53>/wn'
   */
  20.0,

  /* Expression: 10
   * Referenced by: '<S53>/Saturation'
   */
  10.0,

  /* Expression: -10
   * Referenced by: '<S53>/Saturation'
   */
  -10.0,

  /* Expression: 10
   * Referenced by: '<S6>/Saturation'
   */
  10.0,

  /* Expression: -10
   * Referenced by: '<S6>/Saturation'
   */
  -10.0,

  /* Expression: [0.04877]
   * Referenced by: '<Root>/Discrete Transfer Fcn'
   */
  0.04877,

  /* Expression: [1 -0.9512]
   * Referenced by: '<Root>/Discrete Transfer Fcn'
   */
  { 1.0, -0.9512 },

  /* Expression: 0
   * Referenced by: '<Root>/Discrete Transfer Fcn'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Unit Delay'
   */
  0.0
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
