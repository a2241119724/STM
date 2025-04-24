#include "test1.h"
#include "Delay.h"
#include "OLED.h"

void initGPIOPinXPP(uint32_t RCC_APB2Periph_GPIOx,uint16_t GPIO_Pin_x,GPIO_TypeDef* GPIOx){
	initGPIOPinX(RCC_APB2Periph_GPIOx,GPIO_Pin_x,GPIOx,GPIO_Mode_Out_PP);
}

void initGPIOPinXAFPP(uint32_t RCC_APB2Periph_GPIOx,uint16_t GPIO_Pin_x,GPIO_TypeDef* GPIOx){
	initGPIOPinX(RCC_APB2Periph_GPIOx,GPIO_Pin_x,GPIOx,GPIO_Mode_AF_PP);
}

void initGPIOPinXIPU(uint32_t RCC_APB2Periph_GPIOx,uint16_t GPIO_Pin_x,GPIO_TypeDef* GPIOx){
	initGPIOPinX(RCC_APB2Periph_GPIOx,GPIO_Pin_x,GPIOx,GPIO_Mode_IPU);
}

void initGPIOPinXAIN(uint32_t RCC_APB2Periph_GPIOx,uint16_t GPIO_Pin_x,GPIO_TypeDef* GPIOx){
	initGPIOPinX(RCC_APB2Periph_GPIOx,GPIO_Pin_x,GPIOx,GPIO_Mode_AIN);
}

void initGPIOPinX(uint32_t RCC_APB2Periph_GPIOx,uint16_t GPIO_Pin_x,GPIO_TypeDef* GPIOx,GPIOMode_TypeDef GPIO_Mode){
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx,ENABLE);
	// GPIO初始化
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx,&GPIO_InitStructure);
}

void initInterrupt(void){
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	initGPIOPinXIPU(RCC_APB2Periph_GPIOB,GPIO_Pin_14,GPIOB);
	// AFIO外部中断引脚选择
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	// EXTI初始化
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	// 设置中断优先级分组(全局只需设置一次)
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	// NVIC初始化
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

void pc13TestFromRegister(void){
	// APB2外设时钟使能寄存器
	RCC->APB2ENR = 0x00000010;
	//
	GPIOC->CRH = 0x00300000;
	// 端口输出数据寄存器
	GPIOC->ODR = 0x00000000;
	// GPIOC->ODR = 0x00002000
	while(1){}
}

void pc13Test(void){
	initGPIOPinXPP(RCC_APB2Periph_GPIOC,GPIO_Pin_13,GPIOC);
	//GPIO_SetBits(GPIOC,GPIO_Pin_13);
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	while(1){}
}

void ledTest(void){
	//
	GPIO_TypeDef* GPIOx = GPIOA;
	//
	initGPIOPinXPP(RCC_APB2Periph_GPIOA,GPIO_Pin_All,GPIOx);
	uint16_t GPIO_Pin_x = GPIO_Pin_0;
//	while(1){
//		if(GPIO_Pin_x>=1<<8){
//			GPIO_Pin_x = GPIO_Pin_0;
//		}
//		// 设置一位
//		GPIO_SetBits(GPIOx,GPIO_Pin_All);
//		GPIO_ResetBits(GPIOx,GPIO_Pin_x);
//		Delay_ms(500);
//		GPIO_Pin_x <<= 1;
//	}
	while(1){
		if(GPIO_Pin_x>=1<<8){
			GPIO_Pin_x = GPIO_Pin_0;
		}
		/// 设置所有位
		GPIO_Write(GPIOx,~GPIO_Pin_x);
		Delay_ms(500);
		GPIO_Pin_x <<= 1;
	}
}

void buzzerTest(void){
	//
	GPIO_TypeDef* GPIOx = GPIOB;
	//
	initGPIOPinXPP(RCC_APB2Periph_GPIOB,GPIO_Pin_12,GPIOx);
	while(1){
		GPIO_SetBits(GPIOx,GPIO_Pin_12);
		Delay_ms(500);
		GPIO_ResetBits(GPIOx,GPIO_Pin_12);
		Delay_ms(500);
	}
}

void keyTest(void){
	initGPIOPinXPP(RCC_APB2Periph_GPIOA,GPIO_Pin_All,GPIOA);
	GPIO_Write(GPIOA,GPIO_Pin_All);
	//
	initGPIOPinXIPU(RCC_APB2Periph_GPIOB,GPIO_Pin_1|GPIO_Pin_11,GPIOB);
	while(1){
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0){
			GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		}else{
			GPIO_SetBits(GPIOA,GPIO_Pin_0);
		}
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0){
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		}else{
			GPIO_SetBits(GPIOA,GPIO_Pin_1);
		}
	}
}

