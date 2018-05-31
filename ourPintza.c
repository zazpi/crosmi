#include "ourPintza.h"
#include "ourADC.h"
#include "ourTimer.h"
#include "ourRccGpio.h"

#define ZIKLO_KOP 3000
#define TIMER_ABIADURA 1

uint16_t maxBalioa = 0;
uint32_t zikloak = 0;
uint16_t azkenMaxBalioa = 0;

void ADCcallback(uint16_t balioa);
void initGPIOA6(void);
void (*callbackPintza)(uint16_t)=0;

void initPintza(void){
	initGPIOA6();
	initTimer2(TIMER_ABIADURA,1,0);
	initADC(1,1,0X06);
	setADCCallBack(ADCcallback);
}

void initGPIOA6(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, 1);
	initGpioPinMode(GPIOA, 6, GPIO_Mode_AN);
}

uint16_t getAzkenKontsumoa(){
	return azkenMaxBalioa;
}
void setPintzaCallback(void (*funtzioa)(uint16_t)){
	callbackPintza = funtzioa;
}
		
void ADCcallback(uint16_t balioa){	
		if(balioa > maxBalioa)
			maxBalioa = balioa;
		if(++zikloak < ZIKLO_KOP){
			azkenMaxBalioa = maxBalioa;
			maxBalioa = 0;
			zikloak = 0;
			if(callbackPintza) callbackPintza(azkenMaxBalioa);
		}
}

