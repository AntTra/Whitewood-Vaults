#include "gpio.h"
#include <stdint.h>

#define UART ((NRF_UART_REG *)0x40002000) // UART register base address

typedef struct {
  volatile uint32_t STARTRX;
  volatile uint32_t STOPRX;
  volatile uint32_t STARTTX;
  volatile uint32_t STOPTX;
  volatile uint32_t RESERVED5[3];
  volatile uint32_t SUSPEND;
  volatile uint32_t RESERVED6[56];
  volatile uint32_t CTS;
  volatile uint32_t NCTS;
  volatile uint32_t RXDRDY;
  volatile uint32_t RESERVED7[4];
  volatile uint32_t TXDRDY;
  volatile uint32_t RESERVED8[1];
  volatile uint32_t ERROR;
  volatile uint32_t RESERVED9[7];
  volatile uint32_t RXTO;
  volatile uint32_t RESERVED10[110];
  volatile uint32_t INTEN;
  volatile uint32_t INTENSET;
  volatile uint32_t INTENCLR;
  volatile uint32_t RESERVED0[93];
  volatile uint32_t ERRORSRC;
  volatile uint32_t RESERVED1[31];
  volatile uint32_t ENABLE;
  volatile uint32_t RESERVED2[1];
  volatile uint32_t PSELRTS;
  volatile uint32_t PSELTXD;
  volatile uint32_t PSELCTS;
  volatile uint32_t PSELRXD;
  volatile uint32_t RXD;
  volatile uint32_t TXD;
  volatile uint32_t RESERVED3[1];
  volatile uint32_t BAUDRATE;
  volatile uint32_t RESERVED4[17];
  volatile uint32_t CONFIG;
} NRF_UART_REG;

void uart_init() {

  GPIO0->PIN_CNF[6] = 0x0; // RX
  GPIO1->PIN_CNF[8] = 0x1; // TX

  UART->PSELRXD = 0x28; //
  UART->PSELTXD = 0x6;  //

  UART->BAUDRATE = 0x00275000; // Baudrate 9600 fra datablad s.513

  UART->PSELCTS = 0x1; // Disabler CTS-tilkobling
  UART->PSELRTS = 0x1; // Disabler RTS-tilkobling

  UART->ENABLE = 0x4;  // Skru på UART-modul
  UART->STARTRX = 0x1; // Start å ta i mot meldinger
};

void uart_send(char letter) {

  UART->STARTTX = 0x1; // Start overføring
  UART->TXD = letter;  // Skriv byte (letter) til TXD registeret

  while (!(UART->TXDRDY)) { // Sjekker om byte er sendt
  }

  UART->TXDRDY = 0x0; // Setter registeret lavt for at en ny byte kan skrives
                      // til TXD-registeret (datablad s. 486)
  UART->STOPTX = 0x1; // Stopp overføring
};

char uart_read() {
  if (UART->RXDRDY) {
    UART->RXDRDY = 0x0; // Settes til 0 for å unngå pakketap før RXD blir lest
    return UART->RXD;
  }
  return '\0';
};
