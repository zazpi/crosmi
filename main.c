#include "ourUsart.h"
#include "ourTimer.h"
#include "ourADC.h"
#include "ourPintza.h"
#include "ourRccGpio.h"
#include "ourSystick.h"
void irakurri(void);
void initGPIO(void);

int main(){
	initGPIO();
	initUsart3(9600,1);
	initSysTick(1000,1);
	initPintza();
	uint16_t kontsumoa;
	for(;;){
		togleGpioPinValue(GPIOF, 6);
		kontsumoa = getAzkenKontsumoa();
		writeUart3((uint8_t*)&kontsumoa,2);
		waitNextSysTick();
	//	irakurri();
		
	}
}

void irakurri(void){
	uint8_t komandoa[2];
	uint32_t n = 0;
	
	while(n != 2){
		n += readUart3(komandoa+n,2);
	}
	writeUart3(komandoa,n);
}

    
void initGPIO(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, 1);
  initGpioPinMode(GPIOF, 6, GPIO_Mode_OUT);
}



