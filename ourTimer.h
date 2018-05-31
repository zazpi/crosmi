#ifndef OURTIMER_H
#define OURTIMER_H
#include <stdint.h>
#include <stm32f407xx.h>

// Konfigurazioa
void initTimer2(uint32_t ms, uint32_t trGo, uint32_t interrupzioa);
void switchTimer2(int piztu);

// Datuak
void waitTick(void);
uint32_t getTicks(void);

//Interrupzioak
void ourTimer2Handler(void);
void setTimer2CallBack(void (*funtzioa)(void));

#endif
