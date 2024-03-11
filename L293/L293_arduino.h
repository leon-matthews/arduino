#pragma once

#include <Arduino.h>

#include "L293.h"


namespace L293 {


/**
Arduino implementation of IO operations required for L293 class.
*/
class ArduinoIO {
    public:
        ArduinoIO(uint8_t input1_pin, uint8_t input2_pin, uint8_t enable_pin) :
        input1_pin{input1_pin}, input2_pin{input2_pin}, enable_pin{enable_pin} {
            pinMode(input1_pin, OUTPUT);
            pinMode(input2_pin, OUTPUT);
            pinMode(enable_pin, OUTPUT);
        };

    void set_input1(bool value) {
        digitalWrite(input1_pin, value);
    }

    void set_input2(bool value) {
        digitalWrite(input2_pin, value);
    }

    void set_enable(bool value) {
        digitalWrite(enable_pin, value);
    }

    void pwn_enable(uint8_t value) {
        analogWrite(enable_pin, value);
    }

    private:
        uint8_t input1_pin, input2_pin, enable_pin;
};


}
