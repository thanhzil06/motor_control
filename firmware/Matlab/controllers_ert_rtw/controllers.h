/*
 * File: controllers.h
 *
 * Code generated for Simulink model 'controllers'.
 *
 * Model version                  : 1.45
 * Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
 * C/C++ source code generated on : Sun Jul  3 11:04:56 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_controllers_h_
#define RTW_HEADER_controllers_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef controllers_COMMON_INCLUDES_
# define controllers_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* controllers_COMMON_INCLUDES_ */

#include "controllers_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Saturation;                   /* '<S6>/Saturation' */
  real_T Saturation_a;                 /* '<S5>/Saturation' */
  real_T Saturation_e;                 /* '<S4>/Saturation' */
} BlockIO_controllers;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTransferFcn_states;   /* '<Root>/Discrete Transfer Fcn' */
  real_T UnitDelay_DSTATE;             /* '<Root>/Unit Delay' */
  real_T UnitDelay_DSTATE_e;           /* '<S52>/Unit Delay' */
  real_T UnitDelay3_DSTATE;            /* '<S52>/Unit Delay3' */
  real_T UnitDelay2_DSTATE;            /* '<S52>/Unit Delay2' */
  real_T UnitDelay1_DSTATE;            /* '<S52>/Unit Delay1' */
  real_T UnitDelay_DSTATE_j;           /* '<S53>/Unit Delay' */
  real_T UnitDelay1_DSTATE_c;          /* '<S53>/Unit Delay1' */
  real_T UnitDelay2_DSTATE_f;          /* '<S53>/Unit Delay2' */
  real_T UnitDelay3_DSTATE_o;          /* '<S53>/Unit Delay3' */
  real_T Filter_DSTATE;                /* '<S32>/Filter' */
  real_T Integrator_DSTATE;            /* '<S37>/Integrator' */
  real_T theta[4];                     /* '<S52>/MATLAB Function' */
  real_T P[16];                        /* '<S52>/MATLAB Function' */
  uint32_T method;                     /* '<S52>/MATLAB Function' */
  uint32_T state;                      /* '<S52>/MATLAB Function' */
  uint32_T state_i[2];                 /* '<S52>/MATLAB Function' */
  uint32_T state_b[625];               /* '<S52>/MATLAB Function' */
  boolean_T theta_not_empty;           /* '<S52>/MATLAB Function' */
  boolean_T state_not_empty;           /* '<S52>/MATLAB Function' */
} D_Work_controllers;

