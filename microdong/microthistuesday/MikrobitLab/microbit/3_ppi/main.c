#include "ppi.h"
#include "gpiote.h"
#include "gpio.h"


int main() {

	GPIO0->PIN_CNF[28] = 1; //Col 1
	GPIO0->PIN_CNF[11] = 1; //Col 2
	GPIO0->PIN_CNF[31] = 1; //Col 3
	GPIO1->PIN_CNF[5] = 1;  //Col 4
	GPIO0->PIN_CNF[30] = 1; //Col 5 
    
    init_PPI();
    init_GPIOTE();
    while(1){
        // Do nothing
    };
    return 0;
}