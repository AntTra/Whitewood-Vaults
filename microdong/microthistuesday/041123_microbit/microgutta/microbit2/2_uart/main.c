#include "uart.h"
#include "gpio.h"

int main(){

    gpio_init();
    uart_init();
	
	int sleep = 0;
	
	while(1){

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		 
		if (!(GPIO0->IN & (1<<14))){
			uart_send('a');
			gpio_lights_on();
		}
		
		if (!(GPIO0->IN & (1<<23))){
            uart_send('b');
			gpio_lights_off();
		}

		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}