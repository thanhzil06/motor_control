/*
 * File: pid1.h
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

#ifndef RTW_HEADER_pid1_h_
#define RTW_HEADER_pid1_h_
#include <stddef.h>
#include <string.h>
#ifndef pid1_COMMON_INCLUDES_
# define pid1_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* pid1_COMMON_INCLUDES_ */

#include "pid1_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S31>/Integrator' */
  real_T Filter_DSTATE;                /* '<S26>/Filter' */
  int32_T clockTickCounter;            /* '<Root>/Setpoint (deg)' */
} D_Work_pid1;

/* Parameters (default storage) */
struct Parameters_pid1_ {
  real_T DiscretePIDController_D;     /* Mask Parameter: DiscretePIDController_D
                                       * Referenced by: '<S25>/Derivative Gain'
                                       */
  real_T DiscretePIDController_I;     /* Mask Parameter: DiscretePIDController_I
                                       * Referenced by: '<S28>/Integral Gain'
                                       */
  real_T DiscretePIDController_InitialCo;
                              /* Mask Parameter: DiscretePIDController_InitialCo
                               * Referenced by: '<S26>/Filter'
                               */
  real_T DiscretePIDController_Initial_d;
                              /* Mask Parameter: DiscretePIDController_Initial_d
                               * Referenced by: '<S31>/Integrator'
                               */
  real_T DiscretePIDController_N;     /* Mask Parameter: DiscretePIDController_N
                                       * Referenced by: '<S34>/Filter Coefficient'
                                       */
  real_T DiscretePIDController_P;     /* Mask Parameter: DiscretePIDController_P
                                       * Referenced by: '<S36>/Proportional Gain'
                                       */
  real_T Setpointdeg_Amp;              /* Expression: 1000
                                        * Referenced by: '<Root>/Setpoint (deg)'
                                        */
  real_T Setpointdeg_Period;           /* Computed Parameter: Setpointdeg_Period
                                        * Referenced by: '<Root>/Setpoint (deg)'
                                        */
  real_T Setpointdeg_Duty;             /* Computed Parameter: Setpointdeg_Duty
                                        * Referenced by: '<Root>/Setpoint (deg)'
                                        */
  real_T Setpointdeg_PhaseDelay;       /* Expression: 0
                                        * Referenced by: '<Root>/Setpoint (deg)'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S31>/Integrator'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S26>/Filter'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 10
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -10
                                        * Referenced by: '<Root>/Saturation'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_pid1 {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern Parameters_pid1 pid1_P;

/* Block states (default storage) */
extern D_Work_pid1 pid1_DWork;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T In2;                     /* '<Root>/In2' */
extern real_T Out1;                    /* '<Root>/Saturation' */

/* Model entry point functions */
extern void pid1_initialize(void);
extern void pid1_step(void);
extern void pid1_terminate(void);

/* Real-time Model object */
extern RT_MODEL_pid1 *const pid1_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'pid1'
 * '<S1>'   : 'pid1/Discrete PID  Controller'
 * '<S2>'   : 'pid1/Discrete PID  Controller/Anti-windup'
 * '<S3>'   : 'pid1/Discrete PID  Controller/D Gain'
 * '<S4>'   : 'pid1/Discrete PID  Controller/Filter'
 * '<S5>'   : 'pid1/Discrete PID  Controller/Filter ICs'
 * '<S6>'   : 'pid1/Discrete PID  Controller/I Gain'
 * '<S7>'   : 'pid1/Discrete PID  Controller/Ideal P Gain'
 * '<S8>'   : 'pid1/Discrete PID  Controller/Ideal P Gain Fdbk'
 * '<S9>'   : 'pid1/Discrete PID  Controller/Integrator'
 * '<S10>'  : 'pid1/Discrete PID  Controller/Integrator ICs'
 * '<S11>'  : 'pid1/Discrete PID  Controller/N Copy'
 * '<S12>'  : 'pid1/Discrete PID  Controller/N Gain'
 * '<S13>'  : 'pid1/Discrete PID  Controller/P Copy'
 * '<S14>'  : 'pid1/Discrete PID  Controller/Parallel P Gain'
 * '<S15>'  : 'pid1/Discrete PID  Controller/Reset Signal'
 * '<S16>'  : 'pid1/Discrete PID  Controller/Saturation'
 * '<S17>'  : 'pid1/Discrete PID  Controller/Saturation Fdbk'
 * '<S18>'  : 'pid1/Discrete PID  Controller/Sum'
 * '<S19>'  : 'pid1/Discrete PID  Controller/Sum Fdbk'
 * '<S20>'  : 'pid1/Discrete PID  Controller/Tracking Mode'
 * '<S21>'  : 'pid1/Discrete PID  Controller/Tracking Mode Sum'
 * '<S22>'  : 'pid1/Discrete PID  Controller/postSat Signal'
 * '<S23>'  : 'pid1/Discrete PID  Controller/preSat Signal'
 * '<S24>'  : 'pid1/Discrete PID  Controller/Anti-windup/Passthrough'
 * '<S25>'  : 'pid1/Discrete PID  Controller/D Gain/Internal Parameters'
 * '<S26>'  : 'pid1/Discrete PID  Controller/Filter/Disc. Forward Euler Filter'
 * '<S27>'  : 'pid1/Discrete PID  Controller/Filter ICs/Internal IC - Filter'
 * '<S28>'  : 'pid1/Discrete PID  Controller/I Gain/Internal Parameters'
 * '<S29>'  : 'pid1/Discrete PID  Controller/Ideal P Gain/Passthrough'
 * '<S30>'  : 'pid1/Discrete PID  Controller/Ideal P Gain Fdbk/Disabled'
 * '<S31>'  : 'pid1/Discrete PID  Controller/Integrator/Discrete'
 * '<S32>'  : 'pid1/Discrete PID  Controller/Integrator ICs/Internal IC'
 * '<S33>'  : 'pid1/Discrete PID  Controller/N Copy/Disabled'
 * '<S34>'  : 'pid1/Discrete PID  Controller/N Gain/Internal Parameters'
 * '<S35>'  : 'pid1/Discrete PID  Controller/P Copy/Disabled'
 * '<S36>'  : 'pid1/Discrete PID  Controller/Parallel P Gain/Internal Parameters'
 * '<S37>'  : 'pid1/Discrete PID  Controller/Reset Signal/Disabled'
 * '<S38>'  : 'pid1/Discrete PID  Controller/Saturation/Passthrough'
 * '<S39>'  : 'pid1/Discrete PID  Controller/Saturation Fdbk/Disabled'
 * '<S40>'  : 'pid1/Discrete PID  Controller/Sum/Sum_PID'
 * '<S41>'  : 'pid1/Discrete PID  Controller/Sum Fdbk/Disabled'
 * '<S42>'  : 'pid1/Discrete PID  Controller/Tracking Mode/Disabled'
 * '<S43>'  : 'pid1/Discrete PID  Controller/Tracking Mode Sum/Passthrough'
 * '<S44>'  : 'pid1/Discrete PID  Controller/postSat Signal/Forward_Path'
 * '<S45>'  : 'pid1/Discrete PID  Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_pid1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
