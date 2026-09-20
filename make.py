import sys
import os

os.system("avr-gcc -mmcu=atmega328p -Os -Wall -DF_CPU=16000000UL -o blink.elf Main.c")
os.system("avr-objcopy -O ihex -R .eeprom blink.elf blink.hex")
os.system(" avrdude -patmega328p -P COM5 -carduino =D -U flash:w:blink.hex:i")