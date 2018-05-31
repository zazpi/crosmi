#ifndef OUR_USART_H
#define OUR_USART_H

#include <stdint.h>
#include <stm32f407xx.h>

void initUsart3(uint32_t baudRate, uint32_t interrupzioak);

// Interrupzioekin
void writeUart3(uint8_t *mezua, uint32_t luzera);
uint32_t readUart3(uint8_t *pMsg, uint32_t maxLen);
// Interrupzio gabe
void writeUart3Blocking(uint8_t *mezua, uint32_t luzera);
void writeByte(uint8_t mezua);
// Interrupzioak
void ourUSART3Handler(void);

void writeToUart(uint8_t *pMsg);


#endif
