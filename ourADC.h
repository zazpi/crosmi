#ifndef OURADC_H
#define OURADC_H

#include <stdint.h>
#include <stm32f407xx.h>

void initADC();
void ourADCHandler();
uint32_t getBalioa();

#endif