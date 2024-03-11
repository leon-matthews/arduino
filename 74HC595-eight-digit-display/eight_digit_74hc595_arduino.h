
#include <Arduino.h>
#include <SPI.h>

#include "eight_digit_74hc595.h"


namespace eight_digit_74hc595 {


/**
Send data out to display using Arduino's shiftOut() function.

Slow, but available on every pin.
*/
class ArduinoShiftOut {
private:
    uint8_t clock, data, latch;

public:
    ArduinoShiftOut(uint8_t clock, uint8_t data, uint8_t latch) :
    clock{clock}, data{data}, latch{latch} {
        pinMode(clock, OUTPUT);
        pinMode(data, OUTPUT);
        pinMode(latch, OUTPUT);
    }

    void send_bytes(uint8_t first, uint8_t second) {
        digitalWrite(latch, LOW);
        shiftOut(data, clock, LSBFIRST, first);
        shiftOut(data, clock, LSBFIRST, second);
        digitalWrite(latch, HIGH);
    }
};


/**
Send data using Arduino's SPI hardware.

Faster, but restricted to one set of pins.

On the Arduino UNO the SPI pins are below. You need to define your own
CS (chip select) pin.

    MOSI    11
    MISO    12
    SCK     13
    SS      10
    CS       -

For writing to a shift register connect its data-in to MOSI (pin 11), its
clock to SCK (pin 13), and finally connect the latch to your chosen CS pin.
*/
class ArduinoSPI {
private:
    uint8_t chip_select;

public:
    ArduinoSPI(uint8_t chip_select) : chip_select{chip_select} {
        pinMode(chip_select, OUTPUT);
        SPI.begin();
        SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV2, LSBFIRST, SPI_MODE0));
    }

    ~ArduinoSPI() {
        SPI.endTransaction();
        SPI.end();
    }

    void send_bytes(uint8_t first, uint8_t second) {
        digitalWrite(chip_select, LOW);
        SPI.transfer(first);
        SPI.transfer(second);
        digitalWrite(chip_select, HIGH);
    }
};


}
