#include "gpio.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include ".build_system/nrf.h"

ssize_t _write(int fd, const void *buf, size_t count) {
  char *letter = (char *)(buf);
  for (int i = 0; i < count; i++) {
    uart_send(*letter);
    letter++;
  }

  return count;
}
int main() {
  gpio_init();
  uart_init();

  int sleep = 0;

  iprintf("The average grade in TTK%d was in %d, and %d: %c\n\r", 4235, 2019,
          2018, 'C');

  while (1) {
    if (!(GPIO0->IN & (1 << 14))) { // Hvis knapp A trykkes, send A
      uart_send('A');
      gpio_lights_on();
    }
    if (!(GPIO0->IN & (1 << 23))) { // Hvis knapp B trykkes, send B
      uart_send('B');
      gpio_lights_off();
    }
    if (uart_read() != '\0') {
      if (GPIO0->OUT & (1 << 21)) {
        gpio_lights_off();
      } else {
        gpio_lights_on();
      }
    }
    sleep = 10000;
    while (--sleep)
      ;
  }
  return 0;
}
