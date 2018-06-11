#include "ourUsart.h"
#include "ourPintza.h"
#include "ourRccGpio.h"
#include "ourSystick.h"

void irakurri(void);
void initGPIO(void);

uint32_t piztuta = 1;

int main(){
	initGPIO();
	initUsart3(9600,1);
	initSysTick(1000,1);
	initPintza();
	
	uint16_t kontsumoa;
	for(;;){
		togleGpioPinValue(GPIOF, 6);
		if(piztuta){
			kontsumoa = getAzkenKontsumoa();
			writeUart3((uint8_t*)&kontsumoa,2);
		}	
		waitNextSysTick();
		irakurri();
	}
}

void irakurri(void){
	uint8_t komandoak[5];
	uint32_t n = readUart3(komandoak,5);
	
	for(uint32_t i = 0; i < n; i++){
		switch(komandoak[i]){
			case (uint8_t) ~0: // Power on
				powerPintza(1);
				piztuta = 1;
				break;
			case (uint8_t) 0: // Power off
				powerPintza(0);
			  piztuta = 0;
				break;
			default:
				break;
		}
	}
}

    
void initGPIO(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, 1);
  initGpioPinMode(GPIOF, 6, GPIO_Mode_OUT);
}
