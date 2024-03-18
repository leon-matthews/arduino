#pragma once

#include <Arduino.h>


// Potentiometer
namespace potentiometer {


static uint16_t value;


uint16_t update() {
    value = analogRead(A0);
    return value;
}


} // namespace potentiometer
