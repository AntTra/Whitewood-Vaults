#ifndef GPIOTE_H
#define GPIOTE_H
#include <stdint.h>

#define GPIOTE ((NRF_GPIOTE_REG *)0x40006000)

typedef struct {
  // Tasks
  volatile uint32_t TASKS_OUT[8]; // 0x000. Last cell: 0x01c (TASKS_OUT[7] =
                                  // 0x01c). 0x030-0x01c = 48 - 28 = 20 -> 5
  volatile uint32_t RESERVED0[4]; // 0x030-0x000 = 48 -> 12
  volatile uint32_t TASKS_SET[8]; // 0x030
  volatile uint32_t RESERVED1[4]; // 0x060-0x030 = 48 -> 12
  volatile uint32_t TASKS_CLR[8]; // 0x060. Last: 0x07c
  // Events
  volatile uint32_t RESERVED2[32]; // From last: 0x100-0x07c = 132 -> 33.
                                   // 0x100-0x060 = 160 -> 40
  volatile uint32_t EVENTS_IN[8];  // 0x100.
  volatile uint32_t RESERVED3[23]; // 0x17c-0x011C = 96 -> 24
  volatile uint32_t EVENTS_PORT;   // 0x17c
  // Registers
  volatile uint32_t RESERVED4[97];  // 0x304-0x17c = 392 -> 98
  volatile uint32_t INTENSET;       // 0x304
  volatile uint32_t INTENCLR;       // 0x308
  volatile uint32_t RESERVED5[129]; // 0x510-0x308 = 520 -> 130
  volatile uint32_t CONFIG[8];      // Sum = 0x510 :)
} NRF_GPIOTE_REG;

#endif

void init_GPIOTE();
