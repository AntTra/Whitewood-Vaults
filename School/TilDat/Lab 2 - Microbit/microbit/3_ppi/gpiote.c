#include "gpiote.h"

void init_GPIOTE() {

  GPIOTE->CONFIG[0] = (1 | (14 << 8) | (2 << 16));
  GPIOTE->CONFIG[1] = (3 << 0) | // AA; (Task mode)
                      (21 << 8) | // BBBBB; (pin select; pins 0 through 4.)
                      (0 << 13) | // C; (port nr.)  
		      (3 << 16) | // DD; (DD=3 -> Toggle - Generate IN[n] when any change on pin.)
                      (0 << 20); // E; (E=0 -> Initial value of pin before task triggering is low);

    GPIOTE->CONFIG[2] = (3 << 0) | (22 << 8) | (3 << 16);
    GPIOTE->CONFIG[3] = (3 << 0) | (15 << 8) | (3 << 16);
    GPIOTE->CONFIG[4] = (3 << 0) | (24 << 8) | (3 << 16);
    GPIOTE->CONFIG[5] = (3 << 0) | (19 << 8) | (3 << 16);
}
