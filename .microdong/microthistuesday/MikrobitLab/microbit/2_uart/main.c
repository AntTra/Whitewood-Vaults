#include <stdio.h>
#include "uart.h"
#include "gpio.h"

#define __BUTTON_A_PIN__ 14
#define __BUTTON_B_PIN__ 23

int btn_b_pressed() {
	return(!(GPIO0->IN & (1 << 23)));
}

int btn_a_pressed() {
	return(!(GPIO0->IN & (1 << 14)));
}	

void uart_send_str(char ** str){
    UART->TASKS_STARTTX = 1;
    char * letter_ptr = *str;
    while(*letter_ptr != '\0'){
        UART->TXD = *letter_ptr;
        while(!UART->EVENTS_TXDRDY);
        UART->EVENTS_TXDRDY = 0;
        letter_ptr++;
    }
}

ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
        uart_send(*letter);
        letter++;
    }
    return count;
}

int main(){
    uart_init();

    gpio_init();

    int sleep = 0;
    while(1){
        if(btn_b_pressed()){
            uart_send('B');
        }
        if(btn_a_pressed()){
            uart_send('A');
            iprintf("The average grade in TTK%d was in %d and %d: %c\n\r",4235,2019,2018,'C');
        }
        if(uart_read() != '\0'){
            if(GPIO0->OUT & (1 << 21)){
                gpio_lights_off();
            } else{
                gpio_lights_on();
            }
        }

    sleep = 10000;
	while(--sleep);
    }
    


    return 0;
}