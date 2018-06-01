#ifndef OURDAC_H
#define OURDAC_H

#include <stdint.h>
#include "ourRccGpio.h"
#include <stm32f407xx.h>

void initDAC(uint32_t dma, uint32_t trgo2);
void setBalioa(uint32_t balioa);

#endif
