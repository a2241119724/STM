#ifndef __TEST2_H
#define __TEST2_H  

#include "stm32f10x.h"
#include <stdint.h>

void pwmTest(void);
void servoTest(void);
void setAngle(float angle);
void motorTest(void);
void setSpeed(int8_t speed);
void inputCaptureTest(void);
void printFreq(void);
void printDuty(void);
void encoderTest(void);
void printCNT(void);
void adcTest(void);
void printVoltage(void);

#endif
