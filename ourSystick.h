#ifndef OUR_SYSTICK_H
#define OUR_SYSTICK_H

#include <stdint.h>
#include <stm32f407xx.h>

void initSysTick(uint32_t ms, uint32_t internalClk);
uint32_t getSysTicks(void);
void waitNextSysTick(void);
void ourSysTickHandler(void);

#endif
