#include "ourADC.h"
uint16_t balioa = 0;

void (*callback)(uint16_t)=0;

void initADC(){
	RCC -> APB2ENR |= 0x01 << 8;
	ADC1 -> CR2 |= 0x01; //ADC PIZTU
	ADC1 -> CR1 |= 0x01 << 5; //INTERRUPZIOA PIZTU
	ADC1 -> CR2 |= 0x01 << 28; //SEÑALE EXTERNO BAT ERABILTZEKO ESAN - EXTEN
	ADC1 -> CR2 |= 0x06 << 24; //TRGO ERABILTZEKO ESAN - EXTSEL
	ADC1 -> SQR3 |= 0x06; //GPIOA6
	NVIC -> ISER[0] |= 0x01 << 18; //INTERRUPZIOA PIZTU
}

void setCallBack(void (*funtzioa)(uint16_t)){
	callback = funtzioa;
}

void ourADCHandler(){
	balioa = ADC1 -> DR;
	if(callback) callback(balioa);
}


uint32_t getBalioa(){
	return balioa;
}
