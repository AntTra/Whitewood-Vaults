#include "gpio.h"
#include "uart.h"
#include <stdio.h>

int main(){
    int sleep = 0;
	uart_init();
	while(1){
		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		if(!(GPIO0->IN & (1<<23))){
            uart_send('B');
		}

		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		if(!(GPIO0->IN & (1<<14))){
            uart_send('A');
		}

		sleep = 10000;
		while(--sleep);
	}
    

}

