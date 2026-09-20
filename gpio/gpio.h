#ifndef GPIO_H
#define GPIO_H

/*
    moved the ADC input pins (PORTC pins) to be inline 
    with a multiple of 8/alligned with byte addr
*/

#define A0 16
#define A1 17
#define A2 18
#define A3 19
#define A4 20
#define A5 21
#define A6 22

enum  pinMode { // enum to replace modes in arduino ide
    INPUT,
    OUTPUT,
    PULLUP
};

uint16_t* pinToDirectionRegister(char pin) { 
    if(pin < 8) {
        return (uint16_t*)&DDRD;
    } else if(pin < 14) {
        return (uint16_t*)&DDRB;
  } else if(pin > 15 && pin < 23) {
        return (uint16_t*)&DDRC;
  } else {
        return nullptr;
  }
}

uint16_t* pinToOutRegister(char pin) { // returns pointer to addr of Output register of selected pin
    if(pin < 8) {
        return (uint16_t*)&PORTD;
    } else if(pin < 14) {
        return (uint16_t*)&PORTB;
    } else if(pin < 20) {
        return (uint16_t*)&PORTC;
    } else {
        return nullptr;
    }
}

uint16_t* pinToInRegister(char pin) { // returns pointer to addr of Input register of selected pin
    if(pin < 8) {
        return (uint16_t*)&PIND;
    } else if(pin < 14) {
        return (uint16_t*)&PINB;
    } else if(pin < 20) {
        return (uint16_t*)&PINC;
    } else {
        return nullptr;
    }
}


 
void setPinMode(unsigned int pin, unsigned int mode) { 
    
    uint16_t* dirReg = pinToDirectionRegister(pin);
    if(dirReg == nullptr)  return; // if pin does not belong to a port return nullptr
    
    switch(mode) {
        case INPUT:
            *dirReg &= ~_BV(pin % 8);
            break;
        case OUTPUT:
            *dirReg |= _BV(pin % 8);
            break;
        case PULLUP:
            *pinToOutRegister(pin) |= _BV(pin % 8);
            *dirReg &= ~_BV(pin % 8); 
            break;
        default:
            return;
            break;

    }
}

int readDigitalPin(unsigned char pin) {
  uint16_t* portReg = pinToInRegister(pin);
  if(portReg == nullptr) return -1; // if pin does not belong to a port return nullptr
  setPinMode(pin, INPUT);
  

  return (*portReg & _BV(pin % 8)) != 0;
    
}


void writeDigitalPin(unsigned char pin, unsigned char val) {
  uint16_t* portReg = pinToOutRegister(pin);
  if(portReg == nullptr) return;
  
  setPinMode(pin, OUTPUT);
  
  if(val) {
    *portReg |= _BV(pin % 8);
  } else {
    *portReg &= ~_BV(pin % 8);
  }
}

#endif