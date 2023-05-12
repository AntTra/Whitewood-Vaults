#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main() {

  GPIO0->PIN_CNF[14] = 0; // button A
  GPIO0->PIN_CNF[23] = 0; // button B

  // Configure leds
  GPIO0->PIN_CNF[21] = 1; // Row 1
  GPIO0->PIN_CNF[22] = 1; // Row 2
  GPIO0->PIN_CNF[15] = 1; // Row 3
  GPIO0->PIN_CNF[24] = 1; // Row 4
  GPIO0->PIN_CNF[19] = 1; // Row 5

  GPIO0->PIN_CNF[28] = 1; // Col 1
  GPIO0->PIN_CNF[11] = 1; // Col 2
  GPIO0->PIN_CNF[31] = 1; // Col 3
  GPIO1->PIN_CNF[5] = 1;  // Col 4
  GPIO0->PIN_CNF[30] = 1; // Col 5

  init_PPI();
  init_GPIOTE();

  while (1) {
  };

  return 0;
}
