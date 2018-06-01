#ifndef OURDMA_H
#define OURDMA_H

#include <stdint.h>
#include <stm32f407xx.h>

void initDMA(void);
void initDMA2DAC(uint16_t * emaitza);


#endif
