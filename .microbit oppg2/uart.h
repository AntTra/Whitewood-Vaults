#ifndef UART_H
#define UART_H

#define UARTE0 ((NRF_UART_REG*)0x40002000) 
#define UARTE1 ((NRF_UART_REG*)0x40028000)

void uart_init();
void uart_send(char letter);
char uart_read();


#endif