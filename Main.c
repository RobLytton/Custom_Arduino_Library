#include <avr/io.h>
#include <util/delay.h>
#include "comm/spi.h"
int main() {
    
    DDRB |= (1 << PB5);
    while(1) {
        PORTB |= (1 << PB5);
        _delay_ms(10000);

        PORTB &= ~(1 << PB5);
        _delay_ms(10000);
    }
    return 0;
}