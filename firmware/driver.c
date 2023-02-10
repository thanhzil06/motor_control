
#include "stm32f4xx.h"
#include "system_timetick.h"
#include "driver.h"
#include "stdlib.h"


void init_main(void);
void PWM0_Set_Freq(uint32_t freq);

void PWM0_Set_Duty(int16_t d);
void PWM1_Set_Duty(int16_t d);
void PWM2_Set_Duty(int16_t d);
int32_t ENC0_GetPos(void);

#define		RBUFF_SIZE			67
#define		TBUFF_SIZE			15
uint8_t 	rxbuff[RBUFF_SIZE];
//uint8_t 	a[RBUFF_SIZE];
uint8_t 	txbuff[TBUFF_SIZE]; 
uint8_t 	tmpTxBuf[TBUFF_SIZE];

int run;
int modes;
int receivedFlag;
uint8_t rcvByte[8];
double Sp, Kp, Ki, Kd, Xi, OmegaN, K1, K2;
uint8_t typeOfSetpoint;

/* Get encoder counter 32 bit */
int32_t ENC0_GetPos(void)
{
	static int32_t 	p = 0, p_pre = 0, dp = 0;
  static int32_t 	pulse_cur = 0.0;
	
	p = (int32_t)TIM1->CNT;
	dp = p - p_pre;
	if (dp > 32768)
		dp -= 65536;
	else if (dp < -32768)
		dp += 65536;
	p_pre = p;
	pulse_cur += dp;
	
	return pulse_cur;
}

/* Setup pwm frequency - unit: Hz */
void PWM0_Set_Freq(uint32_t freq)
{
	uint32_t period;
	
	period = 84000000/(freq*(TIM12->PSC+1))-1;	
	if (period > 0xffff)
		period = 0xffff;
	
	TIM12->ARR = period;
}

/* Output pwm frequency - unit: 0.1% */
void PWM0_Set_Duty(int16_t d)
{
	if (d<-1000)
		d = -1000;
	else if (d>1000)
		d = 1000;

	if (d == 0){
		GPIO_SetBits(GPIOD,GPIO_Pin_10);  	// disable pwm
	}	
	else if (d > 0)	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_10);	// enabe pwm		
		GPIO_ResetBits(GPIOB,GPIO_Pin_15); 	// dir = 1
	}
	else 	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_10);	// enabe pwm
		GPIO_SetBits(GPIOB,GPIO_Pin_15); 		// dir = 0
		d = -d;
	}
	d = (TIM12->ARR+1)*d/1000;
	TIM12->CCR1 = (uint32_t)d;
}

void init_main(void)
{
	GPIO_InitTypeDef 				GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef 			TIM_OCInitStructure;
	
	USART_InitTypeDef 			USART_InitStructure;
	DMA_InitTypeDef   			DMA_InitStructure;
  NVIC_InitTypeDef  			NVIC_InitStructure;
	
	//**********PWM*********
	/* TIM clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 

	/* PULSE pin configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	// R_PWM
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_TIM12);
	
	/* DIR, EN pins configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9| GPIO_Pin_15| GPIO_Pin_14;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* TIM CH1 configuration */
	TIM_TimeBaseStructure.TIM_Period = 1000-1;// 2M/1000=2k
	TIM_TimeBaseStructure.TIM_Prescaler = 42 - 1;// 84M/42=2M
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM12, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);

	TIM_Cmd(TIM12, ENABLE);
		
	//**********ENCODER*********
	/* TIM1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	/* TIM1 channell2 configuration */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);

	/* Initialise encoder interface */
	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	/* TIM enable counter */
	TIM1->CNT = 0;
	TIM_Cmd(TIM1, ENABLE);	
	

	/*_____________________My Init_____________________*/
	//---------------------USART2---------------------
	/* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  /* Enable UART clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	/* Enable DMA1 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	
	/* Connect UART2 pins to AF7 */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); 

  /* GPIO Configuration for UART2 Tx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* GPIO Configuration for USART2 Rx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
       
  /* USARTx configured as follow:
		- BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART2, &USART_InitStructure);	
	/* Enable USART */
  USART_Cmd(USART2, ENABLE);	
	
	/* Enable USART2 DMA */
	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
  USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);	
	
	/* DMA1 Stream6 Channel4 for USART2 Tx configuration */			
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;	// &a: Lay dia chi cua bien a, voi a la thanh ghi DR cua USART2.
																																		// &UART4->DR: dia chi dich
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)txbuff;					// txbuff: dia chi nguon
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;						// Huong truyen di
  DMA_InitStructure.DMA_BufferSize = TBUFF_SIZE;	
	/* Tang dia chi nguon va dich */ 
	//Vi dia chi cua ngoai vi can truyen data toi la co dinh, nen khong tang dia chi cua ngoai vi
	// Khi truyen txbuff[0] xong thi truyen tiep txbuff[1]. Vi vay, can tang dia chi nguon len de truyen byte tiep theo.
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; 				// Or Circular_In order for data khong bi tran, thuong dung cho Rx
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;		// Neu nhu 2 DMA cung xay ra, DMA nao duoc set priority_high thi se xay ra truoc
																												// Neu nhu khong set priority, DMA co chi so nho thuc hien truoc. Vi du nhu stream_0 thuc hien nhiem vu truoc stream_7.		
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	/* Thuc hien config xong roi moi cho phep DMA1_Stream6 hoat dong*/
  DMA_Init(DMA1_Stream6, &DMA_InitStructure);
  DMA_Cmd(DMA1_Stream6, ENABLE);
	
	/* DMA1 Stream5 Channel4 for USART2 Rx configuration */			
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rxbuff;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = RBUFF_SIZE;
	
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
  DMA_Init(DMA1_Stream5, &DMA_InitStructure);
  DMA_Cmd(DMA1_Stream5, ENABLE);
		
	/* Enable DMA Interrupt to the highest priority */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Transfer complete interrupt mask */
  DMA_ITConfig(DMA1_Stream5, DMA_IT_TC, ENABLE);	// Khi co IT_TC duoc bat len thi nhay vao ham ngat DMA1_Stream2_IRQHandler()

}

