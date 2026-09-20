#ifndef SPI_H
#define SPI_H
#include <avr/io.h>

#define SCLK PB5
#define CIPO PB4
#define COPI PB3

#define LSBFIRST 0
#define MSBFIRST 1


void spiSetup() {
    DDRB |= (1 << SCLK) | (1 << COPI); 
    DDRB &= ~(1 << CIPO); 
    SPCR |= (1 << SPE) | (1 << MSTR);
    
}

void spiBitMode(char mode) { // wirtes to the SPCR DORD for LSB or MSB first
   SPCR = mode ? SPCR | (1 << DORD) : SPCR & ~(1 << DORD);

}

char spiTransfer(char data) { 
    SPDR = data;

    while(!(SPSR & (1 << SPIF))); // wait for spi interrupt flag bit to be set by hardware

    return SPDR; // returned data received by peripheral device
}

void spiSetSlave() { // sets spi hardware to acts as a slave
    SPDR &= ~(1 << MSTR); 
}



void spiStop() {
    SPCR &= ~(1 << SPE);
}




#endif