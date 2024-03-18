#pragma once

#include <Arduino.h>


// Beeper
namespace beeper {

const byte pin = 3;

void init() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);   // Low = Buzzer on 
}

void beep() {
    digitalWrite(pin, LOW);
    delay(100);
    digitalWrite(pin, HIGH);
}

} // namespace buzzer
