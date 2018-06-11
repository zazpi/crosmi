#include "ourSystick.h"

uint32_t systicks = 0;
uint32_t systickOld = 0;

/**
Initializes the System Tick core peripheral.
@param ms: uint32_t type sets the milliseconds for the clock
@param internalClk: uint32_t type optional parameter, acts as a boolean to know whether internal clock is needed.
@return void.
*/
void initSysTick(uint32_t ms, uint32_t internalClk){
	SysTick -> CTRL &= ~(0X01 <<2); // AHB / 8
	SysTick -> CTRL |= 0X01 << 1; //TICKINT Enable interrupt
	if(internalClk){
		SysTick -> LOAD = 16000000 / 8 / 1000 * ms - 1UL; 
	}else{
		RCC -> CR |= 0X01 << 16; // HSE ENABLE
		//while(!(RCC -> CR & (0x01 << 17)));
		RCC -> CFGR |= 0X01; // CHOOSE HSE INSEAD OF HSI
		SysTick -> LOAD = 25000000 / 8 / 1000 * ms - 1UL; 
	}
	SysTick -> VAL = 0UL;
	SysTick -> CTRL |= 0X01; // ENABLE
}

/**
Get the current system tick value.
@reurn systicks: uint32_t type ticks value.
*/
uint32_t getSysTicks(void){
	return systicks;
}
/**
This function is used to count until the next system tick.
@return void.
*/
void waitNextSysTick(void){
	while(systicks == systickOld);
	systickOld++;
}
/**
Interruption handler for SysTick.
@return void.
*/
void ourSysTickHandler(void){
	systicks++;
}
