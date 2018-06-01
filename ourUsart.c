#include "ourUsart.h"
#include "ourRccGpio.h"

#define USART3_TX 8
#define USART3_RX 9

#define BUFFER_SIZE 20

typedef struct Buffer{
	uint32_t size;
	uint8_t buffer[BUFFER_SIZE];
}Buffer;

Buffer bufferIdatzi;
Buffer bufferIrakurri;

void pushBuffer(Buffer * buffer, uint8_t balioa){
	buffer->buffer[buffer->size++] = balioa;
}

uint8_t popBuffer(Buffer * buffer){
	uint8_t pop = buffer->buffer[0];
	for(int i = 1; i < buffer->size;i++){
		buffer->buffer[i-1] = buffer->buffer[i];
	}
	buffer->size--;
	return pop;
}

uint32_t readBufferSize(){
	return bufferIrakurri.size;
}

void initGPIOUsart3(void);
void pushBuffer(Buffer * buffer, uint8_t balioa);
uint8_t popBuffer(Buffer * buffer);


/*
/ Usart 3 hasieratzen du.
/ Baudratea eta interrupzioak erabili edo ez zehaztu daiteke
*/
void initUsart3(uint32_t baudRate, uint32_t interrupzioak){
	initGPIOUsart3();
	RCC->APB1ENR |= 0x01<<18;
	
	USART3->BRR |= (16000000/(8*2*baudRate))<< 4; // Baudrate mantissa
	USART3->BRR |= 0x3; // Baudrate fraction
	
	USART3->CR1 |= 0X01 << 13; // UE Usart enable
	USART3->CR1 |= 0X01 << 2; // RE Read enable
	USART3->CR1 |= 0X01 << 3; // TE Transmitter enable
	
	if(interrupzioak){
		USART3->CR1 |= 0X01 << 5;// RXNEIE Interrupzioa irakurri duenean
		USART3->CR1 |= 0X01 << 6;// TCIE Interrupzioa idatzi duenean
	  NVIC->ISER[39/32] |= 0X01 << (39 % 32);
	}

}

/*
/ Usart 3k funtzionatzeko behar dituen gpio portuak martxan jartzen ditu
*/
void initGPIOUsart3(){
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,1);
	initGpioPinMode(GPIOD,USART3_TX,GPIO_Mode_AF);
	initGpioPinMode(GPIOD,USART3_RX,GPIO_Mode_AF);
	setGpioPinAF(GPIOD,8,7);
	setGpioPinAF(GPIOD,9,7);
}
/*
/ Agindutako byte luzera bidaltzen du. 
/ Byte guztiak DR.ra kopiatu arte ez da funtzioa bukatzen
*/
void writeUart3Blocking(uint8_t *mezua, uint32_t luzera){
	while(luzera != 0){
		writeByte(*mezua);
		luzera--;
		mezua++;
	}
}

/*
/ Byte bakarra bidaltzen du
*/
void writeByte(uint8_t  mezua){
	while(!(USART3->SR & 0X01<<7));
	USART3->DR = mezua;
}

/*
/ Mezua bufferrera kopiatzen du ahal denean bidaltzeko
*/
void writeUart3(uint8_t *mezua, uint32_t luzera){
	while(luzera != 0 && bufferIrakurri.size != BUFFER_SIZE){
		pushBuffer(&bufferIdatzi, *mezua++);
		luzera--;
	}
	writeByte(popBuffer(&bufferIdatzi));
}

/*
/ Aurretik irakurritakoa (buferrean dagoena) kopiatzen du
*/
uint32_t readUart3(uint8_t *pMsg, uint32_t maxLen){
	uint32_t byteKop = 0;
	while(maxLen != 0 && bufferIrakurri.size != 0){
		*pMsg++ = popBuffer(&bufferIrakurri);
		maxLen--;
		byteKop++;
	}
	return byteKop;
}

/*
/ Interrupzioak
/ Irakurri duenean: irakurritako bytea buferrean idazten du
/ Idazten duenean: buferreko hurrengo bytea idazten du bidaltzeko
*/
void ourUSART3Handler(){
	uint32_t sr = USART3->SR;
	if(sr & 0X01<<5){ // RXNE
		uint8_t irakurri = USART3->DR;
		pushBuffer(&bufferIrakurri,irakurri);
	}else if(sr & 0x01 << 6){ // TC
		if(bufferIdatzi.size != 0){
			USART3->DR = popBuffer(&bufferIdatzi);
		}else{
			USART3-> SR &= ~(0x01 << 6); // TC
		}
	}
}

