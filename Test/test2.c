#include "test2.h"
#include "test1.h"
#include "Delay.h"
#include "OLED.h"

void pwmTest(void){
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN,ENABLE);
	initGPIOPinXAFPP(RCC_APB2Periph_GPIOA,GPIO_Pin_0,GPIOA);
	// 内部时钟
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructrue;
	TIM_TimeBaseInitStructrue.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructrue.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructrue.TIM_Period = 100-1; // ARR
	TIM_TimeBaseInitStructrue.TIM_Prescaler = 720-1;
	TIM_TimeBaseInitStructrue.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructrue);
	
	TIM_OCInitTypeDef TIM_OCInitStructrue;
	TIM_OCStructInit(&TIM_OCInitStructrue);
	TIM_OCInitStructrue.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructrue.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructrue.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructrue.TIM_Pulse = 50; // CCR
	TIM_OC1Init(TIM2,&TIM_OCInitStructrue);
	
	TIM_Cmd(TIM2,ENABLE);
//	uint8_t i = 0;
//	while(1){
//		for(i=0;i<=100;i++){
//			TIM_SetCompare1(TIM2,i);
//			Delay_ms(10);
//		}
//		for(i=0;i<=100;i++){
//			TIM_SetCompare1(TIM2,100-i);
//			Delay_ms(10);
//		}
//	}
}

void servoTest(void){
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN,ENABLE);
	initGPIOPinXAFPP(RCC_APB2Periph_GPIOA,GPIO_Pin_1,GPIOA);
	// 内部时钟
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructrue;
	TIM_TimeBaseInitStructrue.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructrue.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructrue.TIM_Period = 20000-1; // ARR
	TIM_TimeBaseInitStructrue.TIM_Prescaler = 72-1;
	TIM_TimeBaseInitStructrue.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructrue);
	
	TIM_OCInitTypeDef TIM_OCInitStructrue;
	TIM_OCStructInit(&TIM_OCInitStructrue);
	TIM_OCInitStructrue.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructrue.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructrue.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructrue.TIM_Pulse = 500; // CCR
	TIM_OC2Init(TIM2,&TIM_OCInitStructrue);
	
	TIM_Cmd(TIM2,ENABLE);
	OLED_Init();
	OLED_ShowString(1,1,"aaa");
	float i = 0;
	while(1){
		for(i=0;i<=180;i++){
			setAngle(i);
			Delay_ms(10);
		}
	}
}

void setAngle(float angle){
	// 0-180;500-2500
	TIM_SetCompare2(TIM2,angle/180*2000+500);
}

void motorTest(void){
	initGPIOPinXPP(RCC_APB2Periph_GPIOA,GPIO_Pin_4|GPIO_Pin_5,GPIOA);
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN,ENABLE);
	initGPIOPinXAFPP(RCC_APB2Periph_GPIOA,GPIO_Pin_2,GPIOA);
	// 内部时钟
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructrue;
	TIM_TimeBaseInitStructrue.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructrue.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructrue.TIM_Period = 100-1; // ARR
	TIM_TimeBaseInitStructrue.TIM_Prescaler = 36-1;
	TIM_TimeBaseInitStructrue.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructrue);
	
	TIM_OCInitTypeDef TIM_OCInitStructrue;
	TIM_OCStructInit(&TIM_OCInitStructrue);
	TIM_OCInitStructrue.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructrue.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructrue.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructrue.TIM_Pulse = 0; // CCR
	TIM_OC3Init(TIM2,&TIM_OCInitStructrue);
	
	TIM_Cmd(TIM2,ENABLE);
	OLED_Init();
	OLED_ShowString(1,1,"aaa");
	setSpeed(-30);
	while(1){
		
	}
}

void setSpeed(int8_t speed){
	if(speed>=0){
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		TIM_SetCompare3(TIM2,speed);
	}else{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		TIM_SetCompare3(TIM2,-speed);
	}
}

void inputCaptureTest(void){
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN,ENABLE);
	initGPIOPinXIPU(RCC_APB2Periph_GPIOA,GPIO_Pin_6,GPIOA);
	// 内部时钟
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructrue;
	TIM_TimeBaseInitStructrue.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructrue.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructrue.TIM_Period = 65535-1; // ARR
	TIM_TimeBaseInitStructrue.TIM_Prescaler = 72-1;
	TIM_TimeBaseInitStructrue.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructrue);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	//TIM_ICInit(TIM3,&TIM_ICInitStructure);
	// 一次性配置两通道
	TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);
	
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM3,ENABLE);
	pwmTest();
	OLED_Init();
	OLED_ShowString(1,1,"Hz:");
	OLED_ShowChar(2,6,'%');
	while(1){
		printFreq();
		printDuty();
	}
}

void printFreq(void){
	OLED_ShowNum(1,4,1000000/(TIM_GetCapture1(TIM3)+1),5);
}

void printDuty(void){
	OLED_ShowNum(2,4,(TIM_GetCapture2(TIM3)+1)*100/(TIM_GetCapture1(TIM3)+1),2);
}

void encoderTest(void){
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN,ENABLE);
	initGPIOPinXIPU(RCC_APB2Periph_GPIOA,GPIO_Pin_6|GPIO_Pin_7,GPIOA);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructrue;
	TIM_TimeBaseInitStructrue.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructrue.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructrue.TIM_Period = 65536-1; // ARR
	TIM_TimeBaseInitStructrue.TIM_Prescaler = 1-1;
	TIM_TimeBaseInitStructrue.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructrue);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	TIM_Cmd(TIM3,ENABLE);
	OLED_Init();
	OLED_ShowString(1,1,"  :");
	while(1){
		printCNT();
		Delay_ms(100);
	}
}

void printCNT(void){
	int16_t t = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	OLED_ShowSignedNum(1,4,t,5);
}

void adcTest(void){
	initGPIOPinXAIN(RCC_APB2Periph_GPIOA,GPIO_Pin_0,GPIOA);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1)==SET);
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	OLED_Init();
	OLED_ShowString(1,1,"  :");
	while(1){
		printVoltage();
		Delay_ms(100);
	}
}

void printVoltage(void){
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	// 自动清楚标志位
	float t = (float)ADC_GetConversionValue(ADC1) / 4095 * 3.3;
	OLED_ShowNum(1,4,t*100,5);
}
