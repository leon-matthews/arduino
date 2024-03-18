#pragma once

#include <stdint.h>


using byte = uint8_t;


namespace seven_segments {


// Bit patterns for active-low
// 7-segment digits, in numeric order.
const byte segment_bits[10] = {
    0xC0,   // 0
    0xF9,   // 1
    0xA4,   // 2
    0xB0,   // 3
    0x99,   // 4
    0x92,   // 5
    0x82,   // 6
    0xF8,   // 7
    0x80,   // 8
    0x90,   // 9
};


/**
Four digit display.

Build from four 7-segment LED displays and two 74HC595
output latches. The first contains the digit-data, with each
segment bit active-low. The second multiplexes between the
four digits, active-high, bits 0 through 3.
*/
class FourDigits
{
  private:
    // Constants
    const static byte num_digits = 4;
    const static int16_t max_value = 9999;
    const static int16_t min_value = 0;

    // Arduino pins
    const byte latch_pin;
    const byte clock_pin;
    const byte data_pin;

    // State
    int16_t _value = 0;

    // Each digit's bit-pattern
    byte digits[num_digits];

    // Methods
    void update_bit_patterns();

  public:
    FourDigits(byte latch_pin, byte clock_pin, byte data_pin);
    void blank();
    int16_t get_max_value();
    int16_t get_value();
    void set_value(int16_t value);
    void show();
};


}   // namespace seven_segments