void lightSensorTest(void){
	initGPIOPinXPP(RCC_APB2Periph_GPIOB,GPIO_Pin_12,GPIOB);
	initGPIOPinXIPU(RCC_APB2Periph_GPIOB,GPIO_Pin_13,GPIOB);
	while(1){
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1){
			GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		}else{
			GPIO_SetBits(GPIOB,GPIO_Pin_12);
		}
	}
}

void OLEDTest(void){
	OLED_Init();
	for(uint8_t i=0;i<1;i++){
		OLED_SetCursor(i,0);
		for(uint8_t j=0;j<128;j++){
			OLED_WriteData(0xFF);
		}
	}
	while(1){}
}

uint8_t count = 0;
void interruptTest(void){
	OLED_Init();
	OLED_ShowString(1,1,"count:");
	OLED_ShowNum(1,7,count,3);
	initInterrupt();
}

void EXTI15_10_IRQHandler(void){
	OLED_ShowNum(1,7,++count,3);
	if(EXTI_GetITStatus(EXTI_Line14)==SET){
		OLED_ShowString(1,1,"aaa");
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}

int8_t count1 = 0;
void knobTest(void){
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	initGPIOPinXIPU(RCC_APB2Periph_GPIOB,GPIO_Pin_0|GPIO_Pin_1,GPIOB);
	// AFIO外部中断引脚选择
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	// EXTI初始化
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0|EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	// 设置中断优先级分组(全局只需设置一次)
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	// NVIC初始化
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
	
	OLED_Init();
	while(1){
		printCount();
	}
}

void EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0)==SET){
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0){
			count1--;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line1)==SET){
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0){
			count1++;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void printCount(void){
	OLED_ShowString(1,1,"count:");
	OLED_ShowSignedNum(1,7,count1,3);
}

void timerTest(void){
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN,ENABLE);
	// 内部时钟
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructrue;
	TIM_TimeBaseInitStructrue.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructrue.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructrue.TIM_Period = 10000-1;
	TIM_TimeBaseInitStructrue.TIM_Prescaler = 7200-1;
	TIM_TimeBaseInitStructrue.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructrue);
	
	TIM_ClearFlag(TIM2,TIM_IT_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	// NVIC初始化
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
	
	OLED_Init();
	while(1){
		printCount();
	}
}

void timer1Test(void){
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN,ENABLE);
	initGPIOPinXIPU(RCC_APB2Periph_GPIOA,GPIO_Pin_0,GPIOA);
	// 外部时钟(0x0F大一点)
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x0F);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructrue;
	TIM_TimeBaseInitStructrue.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructrue.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructrue.TIM_Period = 10-1;
	TIM_TimeBaseInitStructrue.TIM_Prescaler = 1-1;
	TIM_TimeBaseInitStructrue.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructrue);
	
	TIM_ClearFlag(TIM2,TIM_IT_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	// NVIC初始化
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
	
	OLED_Init();
	while(1){
		printCount();
		OLED_ShowSignedNum(2,7,TIM_GetCounter(TIM2),3);
	}
}

void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){
		count1++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
