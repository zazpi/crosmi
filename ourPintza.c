#include "ourPintza.h"
#include "ourADC.h"
#include "ourTimer.h"
#include "ourRccGpio.h"

#include "ourDMA.h"
#include "ourDAC.h"

#define ZIKLO_KOP 100 // cycles for the ADC.
#define TIMER_ABIADURA 10

#define OFFSET (uint16_t) 0x04d9 //custom offset for the alternate current signal

uint16_t maxBalioa = 0;
uint32_t zikloak = 0;
uint16_t azkenMaxBalioa = 0;

void ADCcallback(uint16_t balioa);
void initGPIOA6(void);
void (*callbackPintza)(uint16_t)=0;

/**
 *This function initializes some peripherals to work with an extern tool (pintza).
 *Initializes GPIO6, Timer 2, ADC, DAC and DMA.
 *@return void.
*/
void initPintza(void){
	initGPIOA6();
	initTimer2(TIMER_ABIADURA,1,0);
	initADC(1,1,0X06);
	setADCCallBack(ADCcallback);

	initDAC(1,1);
	initDMA2DAC(&azkenMaxBalioa);
}

/**
 *This function enables or disables Timer2 and ADC depending on the given param.
 *@param piztu: uint32_t type acts as a boolean to enable or disable Timer 2 and ADC.
 *@return void.
*/
void powerPintza(uint32_t piztu){
	switchTimer2(piztu);
	switchADC(piztu);
}

/**
Initializes GPIO6 and sets its mode to Analog mode.
@return void.
*/
void initGPIOA6(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, 1);
	initGpioPinMode(GPIOA, 6, GPIO_Mode_AN);
}
/**
Gets the last value from the conversion made by ADC.
@return azkenBalio: uint16_t type last conversion value.
*/
uint16_t getAzkenKontsumoa(){
	return azkenMaxBalioa;
}

/**
Sets callback function that recieves the last value of the conversion as parameter.
@param funtzioa: void type function, is a pointer to a void returning function which take uint16_t
type parameter.
@return void.
*/
void setPintzaCallback(void (*funtzioa)(uint16_t)){
	callbackPintza = funtzioa;
}
/**
This function calculates the max value converted by the ADC. It waits for 3000 cycles
and takes the max value. Used to take the peak value of the alternate current. And sets
the max value to the callback function.
@param balio: uint16_t type current value converted by the ADC.
@return void.
*/
void ADCcallback(uint16_t balioa){
		if(balioa < OFFSET)
			 balioa = OFFSET+(OFFSET-balioa);
    if(balioa > maxBalioa)
			maxBalioa = balioa;
		if(++zikloak > ZIKLO_KOP){
			azkenMaxBalioa = maxBalioa;
			maxBalioa = 0;
			zikloak = 0;
			if(callbackPintza) callbackPintza(azkenMaxBalioa);
		}
}
