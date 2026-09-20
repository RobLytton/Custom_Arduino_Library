#ifndef I2C_H
#define I2C_H

#include <avr/io.h>

static uint16_t TxBuffer[];
static uint16_t RxBuffer[];

void startCond() { // bits that tell hardware to generate a start condition
  TWCR |= (1 << TWINT) | (1 << TWSTA) | (1 << TWEN) & ~(1 << TWSTO); 
  
}  

void stopCond() { // bits that tell hardware to generate a stop condition
  TWCR |= (1 << TWINT) | (1 << TWSTO) | (1 << TWEN) & ~(1 << TWSTA);
}

void dataCond() { // bits that tell hardware to start sending the byte stored in TWDR;
  TWCR |= (1 << TWINT) | (1 << TWEN) & ~(1 << TWSTO) & ~(1 << TWSTA);
  
}

byte loadAddr(byte addr, byte dir) { // loads what address to request or read from and the direction of transfer
  TWDR = (addr << 1) | (dir & 1);
}

void setMaster() { // place holder to set device to a master of i2c bus

}

void setSlave() { // place holder to set device to slave on i2c bus

}

void setAddr() { // place holder to set address of device when in slave mode
    
}

byte sendByte(byte data) {  // places byte on data register to be sent by hardware
  while(!(TWSR & (1 << TWINT))); // wait till hardware is ready for next byte
  TWDR = data;
  dataCond();
  return TWSR;
}

#endif