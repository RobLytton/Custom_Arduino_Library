#ifndef SEVENSEGMENTDISPLAY_H
#define SEVENSEGMENTDISPLAY_H

#include "../comm/spi.h"
#include <avr/io.h>
static char CS;
/*
    maps bits to wire going to each segment of the 7 segment display
*/
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

/*
    _7SegmentBeing() basically sets up the SPI hardware as this driver works with a
    74HC595N shift register to save pins
*/

void _7SegmentBegin() { 
    spiSetup();
    spiBitMode(MSBFIRST);
    DDRB |= (1 << PB2);
    PORTB |= (1 << PB2);
}

int setChipSelect(unsigned char pin) { // method for custom pin
    if(pin == 12 | pin == 13 | pin == 11 | pin > 13) return -1;
    CS = pin;

    return 0;
}

int writeNum(unsigned int num) { // uses SPI to communicate with shift register
    if(num > 16) return -1;
    PORTB &= ~(1 << PB2);
    spiTransfer(codes[num]);
    PORTB |= (1 << PB2);
    return 0;
}

void _7SegmentStop() { // disabled SPI hardware to free it for use 
    spiStop();
}

#endif