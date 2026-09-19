#ifndef I2C_H
#define I2C_H

#include <avr/io.h>

static uint16_t TxBuffer[];
static uint16_t RxBuffer[];

void startCond() {
  TWCR |= (1 << TWINT) | (1 << TWSTA) | (1 << TWEN) & ~(1 << TWSTO);
  
}  

void stopCond() {
  TWCR |= (1 << TWINT) | (1 << TWSTO) | (1 << TWEN) & ~(1 << TWSTA);
}

void dataCond() {
  TWCR |= (1 << TWINT) | (1 << TWEN) & ~(1 << TWSTO) & ~(1 << TWSTA);
  
}

byte loadAddr(byte addr, byte dir) {
  TWDR = (addr << 1) | (dir & 1);
}


byte sendByte(byte data) {
  while(!(TWSR & (1 << TWINT)));
  TWDR = data;
  dataCond();
  return TWSR;
}

#endif