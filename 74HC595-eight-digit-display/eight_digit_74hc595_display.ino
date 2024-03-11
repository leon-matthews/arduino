/**
8-digit, 7-segment display driven by two 74HC595 shift registers.
*/

#include <stdint.h>

#include "eight_digit_74hc595_arduino.h"


//~ using IO = eight_digit_74hc595::ArduinoShiftOut;
//~ auto io = IO(13, 11, 9);

using IO = eight_digit_74hc595::ArduinoSPI;
auto io = IO(9);

auto display = eight_digit_74hc595::Display<IO>(io);


void setup() {
    // Set digits
    for(uint8_t i=0; i < 8; ++i) {
        display.set_digit(i, 8-i);
    }

    display.set_bits(7, 0x4e);
    display.set_bits(6, 0x7e);
    display.set_bits(5, 0x15);
    display.set_bits(4, 0x47);
    display.set_bits(3, 0x7e);
    display.set_bits(2, 0x3e);
    display.set_bits(1, 0x15);
    display.set_bits(0, 0x3d);
}


void loop() {
    display.refresh();
}
