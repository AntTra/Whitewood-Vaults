#include "gpio.h"
#include "uart.h"

void uart_init(){
    GPIO0->PIN_CNF[6]=0; //0 SIDEN RECIEVE INPUT?
    GPIO1->PIN_CNF[8]=0;
    UART->PSEL_TXD=0x80000008;
    UART->PSEL_RXD=0x00000006;
    UART->BAUDRATE=0x00275000;
    UART->PSEL_RTS=(1<<5);
    UART->PSEL_CTS=(1<<5);
    UART->ENABLE=0x4;
    UART->TASKS_STARTRX=1; //start reiciever WHY
}

void uart_send(char letter){
    UART->TASKS_STARTTX=1;
    UART->TXD=letter;
    int sleep = 0;
    while (!(UART->EVENTS_TXDRDY))
    {
        sleep = 10000;
		while(--sleep);
    }
    UART->EVENTS_TXDRDY=0;
    UART->TASKS_STOPTX=1;
}

char uart_read(){
    
    if (UART->EVENTS_RXDRDY)
    {
        UART->EVENTS_RXDRDY=0;
        return UART->RXD;
    }
    return '\0';
    
}