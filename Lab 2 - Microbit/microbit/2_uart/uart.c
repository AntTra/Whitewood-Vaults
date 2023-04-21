#include "gpio.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

#define UART ((NRF_UART_REG*)0x40002000) //uart 0 base adress
#define GPIO0 ((NRF_GPIO_REGS0*)0x50000000) //gpio 0 base adress
#define GPIO1 ((NRF_GPIO_REGS1*)0x50000300) //gpio 1 base adress

typedef struct {
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTX;
    volatile uint32_t TASKS_STOPTX;
    volatile uint32_t RESERVED_0[3];
    volatile uint32_t TASKS_SUSPEND;
    volatile uint32_t RESERVED_1[56];
    volatile uint32_t EVENTS_CTS;
    volatile uint32_t EVENTS_NCTS;
    volatile uint32_t EVENTS_RXDRDY;
    volatile uint32_t RESERVED_2[4];
    volatile uint32_t EVENTS_TXDRDY;
    volatile uint32_t RESERVED_3;
    volatile uint32_t EVENTS_ERROR;
    volatile uint32_t RESERVED_4[7];
    volatile uint32_t EVENTS_RXTO;
    volatile uint32_t RESERVED_5[46];
    volatile uint32_t SHORTS;
    volatile uint32_t RESERVED_6[64];
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED_7[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED_8[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED_9;
    volatile uint32_t PSEL_RTS;
    volatile uint32_t PSEL_TXD;
    volatile uint32_t PSEL_CTS;
    volatile uint32_t PSEL_RXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED_10;
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED_11[17];
    volatile uint32_t CONFIG;
} NRF_UART_REG;

void uart_init(){

    // Configure CPIO pins (dere må sjekke selv hvilken GPIO modul de ulike knappene tilhører)
    GPIO1->PIN_CNF[8] = 1; //Output from MCU to UART //TX
    GPIO0->PIN_CNF[6] = 0; //Input for MCU from UART //RX

    //brukes av UART-modulen
    UART->PSEL_TXD = 0x06; 
    UART->PSEL_RXD = 0x28;

    //badurate lik 9600
    UART->BAUDRATE = 0x00275000;

    //ingen CTS eller RTS
    UART->PSEL_CTS = 0xFFFFFFFF;
    UART->PSEL_RTS = 0xFFFFFFFF;

    //skru på UART modul
    UART->ENABLE = 0x4;

    // Configure leds (dere må sjekke selv hvilken GPIO modul de ulike knappene tilhører)
	GPIO0->PIN_CNF[21] = 1; //Row 1
	GPIO0->PIN_CNF[22] = 1; //Row 2
	GPIO0->PIN_CNF[15] = 1; //Row 3
	GPIO0->PIN_CNF[24] = 1; //Row 4
	GPIO0->PIN_CNF[19] = 1; //Row 5

	GPIO0->PIN_CNF[28] = 1; //Col 1
	GPIO0->PIN_CNF[11] = 1; //Col 2
	GPIO0->PIN_CNF[31] = 1; //Col 3
	GPIO1->PIN_CNF[5] = 1;  //Col 4
	GPIO0->PIN_CNF[30] = 1; //Col 5 
	
	// Configure buttons (dere må sjekke selv hvilken GPIO modul de ulike knappene tilhører)
	GPIO0->PIN_CNF[14] = 0; // button A 
	GPIO0->PIN_CNF[23] = 0; // button B
}

void uart_send(char letter){
    UART->TASKS_STARTTX = 0x1;
    UART->TXD = letter;
    while(UART->EVENTS_TXDRDY != 0x1){
        continue;
    }
    UART->TASKS_STOPTX = 0x1;
}

char uart_read(){
    UART->TASKS_STARTRX = 0x1;
    if(!UART->EVENTS_RXDRDY){
        return '\0';
    }
    else{
        return UART->RXD;
    }
}
