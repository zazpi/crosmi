#include "ourUsart.h"
#include "ourTimer.h"
#include "ourADC.h"
#include "ourRccGpio.h"
#include <stdint.h>

#define ZIKLO_KOP 3000

void initGPIOa(void);
void ADCcallback(uint16_t balioa);

uint16_t maxBalioa = 0;
uint32_t zikloak = 0;

int main(){
	initGPIOa();
	initCom(9600);
	initTimer2(1);
	initADC();	
	setCallBack(ADCcallback);
	for(;;){
	}
}

void ADCcallback(uint16_t balioa){
	if(balioa > maxBalioa)
		maxBalioa = balioa;
	if(++zikloak == ZIKLO_KOP){
		writeToUart((uint8_t * )&maxBalioa);
		maxBalioa = 0;
		zikloak = 0;

	}
}

void initGPIOa(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, 1);
	initGpioPinMode(GPIOA, 5, GPIO_Mode_AN);
	initGpioPinMode(GPIOA, 6, GPIO_Mode_AN);
	
}
