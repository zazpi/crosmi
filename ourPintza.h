#ifndef OUR_PINTZA_H
#define OUR_PINTZA_H

#include <stdint.h>
#include <stm32f407xx.h>

void initPintza(void);
void powerPintza(uint32_t piztu);

uint16_t getAzkenKontsumoa(void);
// Interrupzioak
void setPintzaCallback(void (*funtzioa)(uint16_t));
void ADCcallback(uint16_t balioa);

#endif
