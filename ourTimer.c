#include "ourTimer.h"

void (*callbackTimer2)(void)=0;

volatile uint32_t ticks=0;
volatile uint32_t ticksOld=0;

/**
Initializes timer 2 setting basic configurations for launch.
Some given paramaters such as trGo and interrupzio are optional.
@param ms: uint32_t type time in millisecond above which timer 2 have to operate.
@param trGo: uint32_t acts as  boolean to know whether is needed to enable TRGO signal.
@param interrupzioa: uint32_t acts as a boolean to know whether interruption configuration is needed.
@return void.
*/
void initTimer2(uint32_t ms, uint32_t trGo, uint32_t interrupzioa){
	RCC -> APB1ENR |= 0x01;
	TIM2 -> CR1 |= 0x01 << 7; //ARPE
	TIM2 -> CR1 |= 0x01 << 4; //Downcounter, DIR
	TIM2 -> ARR = ((16000000/1000 * ms)-1UL);
  TIM2 -> CR1 |= 0x01; //Counter enable.	
	if(trGo){
		TIM2 -> CR2 |= 0x02 << 4; // Creates TRGO signal - Update
	}
	if(interrupzioa){
		TIM2->DIER |= 0X01;
		NVIC->ISER[0] |= (0X01<<28);
	}
}

/**
Enables or disables the Timer 2 depending on the given parameter.
@param piztu: uint32_t type acts as a boolean to enable or disable the Timer 2.
@return void.
*/
void switchTimer2(int piztu){
	if(piztu)
		TIM2 -> CR1 |= 0x01;
	else
		TIM2 -> CR1 &= ~0x01;
}

void waitTick(void) {
  while(ticksOld==ticks);
  ticksOld++;
}

uint32_t getTicks(void){
	return ticks;
}

void setTimer2CallBack(void (*funtzioa)(void)){
	callbackTimer2 = funtzioa;
}

/**
Custom handler for Timer 2 interruption.
@return void.
*/
void ourTimer2Handler(void){
	TIM2->SR &= ~0X01;
	ticks++;
	if(callbackTimer2) callbackTimer2();
}





