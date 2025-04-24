#ifndef __TEST3_H
#define __TEST3_H 

#include <stdint.h>
#include <stdio.h>

void dmaTransport(uint32_t source,uint32_t target);
void dmaTest(void);
void usartTest(void);
void sentDataBySerial(uint8_t byte);
int fputc(int ch,FILE *f); // 勾选Use MicroLIB

#endif
