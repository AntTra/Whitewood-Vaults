#include "uart.h"


void uart_init(){
    //sett RDX = 0.6 til input
    GPIO0->PIN_CNF[6] = 0;
    //sett TXD = 1.8 til output
    GPIO1->PIN_CNF[8] = 1;
    UART->PSEL_TXD = 6;
    UART->PSEL_RXD = 0x28;
    UART->BAUDRATE = 0x00275000;
    UART->ENABLE = 4;
    UART->PSEL_CTS = ~0;
    UART->PSEL_RTS = ~0;
    UART->TASKS_STARTRX = 1;
}

void uart_send(char letter){
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;
    while(!(UART->EVENTS_TXDRDY)){};
    UART->EVENTS_TXDRDY = 0;
    UART->TASKS_STOPTX = 1;
}

char uart_read(){
    if(UART->EVENTS_RXDRDY){
        return UART->RXD;
    }
    return '\0';
}