void delay_us(uint16_t period){

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  	TIM6->PSC = 83;		// clk = SystemCoreClock / 4 / (PSC+1) *2 = 1MHz
  	TIM6->ARR = period-1;
  	TIM6->CNT = 0;
  	TIM6->EGR = 1;		// update registers;

  	TIM6->SR  = 0;		// clear overflow flag
  	TIM6->CR1 = 1;		// enable Timer6

  	while (!TIM6->SR);
    
  	TIM6->CR1 = 0;		// stop Timer6
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, DISABLE);
}

void delay_01ms(uint16_t period){

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  	TIM6->PSC = 8399;		// clk = SystemCoreClock / 4 / (PSC+1) *2 = 10KHz
  	TIM6->ARR = period-1;
  	TIM6->CNT = 0;
  	TIM6->EGR = 1;		// update registers;

  	TIM6->SR  = 0;		// clear overflow flag
  	TIM6->CR1 = 1;		// enable Timer6

  	while (!TIM6->SR);
    
  	TIM6->CR1 = 0;		// stop Timer6
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, DISABLE);
}

uint8_t lengthTxBuf;
void send_data(int16_t setpoint, int16_t processvar){
	
	lengthTxBuf = sprintf((char *)tmpTxBuf, "%d,%d\r\n",setpoint, processvar);
	txbuff[0] = 'S';
	txbuff[1] = (char)',';
	for(int count = 0; count < lengthTxBuf; count ++){
		txbuff[2 + count] = tmpTxBuf[count];
	}
	
	DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6);
	DMA1_Stream6->NDTR = TBUFF_SIZE;
	DMA_Cmd(DMA1_Stream6, ENABLE);
}
double ConvertByteToDouble(uint8_t *str){
	char string[8];
	for(int i = 0; i < 7; i++){
		if(str[i]!=0)
			string[i] = (char)str[i];
		else string[i] = 0;
	}	
	
	/* Remember to include "stdlib.h" so that you can use atof() function */
	double d;
	d = atof(string);
	return d;
}

uint16_t pulse_square(uint16_t value){
	
}

void DMA1_Stream5_IRQHandler(void)
{
  uint16_t i;

  /* Clear the DMA1_Stream5 TCIF2 pending bit */
  DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5);		// Luc truoc code cu: DMA_IT_TCIF2 -> cua Stream2 UART4 -> BUG here

  /*
	for(i=0; i<RBUFF_SIZE; i++)
			a[i] = rxbuff[i];	
	index = index + BUFF_SIZE;
	*/
	run = rxbuff[0];
	modes = rxbuff[1];
	
	for(int loop = 0; loop<8; loop++)
		rcvByte[loop] = rxbuff[2+loop];
	Sp = ConvertByteToDouble(rcvByte);		
	
	for(int loop = 0; loop<8; loop++)
		rcvByte[loop] = rxbuff[10+loop];
	Kp = ConvertByteToDouble(rcvByte);
	
	for(int loop = 0; loop<8; loop++)
		rcvByte[loop] = rxbuff[18+loop];
	Ki = ConvertByteToDouble(rcvByte);
	
	for(int loop = 0; loop<8; loop++)
		rcvByte[loop] = rxbuff[26+loop];
	Kd = ConvertByteToDouble(rcvByte);
	
	for(int loop = 0; loop<8; loop++)
		rcvByte[loop] = rxbuff[34+loop];
	Xi = ConvertByteToDouble(rcvByte);
	
	for(int loop = 0; loop<8; loop++)
		rcvByte[loop] = rxbuff[42+loop];
	OmegaN = ConvertByteToDouble(rcvByte);
	
	for(int loop = 0; loop<8; loop++)
		rcvByte[loop] = rxbuff[50+loop];
	K1 = ConvertByteToDouble(rcvByte);
	
	for(int loop = 0; loop<8; loop++)
		rcvByte[loop] = rxbuff[58+loop];
	K2 = ConvertByteToDouble(rcvByte);
	
	typeOfSetpoint = rxbuff[66];
	
	DMA_Cmd(DMA1_Stream5, ENABLE);
	receivedFlag =1;
}
