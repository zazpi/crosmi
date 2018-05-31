#include "ourTimer.h"

void (*callbackTimer2)(void)=0;

volatile uint32_t ticks=0;
volatile uint32_t ticksOld=0;

void initTimer2(uint32_t ms, uint32_t trGo, uint32_t interrupzioa){
	RCC -> APB1ENR |= 0x01;
	TIM2 -> CR1 |= 0x01 << 7; //ARPE
	TIM2 -> CR1 |= 0x01 << 4; //Downcounter, DIR
	TIM2 -> ARR = ((16000000/1000 * ms)-1UL);
  TIM2 -> CR1 |= 0x01; //Counter enable.	
	if(trGo){
		TIM2 -> CR2 |= 0x02 << 4; // TRGO señalea sortu - Update
	}
	if(interrupzioa){
		TIM2->DIER |= 0X01;
		NVIC->ISER[0] |= (0X01<<28);
	}
}

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

void ourTimer2Handler(void){
	TIM2->SR &= ~0X01;
	ticks++;
	if(callbackTimer2) callbackTimer2();
}





