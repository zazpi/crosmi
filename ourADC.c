#include "ourADC.h"
uint16_t azkenBalioa = 0;

void (*callback)(uint16_t)=0;

void initADC(uint32_t timer2TRGO, uint32_t interrupzioa, uint32_t kanala){
	RCC -> APB2ENR |= 0x01 << 8;
	ADC1 -> CR2 |= 0x01; //ADC PIZTU
	ADC1 -> SQR3 |= kanala; //GPIOA6 0x06
	if(timer2TRGO) {
		ADC1 -> CR2 |= 0x01 << 28; //SEÑALE EXTERNO BAT ERABILTZEKO ESAN - EXTEN
		ADC1 -> CR2 |= 0x06 << 24; //TRGO ERABILTZEKO ESAN - EXTSEL
	}
	if(interrupzioa){
		ADC1 -> CR1 |= 0x01 << 5; //INTERRUPZIOA PIZTU
		NVIC -> ISER[0] |= 0x01 << 18; //INTERRUPZIOA PIZTU
	}
}

void switchADC(int piztu){
	if(piztu)
		ADC1 -> CR2 |= 0x01;
	else
		ADC1 -> CR2 &=  ~0x01;
}

void setADCCallBack(void (*funtzioa)(uint16_t)){
	callback = funtzioa;
}

void ourADCHandler(){
	azkenBalioa = ADC1 -> DR;
	if(callback) callback(azkenBalioa);
}

uint16_t getAzkenBalioa(){
	return azkenBalioa;
}

uint16_t getBalioa(void){
	ADC1->CR2 |= 0X01 <<30; // Neurketa hasi
	while(!(ADC1->SR & 0X01 << 1)); // Itxaron bukatu arte
	azkenBalioa = ADC1 ->DR;
	return azkenBalioa;
}
