#pragma once

#include <Arduino.h>

#include "MAX7219.h"


namespace MAX7219 {


/**
Arduino I/O using the shiftOut() function.

Not the fastest, but available on any pin you like.
*/
class ArduinoShiftOut {

public:
    ArduinoShiftOut(uint8_t clock_pin, uint8_t cs_pin, uint8_t data_pin) :
    clock_pin{clock_pin}, cs_pin{cs_pin}, data_pin{data_pin} {
        pinMode(clock_pin, OUTPUT);
        pinMode(cs_pin, OUTPUT);
        pinMode(data_pin, OUTPUT);
    };

    void send_command(uint8_t address, uint8_t data) {
        digitalWrite(cs_pin, LOW);
        shiftOut(data_pin, clock_pin, MSBFIRST, address);
        shiftOut(data_pin, clock_pin, MSBFIRST, data);
        digitalWrite(cs_pin, HIGH);
    }

private:
    uint8_t clock_pin, cs_pin, data_pin;
};


/**
Arduino I/O using its SPI hardware.

Very fast, but restricted to devices SPI pins. For the Arduino UNO these
are pins 11, 12, and 13 for MOSI, MISO, and SCK respectively.
*/
class ArduinoSPI {
public:
    ArduinoSPI(uint8_t mosi, uint8_t miso, uint8_t sck) :
    mosi{mosi}, miso{miso}, sck{sck} {
    }
    void send_command(uint8_t address, uint8_t data);

private:
    uint8_t mosi, miso, sck;
};


}
