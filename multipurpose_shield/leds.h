#pragma once

#include <Arduino.h>


// Four LEDs in a line
namespace leds {


const byte num_leds = 4;
const byte pins[num_leds] = {13, 12, 11, 10};


void init() {
    for(byte i=0; i < num_leds; ++i) {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], HIGH);    // HIGH = Off
    }
}


void show_lsb(const uint16_t& number) {
    for(byte i=0; i < num_leds; ++i) {
        digitalWrite(pins[i], ! (number & (1 << i)));
    }
}


} // namespace four_leds
