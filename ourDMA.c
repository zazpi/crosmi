#include "ourDMA.h"

uint16_t dir;

void initDMA(void){
	RCC->AHB1ENR |= 0X01 << 22;
	DMA2_Stream0->CR &= ~(0X07 << 25); //CHSEL Channel 0
	DMA2_Stream0->CR &= ~(0x01 << 19); // CT Target Memory 0
	DMA2_Stream0->CR |= 0x02 << 16; // Priority High
	DMA2_Stream0->CR |= 0x01 <<13; // MSIZE Memory Half word 16bit
	DMA2_Stream0->CR |= 0x01 <<11; // PSIZE Peripheral Half word 16bit
	
	DMA2_Stream0->CR &= ~(0x03 << 6); //DIR Peripheral to memory 
	
	DMA2_Stream0->PAR |= ADC1_BASE + 0X4C; // Peripheral address
	DMA2_Stream0->M0AR |= (uint32_t) &dir; // Memory address
	
	DMA2_Stream0->NDTR |= 0x01;
	DMA2_Stream0->CR |= 0x01 <<8; // Circular mode
	ADC1->CR2 |= 0X01 << 8;
	ADC1->CR2 |= 0X01 << 9;
	DMA2_Stream0->CR |= 0x01; // Stream enable
}

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
