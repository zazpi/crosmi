#ifndef OUR_USART_H
#define OUR_USART_H

#include <stdint.h>
#include <stm32f407xx.h>

typedef enum e_Com {COM1,COM2} COM;

void initCom(uint32_t baudRate);
void writeToUart(uint8_t *pMsg);
void ourUSART3Handler(void);
void readFromUart (void);
int getBidali (void);

#endif
