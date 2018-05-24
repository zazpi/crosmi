#ifndef OURADC_H
#define OURADC_H

#include <stdint.h>
#include <stm32f407xx.h>

void initADC(void);
void ourADCHandler(void);
uint32_t getBalioa(void);
void setCallBack(void (*funtzioa)(uint16_t));

#endif
