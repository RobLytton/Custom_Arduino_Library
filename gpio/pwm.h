#ifndef PWM_H
#define PWM_H
#include <avr/io.h>
#include "gpio.h"


int hasPwm(int pin) {
    return (pin == 3)  | (pin == 5) | (pin == 6) | (pin == 9) |
           (pin == 10) | (pin == 11);
}

int setAnalogPin(int pin, unsigned char value) {
    setPinMode(pin, OUTPUT);
    if(hasPwm(pin)) {
        
        

        switch(pin) {
                case 3:

                    TCCR2A |=  (1 << COM2B1); // enable OC2B output
                    TCCR2A |= 1;
                    TCCR2B = 1; // bit CS10 for clock on timer no prescaler
                    OCR2B = value;
                    
                    break; 
                case 5:
                    TCCR0A |=  (1 << COM0B1);  // enable OC0B output
                    TCCR0A |= 1;
                    TCCR0B = 1 ;   
                    OCR0B = value;
                    
                    break;
                case 6:
                    TCCR0A |=  (1 << COM0A1);  // enable OC0A output
                    TCCR0A |= 1;
                    TCCR0B = 1;
                    OCR0A = value;
                    
                    break;
                case 9:
                    TCCR1A |= (1 << COM1A1); // enable OC1A output
                    TCCR1A |= 1;
                    TCCR1B = 1;
                    OCR1A = value;
                    
                   
                    
                    
                    break;
                case 10:
                    
                    TCCR1A |= (1 << COM1B1); // enable OC1B output
                    TCCR1A |= 1;
                    TCCR1B = 1;
                    OCR1B = value;
                    
                    break;
                case 11:
                    
                    TCCR2A |= (1 << COM2A1);
                    TCCR2A |= 1;
                    TCCR2B = 1; // bit CS10 for clock on timer no prescaler
  
                    OCR2A = value;
                    
                    break;
                default:
                    break;

        }     
    } else {
        if(value > 128) writeDigitalPin(pin, 1);
        else writeDigitalPin(pin, 0);
    }    
    return 0;

}



#endif