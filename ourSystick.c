#include "ourSystick.h"

uint32_t systicks = 0;
uint32_t systickOld = 0;

void initSysTick(uint32_t ms, uint32_t internalClk){
	SysTick -> CTRL &= ~(0X01 <<2); // AHB / 8 erabili
	SysTick -> CTRL |= 0X01 << 1; //TICKINT Enable interrupt
	if(internalClk){
		SysTick -> LOAD = 16000000 / 8 / 1000 * ms - 1UL; 
	}else{
		RCC -> CR |= 0X01 << 16; // HSE ENABLE
		//while(!(RCC -> CR & (0x01 << 17)));
		RCC -> CFGR |= 0X01; // HSE AUKERATU HSI BEHARREAN
		SysTick -> LOAD = 25000000 / 8 / 1000 * ms - 1UL; 
	}
	SysTick -> VAL = 0UL;
	SysTick -> CTRL |= 0X01; // ENABLE
}

uint32_t getSysTicks(void){
	return systicks;
}

void waitNextSysTick(void){
	while(systicks == systickOld);
	systickOld++;
}

void ourSysTickHandler(void){
	systicks++;
}
