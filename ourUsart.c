#include "ourUsart.h"
#include "ourRccGpio.h"

#define USART3_TX 8
#define USART3_RX 9
#define RCC_APB1Periph_USART3 ((uint32_t)(0x01<<18))

void initGPIO(void);

void initCom( uint32_t baudRate){
	initGPIO();
	RCC->APB1ENR |= RCC_APB1Periph_USART3;
	
	USART3->BRR |= (16000000/(8*2*baudRate))<< 4; // Baudrate mantissa
	USART3->BRR |= 0x3; // Baudrate fraction
	
	USART3->CR1 |= 0X01 << 13; // UE Usart enable
	USART3->CR1 |= 0X01 << 2; // RE Read enable
	USART3->CR1 |= 0X01 << 3; // TE Transmitter enable
	
	USART3->CR1 |= 0X01 << 5;// RXNEIE Interrupzioa irakurri duenean
	NVIC->ISER[39/32] |= 0X01 << (39 % 32);
}

void initGPIO(){
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,1);
	initGpioPinMode(GPIOD,USART3_TX,GPIO_Mode_AF);
	initGpioPinMode(GPIOD,USART3_RX,GPIO_Mode_AF);
	setGpioPinAF(GPIOD,8,7);
	setGpioPinAF(GPIOD,9,7);
}

void writeToUart(uint8_t *pMsg){
	while(*pMsg != 0){
		while(!(USART3->SR & 0X01<<7));
		USART3->DR = *pMsg;
		pMsg++;
	}
}

void ourUSART3Handler(){
	if(USART3->SR & 0X01<<5){ // RXNE
		uint8_t irakurri = USART3->DR;
		writeToUart(&irakurri);
	}
}
