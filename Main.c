#include <avr/io.h>
#include <util/delay.h>
#include "comm/spi.h"
#define CS PB2
#define RST PB1

int main() {
    spiSetup();
    spiBitMode(MSBFIRST);
    DDRB |= (1 << CS) | (1 << RST);
    PORTB |= (1 << CS) | (1 << RST);

    char i = 0;
    while(1) {
        PORTB &= ~(1 << CS);
        spiTransfer(i++);
        PORTB |= (1 << CS);
        _delay_ms(100);
    }
    return 0;
}