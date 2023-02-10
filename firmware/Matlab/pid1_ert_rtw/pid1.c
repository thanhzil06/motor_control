/*
 * File: pid1.c
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

/* Exported block signals */
real_T In2;                            /* '<Root>/In2' */
real_T Out1;                           /* '<Root>/Saturation' */

/* Block states (default storage) */
D_Work_pid1 pid1_DWork;

/* Real-time model */
RT_MODEL_pid1 pid1_M_;
RT_MODEL_pid1 *const pid1_M = &pid1_M_;

/* Model step function */
void pid1_step(void)
{
  real_T rtb_Add;
  real_T rtb_FilterCoefficient;
  real_T u0;

  /* DiscretePulseGenerator: '<Root>/Setpoint (deg)' */
  rtb_Add = (pid1_DWork.clockTickCounter < pid1_P.Setpointdeg_Duty) &&
    (pid1_DWork.clockTickCounter >= 0) ? pid1_P.Setpointdeg_Amp : 0.0;
  if (pid1_DWork.clockTickCounter >= pid1_P.Setpointdeg_Period - 1.0) {
    pid1_DWork.clockTickCounter = 0;
  } else {
    pid1_DWork.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Setpoint (deg)' */

  /* Sum: '<Root>/Add' incorporates:
   *  Inport: '<Root>/In2'
   */
  rtb_Add -= In2;

  /* Gain: '<S34>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S26>/Filter'
   *  Gain: '<S25>/Derivative Gain'
   *  Sum: '<S26>/SumD'
   */
  rtb_FilterCoefficient = (pid1_P.DiscretePIDController_D * rtb_Add -
    pid1_DWork.Filter_DSTATE) * pid1_P.DiscretePIDController_N;

  /* Sum: '<S40>/Sum' incorporates:
   *  DiscreteIntegrator: '<S31>/Integrator'
   *  Gain: '<S36>/Proportional Gain'
   */
  u0 = (pid1_P.DiscretePIDController_P * rtb_Add + pid1_DWork.Integrator_DSTATE)
    + rtb_FilterCoefficient;

  /* Saturate: '<Root>/Saturation' */
  if (u0 > pid1_P.Saturation_UpperSat) {
    Out1 = pid1_P.Saturation_UpperSat;
  } else if (u0 < pid1_P.Saturation_LowerSat) {
    Out1 = pid1_P.Saturation_LowerSat;
  } else {
    Out1 = u0;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Update for DiscreteIntegrator: '<S31>/Integrator' incorporates:
   *  Gain: '<S28>/Integral Gain'
   */
  pid1_DWork.Integrator_DSTATE += pid1_P.DiscretePIDController_I * rtb_Add *
    pid1_P.Integrator_gainval;

  /* Update for DiscreteIntegrator: '<S26>/Filter' */
  pid1_DWork.Filter_DSTATE += pid1_P.Filter_gainval * rtb_FilterCoefficient;
}

/* Model initialize function */
void pid1_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(pid1_M, (NULL));

  /* block I/O */

  /* exported global signals */
  Out1 = 0.0;

  /* states (dwork) */
  (void) memset((void *)&pid1_DWork, 0,
                sizeof(D_Work_pid1));

  /* external inputs */
  In2 = 0.0;

  /* Start for DiscretePulseGenerator: '<Root>/Setpoint (deg)' */
  pid1_DWork.clockTickCounter = 0;

  /* InitializeConditions for DiscreteIntegrator: '<S31>/Integrator' */
  pid1_DWork.Integrator_DSTATE = pid1_P.DiscretePIDController_Initial_d;

  /* InitializeConditions for DiscreteIntegrator: '<S26>/Filter' */
  pid1_DWork.Filter_DSTATE = pid1_P.DiscretePIDController_InitialCo;
}

/* Model terminate function */
void pid1_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
