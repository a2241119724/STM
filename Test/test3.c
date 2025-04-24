#include "test3.h"
#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"
#include "test1.h"

void dmaTransport(uint32_t source,uint32_t target){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_BufferSize = 4;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
	DMA_InitStructure.DMA_MemoryBaseAddr = target;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr = source;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1,ENABLE);
}

void dmaTest(void){
	uint8_t dataA[] = {1,2,3,4};
	uint8_t dataB[] = {0,0,0,0};
	OLED_Init();
	while(1){
		for(int i=0;i<4;i++){
			dataA[i] += 1;
			OLED_ShowNum(1,(i+1)*2,dataA[i],1);
			OLED_ShowNum(2,(i+1)*2,dataB[i],1);
		}
		DMA_Cmd(DMA1_Channel1,DISABLE);
		DMA_SetCurrDataCounter(DMA1_Channel1,4);
		dmaTransport((uint32_t)dataA,(uint32_t)dataB);
		Delay_ms(1000);
		for(int i=0;i<4;i++){
			OLED_ShowNum(1,(i+1)*2,dataA[i],1);
			OLED_ShowNum(2,(i+1)*2,dataB[i],1);
		}
		Delay_ms(1000);
	}
}

void usartTest(void){
	initGPIOPinXAFPP(RCC_APB2Periph_GPIOA,GPIO_Pin_9,GPIOA);
	initGPIOPinXIPU(RCC_APB2Periph_GPIOA,GPIO_Pin_10,GPIOA);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_InitTypeDef USART_InitStructrue;
	USART_InitStructrue.USART_BaudRate = 9600;
	USART_InitStructrue.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructrue.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructrue.USART_Parity = USART_Parity_No;
	USART_InitStructrue.USART_StopBits = USART_StopBits_1;
	USART_InitStructrue.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructrue);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART1,ENABLE);
	printf("你好\r\n");
	OLED_Init();
	while(1){
		
	}
}

void sentDataBySerial(uint8_t byte){
	USART_SendData(USART1,byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

int fputc(int ch,FILE *f){
	sentDataBySerial(ch);
	return ch;
}

void USART1_IRQHandler(void){
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET){
		uint16_t res = USART_ReceiveData(USART1);
		OLED_ShowNum(1,1,res,1);
	}
}
