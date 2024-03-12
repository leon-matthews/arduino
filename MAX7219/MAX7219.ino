/**
Interface with MAX7219 LED driver.
*/

#include "MAX7219_arduino.h"

using IO = MAX7219::ArduinoShiftOut;

auto io = IO(10, 9, 8);
auto display = MAX7219::MAX7219<IO>(io);


void setup() {
    display.setup();
    display.set_brightness(0);
}


uint8_t count = 0;


void loop() {
    for(uint8_t digit = 0; digit < 8; ++digit) {
        display.set_digit(digit, count);
        ++count;
        delay(1000);
    }
    display.blank();
}
