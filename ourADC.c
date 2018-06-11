#include "ourADC.h"
uint16_t azkenBalioa = 0;

void (*callback)(uint16_t)=0;

/**
This function initializes ADC, setting core basic params to launch ADC. Some of the params are optional configurations
such as interruption and TRGO.
@param timer2TRGO: uint32_t type but acts as a boolean to know if timer 2's TRGO is needed.
@param interrupzioa: uint32_t type but acts as boolean to know if interruption is needed.
@param kanala: uint32_t type holds the value of which channel should be used by the ADC.
@return void.
*/
void initADC(uint32_t timer2TRGO, uint32_t interrupzioa, uint32_t kanala){
	RCC -> APB2ENR |= 0x01 << 8;
	ADC1 -> CR2 |= 0x01; //ADC enable
	ADC1 -> SQR3 |= kanala; //GPIOA6 0x06
	if(timer2TRGO) {
		ADC1 -> CR2 |= 0x01 << 28; //Set ADC to use extern signal
		ADC1 -> CR2 |= 0x06 << 24; //Set ADC to use TRGO
	}
	if(interrupzioa){
		ADC1 -> CR1 |= 0x01 << 5; //Enable interruption
		NVIC -> ISER[0] |= 0x01 << 18; //Enable interruption
	}
}

/**
This function enable or disable ADC peripheral depending on the given parameter that acts as a boolean type.
@param piztu: int type but acts as a boolean to know whether is needed to enable or disable ADC1.
@return void.
*/
void switchADC(int piztu){
	if(piztu)
		ADC1 -> CR2 |= 0x01;
	else
		ADC1 -> CR2 &=  ~0x01;
	azkenBalioa= 0;
}

/**
This function sets a pointer to another function which accepts a paramater of type uint16_t. Callback funtcion.
@params funtzio: void type points to a function.
@return void
*/
void setADCCallBack(void (*funtzioa)(uint16_t)){
	callback = funtzioa;
}

/**
This function acts as a handler for the interruption caused by the ADC.
@return void.
*/
void ourADCHandler(){
	azkenBalioa = ADC1 -> DR;
	if(callback) callback(azkenBalioa);
}

/**
Function that returns the last value of ADC.
@return azkenBalioa: uint16_t type ADC last value.
*/
uint16_t getAzkenBalioa(){
	return azkenBalioa;
}

/**
This function return the last value.
@return azkenBalioa: uint16_t type conversion's last value.
*/
uint16_t getBalioa(void){
	ADC1->CR2 |= 0X01 <<30; // Conversion start
	while(!(ADC1->SR & 0X01 << 1)); // Wait until it ends
	azkenBalioa = ADC1 ->DR;
	return azkenBalioa;
}
