/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'pid1'.
 *
 * Model version                  : 1.26
 * Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
 * C/C++ source code generated on : Sat Apr 23 10:14:05 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */

#include "stm32f4xx.h"                 
#include "system_timetick.h"
#include "driver.h"

#include "controllers.h"                      /* Model's header file */
#include "rtwtypes.h"

static boolean_T OverrunFlag = 0;
extern int run, modes;
extern double Sp, Kp, Ki, Kd, Xi, OmegaN, K1, K2;
extern uint8_t typeOfSetpoint;
extern int receivedFlag;

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(void);
void rt_OneStep(void)
{
  //static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  
	/* Code mau tu ert_main.c
	if (OverrunFlag) {
    rtmSetErrorStatus(pid1_M, "Overrun");
    return;*/
	if (OverrunFlag++) {
    rtmSetErrorStatus(controllers_M, "Overrun");
    return;
		
  }

  // code mau: OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  controllers_step();

  /* Get model outputs here */

  /* Indicate task complete */
  // code mau: OverrunFlag = false;
	OverrunFlag--;
  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int16_t udk, i;
uint16_t cnt = 0;
int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  (void)(argc);
  (void)(argv);
	
		/* Enable SysTick at 5ms interrupt. Moi 5ms se lay mau mot lan*/
  SysTick_Config(SystemCoreClock/200);
	delay_01ms(1000);	// Delay de dong co khoi dong
	
	/* init_main() se khoi tao cac gia tri phan cung, match voi cac bien ben matlab de khong xay ra bug. 
		Neu muon thay bug, cu viec xoa ham nay trong main di :) */
	init_main();
	
	PWM0_Set_Freq(10000);
	PWM0_Set_Duty(0);  // Do phan giai la 0.01%. Nghia la neu muon cong suat hoat dong 100% thi phai set gia tri la 10000.
	//PWM1_Set_Duty(0);
	
	
  /* Initialize model */
  controllers_initialize();

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.005 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   *
   *  rt_OneStep();
   */
	 
	while(1){			
		if(run == 0){
					GPIO_SetBits(GPIOD, GPIO_Pin_14);
				  GPIO_ResetBits(GPIOD, GPIO_Pin_15);
			TIM1->CNT = 0;
			if(tick_flag) { 
					tick_flag = 0;
					setPoint = 0;
					processVar = 0;					
					send_data((int16_t)(setPoint),(int16_t)(processVar));							
			}
			
			PWM0_Set_Duty(0);					
			}
			else {
				GPIO_SetBits(GPIOD, GPIO_Pin_15);
				GPIO_ResetBits(GPIOD, GPIO_Pin_14);
					
				if(receivedFlag == 1)	{
						// Init params...
						setPoint = Sp;
						mode = modes;
						controllers_P.DiscretePIDController_P = Kp;
						controllers_P.DiscretePIDController_I = Ki;
						controllers_P.DiscretePIDController_D = Kd;
						controllers_P.xi_Value = Xi;
						controllers_P.wn_Value = OmegaN;
						controllers_P.K1_Gain = K1;
						controllers_P.K2_Gain = K2;
						receivedFlag = 0;					
					}
					
				if(tick_flag) { 
					tick_flag = 0;	
					
					if(typeOfSetpoint == 1){	// Square pulse mode
							cnt++;
							if(cnt == 200){
								//cnt = 0;
								setPoint = 0;
							}
							if(cnt == 400){
								cnt = 0;
								setPoint = Sp;
							}												
						}
					
					processVar = (double)ENC0_GetPos()/20000.0 *360.0;				
				/* 		____Bai toan dieu khien vi tri/goc cua dong co____
					Doc tin hieu tu cam bien encoder ve va gan cho In2 trong matlab. 
					Encoder co 1000 xung, ma mach co 2 kenh A, B, dong thoi xung canh len canh xuong nen nhan 4 -> 4000.
					1 vong quay bang 360 do nen nhan cho 360 de ra duoc goc cua dong co.
					Ngoai ra, dong co oos hop so ti le 1:5 */	
			
					rt_OneStep(); // Goi ham controllers_step()_Nghia la goi mo hinh simulink
			
					Udk = Udk*1000/12;
					/* Bien Out1 la dien ap dau ra cua cau H dieu khien dong co.
						Bien Out1 ve trai se la xung PWM.
						Xung PWM cos tan so 10kHz -> 1/10k = 0.01% -> Ton/T = 0 -> 100.00% ___  0 -> 12V */

					udk = (int)Udk;
					PWM0_Set_Duty(udk);
					send_data((int16_t)(setPoint),(int16_t)(processVar));				
			//if(tick_count>15000)		{
				// Lo nhu tick_count co lon hon 4000 ma phan code tren van dang thuc hien tac vu nao do thi phai chowf tac vu do duoc thuc hien xong
				//GPIO_SetBits(GPIOD,GPIO_Pin_15);
				//break;} // Sau 20s thi thoat ra khoi ham while va set tin hieu dieu rong xung ve 0_Ham PWM0_Set_Duty(0);
			}		 
	}
}	

	//6. while(1);

  /* Disable rt_OneStep() here */

  /* Terminate model */
  controllers_terminate();
}
