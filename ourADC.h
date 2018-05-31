#ifndef OURADC_H
#define OURADC_H

#include <stdint.h>
#include <stm32f407xx.h>

//Konfigurazioa
void initADC(uint32_t timer2TRGO, uint32_t interrupzioa, uint32_t kanala);
void switchADC(int piztu);

//Datuak
uint16_t getAzkenBalioa(void);
uint16_t getBalioa(void);

//Interrupzioa
void ourADCHandler(void);
void setADCCallBack(void (*funtzioa)(uint16_t));

#endif
