
#include "interfaces.h"


namespace hd44780 {


/**
Send command byte.
*/
void ArduinoEightWire::command(byte order) const {
    digitalWrite(enable, HIGH);
    digitalWrite(rs, LOW);
    digitalWrite(bit0, bit_get(order, 0));
    digitalWrite(bit1, bit_get(order, 1));
    digitalWrite(bit2, bit_get(order, 2));
    digitalWrite(bit3, bit_get(order, 3));
    digitalWrite(bit4, bit_get(order, 4));
    digitalWrite(bit5, bit_get(order, 5));
    digitalWrite(bit6, bit_get(order, 6));
    digitalWrite(bit7, bit_get(order, 7));
    digitalWrite(enable, LOW);
}


/**
Initialise MCU hardware.
*/
void ArduinoEightWire::init() const {
    // Control pins
    pinMode(rs, OUTPUT);
    pinMode(rw, OUTPUT);
    pinMode(enable, OUTPUT);

    // Initial state
    digitalWrite(rs, LOW);
    digitalWrite(rw, LOW);
    digitalWrite(enable, HIGH);

    // Data pins (leave low)
    pinMode(bit0, OUTPUT);
    pinMode(bit1, OUTPUT);
    pinMode(bit2, OUTPUT);
    pinMode(bit3, OUTPUT);
    pinMode(bit4, OUTPUT);
    pinMode(bit5, OUTPUT);
    pinMode(bit6, OUTPUT);
    pinMode(bit7, OUTPUT);
}


/**
Write a single character
*/
void ArduinoEightWire::write(byte character) const {
    digitalWrite(enable, HIGH);
    digitalWrite(rs, HIGH);
    digitalWrite(bit0, bit_get(character, 0));
    digitalWrite(bit1, bit_get(character, 1));
    digitalWrite(bit2, bit_get(character, 2));
    digitalWrite(bit3, bit_get(character, 3));
    digitalWrite(bit4, bit_get(character, 4));
    digitalWrite(bit5, bit_get(character, 5));
    digitalWrite(bit6, bit_get(character, 6));
    digitalWrite(bit7, bit_get(character, 7));
    digitalWrite(enable, LOW);
}


} // namespace hd44780
