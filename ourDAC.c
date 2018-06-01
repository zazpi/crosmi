#include "ourDAC.h"

void initGPIODAC2(void);

void initDAC(uint32_t dma, uint32_t trgo2){
	initGPIODAC2();
	RCC->APB1ENR |= (0X01 << 29); //DAC periferikua enable
	DAC->CR |= 0X01 <<(0+16) ; // EN Enable 
	
	DAC ->CR |= 0X01 <<(1 +16); // BOFF Buffer disable
	DAC ->CR |= 0X01 <<(2+16); // TEN Trigger
	
	if(trgo2){
		DAC -> CR |= 0X04 <<(3+16); // TSEL TRGO2
	}else{
		DAC -> CR |= 0X07 <<(3+16); // TSEL TRGO2
	}
	if(dma){
		DAC ->CR |= 0X01 << (12+16); // DMAEN1
	}
}

void initGPIODAC2(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, 1);
	initGpioPinMode(GPIOA, 5, GPIO_Mode_AN);
}

void setBalioa(uint32_t balioa){
	DAC->DHR12R2 |= balioa; 
	DAC->SWTRIGR |= 0x01 <<1; 
}
