#pragma once

#include <stdint.h>

#include <util/delay.h>

#include "Arduino.h"

#include "common.h"


typedef uint8_t byte;


namespace hd44780 {


/**
The hardware interface between the MCU and the LCD.
*/
class Interface
{
    public:
        virtual void init() const = 0;
        virtual void command(byte) const = 0;
        virtual void write(byte) const= 0;
};


/**
An Arduino implementation of a full, 8-wire interface to the LCD.
*/
class ArduinoEightWire : public Interface
{
    private:
        // Pin definition
        byte rs;
        byte rw;
        byte enable;
        byte bit0;
        byte bit1;
        byte bit2;
        byte bit3;
        byte bit4;
        byte bit5;
        byte bit6;
        byte bit7;

    public:
        ArduinoEightWire(byte rs, byte rw, byte enable,
            byte bit0, byte bit1, byte bit2, byte bit3,
            byte bit4, byte bit5, byte bit6, byte bit7) :
                rs(rs), rw(rw), enable(enable),
                bit0(bit0), bit1(bit1), bit2(bit2), bit3(bit3),
                bit4(bit4), bit5(bit5), bit6(bit6), bit7(bit7) {}
        void init() const;
        void command(byte order) const;
        void write(byte character) const;
};


/**
Interface to an I2C I/O expander backback based on the PCF8574 chip.

Requiring only 2-pins on the MCU, and available for less than $1, it is a
no-brainer to use these on every stand-alone LCD display that I own.
*/
class I2C_Backpack_PCF8574 : public Interface
{

};


} // namespace hd44780
