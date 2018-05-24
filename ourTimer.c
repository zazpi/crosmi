#include "ourTimer.h"

void initTimer2(int ms){
	RCC -> APB1ENR |= 0x01;
	TIM2 -> CR1 |= 0x01 << 7; //ARPE
	TIM2 -> CR1 |= 0x01 << 4; //Downcounter, DIR
	TIM2 -> ARR = ((16000000/1000 * ms)-1UL);
	TIM2 -> CR2 |= 0x02 << 4; // TRGO señalea sortu - Update
  TIM2 -> CR1 |= 0x01; //Counter enable.	
}