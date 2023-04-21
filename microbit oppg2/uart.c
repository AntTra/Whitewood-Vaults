#include "uart.h"
#include "gpio.h"
#include <stdint.h>
#include <stdio.h>

typedef struct{ 
    // UART Tasks Registers
    volatile uint32_t STARTRX;
    volatile uint32_t STOPRX;
    volatile uint32_t STARTTX;
    volatile uint32_t STOPTX;
    volatile uint32_t RESERVED0[3];
    volatile uint32_t SUSPEND;
    volatile uint32_t RESERVED1[56];
    // UART Events Registers
    volatile uint32_t CTS;
    volatile uint32_t NCTS;
    volatile uint32_t RXDRDY;
    volatile uint32_t RESERVED2[4];
    volatile uint32_t TXDRDY;
    volatile uint32_t RESERVED3;
    volatile uint32_t ERROR;
    volatile uint32_t RESERVED4[7];
    volatile uint32_t RXTO;
    volatile uint32_t RESERVED5[110];
    // UART Registers
    volatile uint32_t INTEN;
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED6[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED7[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED8;
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED9;
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED10[17];
    volatile uint32_t CONFIG;
}NRF_UART_REG;




void uart_init(){
    gpio_init();
    //Setting pins
    GPIO0->PIN_CNF[6] = 0; //RXD
    GPIO1->PIN_CNF[8] = 1; //TXD

    //Setting TXD
    //UARTE0->PSELTXD = 8;
    UARTE0->PSELTXD = 0x06;
    
    //Setting RXD
    //UARTE0->PSELRXD = 6;
    UARTE0->PSELRXD = 0x28;

    //Disconnecting pins
    UARTE0->PSELCTS = 0xFFFFFFFF;
    UARTE0->PSELRTS = 0xFFFFFFFF;

    UARTE0->BAUDRATE = 0x00275000;

    UARTE0->ENABLE = 4;
    UARTE0->STARTRX = 1;
}

void uart_send(char letter){
    UARTE0->STARTTX = 1;
    UARTE0->TXD = letter;
    
    while(UARTE0->TXDRDY != 1){
        //wait
    }
    UARTE0->TXDRDY = 0;
    UARTE0->STOPTX = 1;
}

char uart_read(){
    UARTE0->STARTRX = 1;
    if(UARTE0->RXDRDY != 1){
        return '\0';
    }
    UARTE0->RXDRDY = 0;
    char letter = UARTE0->RXD;
    return letter;
} 

