#ifndef PWM_H
#define PWM_H
#include <avr/io.h> // for register variables
#include "gpio.h"


int hasPwm(int pin) { // returns combined boolean for each pin
    return (pin == 3)  | (pin == 5) | (pin == 6) | (pin == 9) |
           (pin == 10) | (pin == 11);
}

int setAnalogPin(int pin, unsigned char value) {
    setPinMode(pin, OUTPUT); // insure pin is output
    if(hasPwm(pin)) {
        
        /*
            Settings by defualt are set to clear regsiter (OC#$) on compare match of corresponding 
            counter register
            Mode is set to PWM, phase correct
            Clock Select bits are set to no prescaler (CS#0) enabled only
        */        

        switch(pin) {
                case 3:

                    TCCR2A |=  (1 << COM2B1); // enable OC2B output
                    TCCR2A |= (1 << WGM20);
                    TCCR2B = 1 << CS20; 
                    OCR2B = value;
                    
                    break; 
                case 5:
                    TCCR0A |=  (1 << COM0B1);  // enable OC0B output
                    TCCR0A |= (1 << WGM00); 
                    TCCR0B = 1 << CS00;    
                    OCR0B = value;
                    
                    break;
                case 6:
                    TCCR0A |=  (1 << COM0A1);  // enable OC0A output
                    TCCR0A |= (1 << WGM00);
                    TCCR0B = 1 << CS00;
                    OCR0A = value;
                    
                    break;
                case 9:
                    TCCR1A |= (1 << COM1A1); // enable OC1A output
                    TCCR1A |= (1 << WGM10);
                    TCCR1B = 1 << CS10;
                    OCR1A = value;
                    break;
                case 10:
                    
                    TCCR1A |= (1 << COM1B1); // enable OC1B output
                    TCCR1A |= (1 << WGM10);
                    TCCR1B = 1 << CS10;
                    OCR1B = value;
                    
                    break;
                case 11:
                    
                    TCCR2A |= (1 << COM2A1);
                    TCCR2A |= (1 << WGM20); 
                    TCCR2B = 1 << CS20; 
  
                    OCR2A = value;
                    
                    break;
                default:
                    break;

        }     
    } else { // if a pin doesn't have pwm capability round to either HIGH or LOW
        if(value > 128) writeDigitalPin(pin, 1);
        else writeDigitalPin(pin, 0);
    }    
    return 0;

}



#endif