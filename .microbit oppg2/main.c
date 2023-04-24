#include "gpio.h"
#include "uart.h"
#include <stdio.h>


void oppgave_2_3(){
    int sleep = 0;
    while (1)
    {
        if(!(GPIO0->IN & (1<<14))){
            uart_send('a');
            gpio_lights_on();
        }
        else if(!(GPIO0->IN & (1<<23))){
            uart_send('b');
            gpio_lights_off();
        }

        sleep =10000;
        while(--sleep);
    }
}

void oppgave_2_4(){
    int lights = 0;

    while(1){
        if(uart_read() != '\0' && lights){
            gpio_lights_off();
            lights = 0;
        }
        else if(uart_read() != '\0' && !lights){
            gpio_lights_on();
            lights = 1;
        }
    }
}

void oppgave_2(){
    int lights = 0;

    while(1){
         if(!(GPIO0->IN & (1<<14))){
            uart_send('a');
            gpio_lights_on();
        }
        else if(!(GPIO0->IN & (1<<23))){
            uart_send('b');
            gpio_lights_off();
        }
        else if(uart_read() != '\0' && lights == 1){
            gpio_lights_off();
            printf("Dette skjedde /n");
            lights =0;

        }
        else if(uart_read() != '\0' && lights == 0){
            gpio_lights_on();
            lights =1;
        }
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

    oppgave_2_3();
    //oppgave_2_4();
    //oppgave_2();

    //Oppgave 2.5
    //iprintf("The average grade in TTK%d was in %d and %d: %c\n\r",4235,2019,2018, 'C');


    return 0;
}