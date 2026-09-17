#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>
#include "../tools.h"

#define A0 16
#define A1 17
#define A2 18
#define A3 19
#define A4 20
#define A5 21
#define A6 22

enum  pinMode {
    INPUT,
    OUTPUT,
    PULLUP
};

char* pinToDirectionRegister(char pin) {
    if(pin < 8) {
        return DDRD;
    } else if(pin < 14) {
        return DDRB;
  } else if(pin < 20) {
        return DDRC;
  } else {
        return nullptr;
  }
}

char* pinToPortRegister(char pin) {
    if(pin < 8) {
        return PORTD;
    } else if(pin < 14) {
        return PORTB;
    } else if(pin < 20) {
        return PORTC;
    } else {
        return nullptr;
    }
}

char setPinMode(unsigned char pin, unsigned char mode) {
    if(pinToDirectionRegister(pin) == nullptr) return -1;
    if(pinToPortRegister(pin) == nullptr) return -1;    
    switch(mode) {
        case INPUT:
           pinToDirectionRegister(pin) &=  ~(1 << (pin % 8));
           break;
        case OUTPUT:
            _SB(pinToDirectionRegister(pin), pin % 8);
            break;
        case PULLUP:
            _CB(pinToDirectionRegister(pin), pin % 8);
            _SB(pinToPortRegister(pin), pin % 8);
            break;
        case default:
            return -1;
    }
    return 0;
}

char readDigitalPin(unsigned char pin) {
    if(pinToPortRegister(pin) == nullptr || _RB(pinToDirectionRegister(pin), pin % 8) == OUTPUT) return -1;
    return _RB(pinToPortRegister(pin), pin % 8);
    
}

void writeDigitalPin(unsigned char pin, unsigned char val) {
    if(pinToPortRegister(pin) == nullptr || _RB(pinToDirectionRegister(pin), pin % 8) == INPUT) return -1;
    val ? _SB(pinToPortRegister(pin), pin % 8) : _CB(pinToPortRegister(pin), pin % 8);
}

#endif