/* Parameters (default storage) */
struct Parameters_controllers_ {
  real_T DiscretePIDController_D;     /* Mask Parameter: DiscretePIDController_D
                                       * Referenced by: '<S31>/Derivative Gain'
                                       */
  real_T DiscretePIDController_I;     /* Mask Parameter: DiscretePIDController_I
                                       * Referenced by: '<S34>/Integral Gain'
                                       */
  real_T DiscretePIDController_InitialCo;
                              /* Mask Parameter: DiscretePIDController_InitialCo
                               * Referenced by: '<S32>/Filter'
                               */
  real_T DiscretePIDController_Initial_p;
                              /* Mask Parameter: DiscretePIDController_Initial_p
                               * Referenced by: '<S37>/Integrator'
                               */
  real_T DiscretePIDController_N;     /* Mask Parameter: DiscretePIDController_N
                                       * Referenced by: '<S40>/Filter Coefficient'
                                       */
  real_T DiscretePIDController_P;     /* Mask Parameter: DiscretePIDController_P
                                       * Referenced by: '<S42>/Proportional Gain'
                                       */
  real_T CompareToConstant_const;     /* Mask Parameter: CompareToConstant_const
                                       * Referenced by: '<S1>/Constant'
                                       */
  real_T CompareToConstant1_const;   /* Mask Parameter: CompareToConstant1_const
                                      * Referenced by: '<S2>/Constant'
                                      */
  real_T CompareToConstant2_const;   /* Mask Parameter: CompareToConstant2_const
                                      * Referenced by: '<S3>/Constant'
                                      */
  real_T K1_Gain;                      /* Expression: 1
                                        * Referenced by: '<S4>/K1'
                                        */
  real_T K2_Gain;                      /* Expression: 1
                                        * Referenced by: '<S4>/K2'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 10
                                        * Referenced by: '<S4>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -10
                                        * Referenced by: '<S4>/Saturation'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S32>/Filter'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S37>/Integrator'
                                        */
  real_T Saturation_UpperSat_c;        /* Expression: 10
                                        * Referenced by: '<S5>/Saturation'
                                        */
  real_T Saturation_LowerSat_l;        /* Expression: -10
                                        * Referenced by: '<S5>/Saturation'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: 0
                                        * Referenced by: '<S52>/Unit Delay'
                                        */
  real_T UnitDelay3_InitialCondition;  /* Expression: 0
                                        * Referenced by: '<S52>/Unit Delay3'
                                        */
  real_T UnitDelay2_InitialCondition;  /* Expression: 0
                                        * Referenced by: '<S52>/Unit Delay2'
                                        */
  real_T UnitDelay1_InitialCondition;  /* Expression: 0
                                        * Referenced by: '<S52>/Unit Delay1'
                                        */
  real_T UnitDelay_InitialCondition_o; /* Expression: 0
                                        * Referenced by: '<S53>/Unit Delay'
                                        */
  real_T UnitDelay1_InitialCondition_l;/* Expression: 0
                                        * Referenced by: '<S53>/Unit Delay1'
                                        */
  real_T UnitDelay2_InitialCondition_j;/* Expression: 0
                                        * Referenced by: '<S53>/Unit Delay2'
                                        */
  real_T UnitDelay3_InitialCondition_j;/* Expression: 0
                                        * Referenced by: '<S53>/Unit Delay3'
                                        */
  real_T xi_Value;                     /* Expression: 0.9
                                        * Referenced by: '<S53>/xi'
                                        */
  real_T wn_Value;                     /* Expression: 20
                                        * Referenced by: '<S53>/wn'
                                        */
  real_T Saturation_UpperSat_i;        /* Expression: 10
                                        * Referenced by: '<S53>/Saturation'
                                        */
  real_T Saturation_LowerSat_a;        /* Expression: -10
                                        * Referenced by: '<S53>/Saturation'
                                        */
  real_T Saturation_UpperSat_d;        /* Expression: 10
                                        * Referenced by: '<S6>/Saturation'
                                        */
  real_T Saturation_LowerSat_b;        /* Expression: -10
                                        * Referenced by: '<S6>/Saturation'
                                        */
  real_T DiscreteTransferFcn_NumCoef;  /* Expression: [0.04877]
                                        * Referenced by: '<Root>/Discrete Transfer Fcn'
                                        */
  real_T DiscreteTransferFcn_DenCoef[2];/* Expression: [1 -0.9512]
                                         * Referenced by: '<Root>/Discrete Transfer Fcn'
                                         */
  real_T DiscreteTransferFcn_InitialStat;/* Expression: 0
                                          * Referenced by: '<Root>/Discrete Transfer Fcn'
                                          */
  real_T UnitDelay_InitialCondition_p; /* Expression: 0
                                        * Referenced by: '<Root>/Unit Delay'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_controllers {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern Parameters_controllers controllers_P;

/* Block signals (default storage) */
extern BlockIO_controllers controllers_B;

/* Block states (default storage) */
extern D_Work_controllers controllers_DWork;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T setPoint;                /* '<Root>/Setpoint' */
extern real_T mode;                    /* '<Root>/Mode' */
extern real_T processVar;              /* '<Root>/PV' */
extern real_T Udk;                     /* '<Root>/Multiport Switch' */
extern real_T xi;                      /* '<S53>/xi' */
extern real_T wn;                      /* '<S53>/wn' */

/* Model entry point functions */
extern void controllers_initialize(void);
extern void controllers_step(void);
extern void controllers_terminate(void);

/* Real-time Model object */
extern RT_MODEL_controllers *const controllers_M;

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
 * '<Root>' : 'controllers'
 * '<S1>'   : 'controllers/Compare To Constant'
 * '<S2>'   : 'controllers/Compare To Constant1'
 * '<S3>'   : 'controllers/Compare To Constant2'
 * '<S4>'   : 'controllers/LQR Controller'
 * '<S5>'   : 'controllers/PID Controller'
 * '<S6>'   : 'controllers/STR Controller'
 * '<S7>'   : 'controllers/PID Controller/Discrete PID Controller'
 * '<S8>'   : 'controllers/PID Controller/Discrete PID Controller/Anti-windup'
 * '<S9>'   : 'controllers/PID Controller/Discrete PID Controller/D Gain'
 * '<S10>'  : 'controllers/PID Controller/Discrete PID Controller/Filter'
 * '<S11>'  : 'controllers/PID Controller/Discrete PID Controller/Filter ICs'
 * '<S12>'  : 'controllers/PID Controller/Discrete PID Controller/I Gain'
 * '<S13>'  : 'controllers/PID Controller/Discrete PID Controller/Ideal P Gain'
 * '<S14>'  : 'controllers/PID Controller/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S15>'  : 'controllers/PID Controller/Discrete PID Controller/Integrator'
 * '<S16>'  : 'controllers/PID Controller/Discrete PID Controller/Integrator ICs'
 * '<S17>'  : 'controllers/PID Controller/Discrete PID Controller/N Copy'
 * '<S18>'  : 'controllers/PID Controller/Discrete PID Controller/N Gain'
 * '<S19>'  : 'controllers/PID Controller/Discrete PID Controller/P Copy'
 * '<S20>'  : 'controllers/PID Controller/Discrete PID Controller/Parallel P Gain'
 * '<S21>'  : 'controllers/PID Controller/Discrete PID Controller/Reset Signal'
 * '<S22>'  : 'controllers/PID Controller/Discrete PID Controller/Saturation'
 * '<S23>'  : 'controllers/PID Controller/Discrete PID Controller/Saturation Fdbk'
 * '<S24>'  : 'controllers/PID Controller/Discrete PID Controller/Sum'
 * '<S25>'  : 'controllers/PID Controller/Discrete PID Controller/Sum Fdbk'
 * '<S26>'  : 'controllers/PID Controller/Discrete PID Controller/Tracking Mode'
 * '<S27>'  : 'controllers/PID Controller/Discrete PID Controller/Tracking Mode Sum'
 * '<S28>'  : 'controllers/PID Controller/Discrete PID Controller/postSat Signal'
 * '<S29>'  : 'controllers/PID Controller/Discrete PID Controller/preSat Signal'
 * '<S30>'  : 'controllers/PID Controller/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S31>'  : 'controllers/PID Controller/Discrete PID Controller/D Gain/Internal Parameters'
 * '<S32>'  : 'controllers/PID Controller/Discrete PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S33>'  : 'controllers/PID Controller/Discrete PID Controller/Filter ICs/Internal IC - Filter'
 * '<S34>'  : 'controllers/PID Controller/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S35>'  : 'controllers/PID Controller/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S36>'  : 'controllers/PID Controller/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S37>'  : 'controllers/PID Controller/Discrete PID Controller/Integrator/Discrete'
 * '<S38>'  : 'controllers/PID Controller/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S39>'  : 'controllers/PID Controller/Discrete PID Controller/N Copy/Disabled'
 * '<S40>'  : 'controllers/PID Controller/Discrete PID Controller/N Gain/Internal Parameters'
 * '<S41>'  : 'controllers/PID Controller/Discrete PID Controller/P Copy/Disabled'
 * '<S42>'  : 'controllers/PID Controller/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S43>'  : 'controllers/PID Controller/Discrete PID Controller/Reset Signal/Disabled'
 * '<S44>'  : 'controllers/PID Controller/Discrete PID Controller/Saturation/Passthrough'
 * '<S45>'  : 'controllers/PID Controller/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S46>'  : 'controllers/PID Controller/Discrete PID Controller/Sum/Sum_PID'
 * '<S47>'  : 'controllers/PID Controller/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S48>'  : 'controllers/PID Controller/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S49>'  : 'controllers/PID Controller/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S50>'  : 'controllers/PID Controller/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S51>'  : 'controllers/PID Controller/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S52>'  : 'controllers/STR Controller/Param Estimation'
 * '<S53>'  : 'controllers/STR Controller/Self-tuning Regulator  '
 * '<S54>'  : 'controllers/STR Controller/Param Estimation/MATLAB Function'
 * '<S55>'  : 'controllers/STR Controller/Self-tuning Regulator  /MATLAB Function'
 */
#endif                                 /* RTW_HEADER_controllers_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
