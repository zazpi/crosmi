#ifndef OUR_USART_H
#define OUR_USART_H

#include <stdint.h>
#include <stm32f407xx.h>

typedef enum e_Com {COM1,COM2} COM;

void initCom(uint32_t baudRate);
//uint32_t readFromUart(COM com, uint8_t *pMsg, uint32_t maxLen);
//void blockingWriteToUart(COM com, uint8_t *pMsg, uint32_t len);
void writeToUart(uint8_t *pMsg);


#endif
