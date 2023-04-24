#include "gpiote.h"

void init_GPIOTE(){
    //setter A-knappen til event
    GPIOTE->CONFIG[0] = 1 | (1 << 17) | (14 << 8);
    //setter LED-matrisen til task
    GPIOTE->CONFIG[1] = 3 | (3 << 16) | (21 << 8);
    GPIOTE->CONFIG[2] = 3 | (3 << 16) | (22 << 8);
    GPIOTE->CONFIG[3] = 3 | (3 << 16) | (15 << 8);
    GPIOTE->CONFIG[4] = 3 | (3 << 16) | (24 << 8);
    GPIOTE->CONFIG[5] = 3 | (3 << 16) | (19 << 8);
}