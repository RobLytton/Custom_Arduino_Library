#ifndef SEVENSEGMENTDISPLAY_H
#define SEVENSEGMENTDISPLAY_H

#include "../comm/spi.h"
#include <avr/io.h>
static char CS;

const static int codes[] = {0b11111100,
                      0b01100000, 
                      0b11011010, 
                      0b11110010, 
                      0b01100110, 
                      0b10110110, 
                      0b10111111, 
                      0b11100000, 
                      0b11111110, 
                      0b11100110, 
                      0b11101110, 
                      0b00111110, 
                      0b00011010, 
                      0b01111010, 
                      0b10011110, 
                      0b10001110};

void _7SegmentBegin() {
    spiSetup();
    spiBitMode(MSBFIRST);
    DDRB |= (1 << PB2);
    PORTB |= (1 << PB2);
}

int setChipSelect(unsigned char pin) {
    if(pin == 12 | pin == 13 | pin == 11 | pin > 13) return -1;
    CS = pin;
    return pin;
}

int writeNum(unsigned int num) {
    if(num > 16) return -1;
    PORTB &= ~(1 << PB2);
    spiTransfer(codes[num]);
    PORTB |= (1 << PB2);
    return 0;
}

void _7SegmentStop() {
    spiStop();
}

#endif