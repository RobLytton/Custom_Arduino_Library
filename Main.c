#include <avr/io.h>
#include <util/delay.h>
#include "comm/spi.h"
int main() {

    
    spiSetup();
    spiBitMode(MSBFIRST);
    while(1) {
        
    }
    return 0;
}