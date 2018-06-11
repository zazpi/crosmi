#include "ourDMA.h"

void initDMA2DAC(uint16_t * emaitza){
	RCC->AHB1ENR |= 0X01 << 21;
	DMA1_Stream6->CR |= 0X07 << 25; //CHSEL Channel 7
	DMA1_Stream6->CR &= ~(0x01 << 19); // CT Target Memory 0
	DMA1_Stream6->CR |= 0x02 << 16; // Priority High
	DMA1_Stream6->CR |= 0x01 <<13; // MSIZE Memory Half word 16bit
	DMA1_Stream6->CR |= 0x01 <<11; // PSIZE Peripheral Half word 16bit
	
	DMA1_Stream6->CR |= 0x01 << 6; //DIR Memory to peripheral
	
	DMA1_Stream6->PAR |= DAC_BASE + 0X14; // Peripheral address  // DAC_DHR12R2
	DMA1_Stream6->M0AR |= (uint32_t) emaitza; // Memory address
	
	DMA1_Stream6->NDTR |= 0x01;
	DMA1_Stream6->CR |= 0x01 <<8; // Circular mode
	
	DMA1_Stream6->CR |= 0x01; // Stream enable
}
