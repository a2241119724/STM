#ifndef __TEST1_H
#define __TEST1_H  

#include "stm32f10x.h"
#include <stdint.h>

void initGPIOPinX(uint32_t RCC_APB2Periph_GPIOx,uint16_t GPIO_Pin_x,GPIO_TypeDef* GPIOx,GPIOMode_TypeDef GPIO_Mode);
void initGPIOPinXPP(uint32_t RCC_APB2Periph_GPIOx,uint16_t GPIO_Pin_x,GPIO_TypeDef* GPIOx);
void initGPIOPinXAFPP(uint32_t RCC_APB2Periph_GPIOx,uint16_t GPIO_Pin_x,GPIO_TypeDef* GPIOx);
void initGPIOPinXAIN(uint32_t RCC_APB2Periph_GPIOx,uint16_t GPIO_Pin_x,GPIO_TypeDef* GPIOx);
void initGPIOPinXIPU(uint32_t RCC_APB2Periph_GPIOx,uint16_t GPIO_Pin_x,GPIO_TypeDef* GPIOx);
void initInterrupt(void);

void pc13TestFromRegister(void);
void pc13Test(void);
void ledTest(void);
void buzzerTest(void);
void keyTest(void);
void lightSensorTest(void);
void OLEDTest(void);
void interruptTest(void);
void EXTI15_10_IRQHandler(void);
void knobTest(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void printCount(void);
void timerTest(void);
void timer1Test(void);
void TIM2_IRQHandler(void);

#endif
