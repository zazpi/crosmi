#include "ourUsart.h"
#include "ourTimer.h"
#include "ourADC.h"

#include <stdint.h>

int main(){
	initCom(9600);
	initTimer2(20);
	initADC();
	
	for(;;){
	 //writeToUart((uint8_t *)"hodei");
	}
}
