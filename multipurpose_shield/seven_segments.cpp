
#include "Arduino.h"

#include "seven_segments.h"


namespace seven_segments {


/**
Constructor.

Args:
  latch_pin (byte): The Arduino pin that is connected to the ST_CP pin of the 74HC595.
  clock_pin (byte): The Arduino pin that is connected to the SH_CP pin of the 74HC595.
  data_pin (byte): The Arduino pin that is connected to the DS of the 74HC595
*/
FourDigits::FourDigits(byte latch_pin, byte clock_pin, byte data_pin) :
        latch_pin(latch_pin), clock_pin(clock_pin), data_pin(data_pin) {
    pinMode(latch_pin, OUTPUT);
    pinMode(clock_pin, OUTPUT);
    pinMode(data_pin, OUTPUT);
    _value = 0;
    update_bit_patterns();
    blank();
}


/**
Blank-out display, but do not change current value.
*/
void FourDigits::blank() {
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, MSBFIRST, 0x00);
  shiftOut(data_pin, clock_pin, MSBFIRST, 0x00);
  digitalWrite(latch_pin, HIGH);
}


/**
Show a single digit of the multiplexed display.

Run this method on each and every loop.
*/
void FourDigits::show() {
    // The digit to display *this* call.
    static byte digit = 0;

    digitalWrite(latch_pin, LOW);
    shiftOut(data_pin, clock_pin, MSBFIRST, digits[digit]);
    shiftOut(data_pin, clock_pin, MSBFIRST, (1<<digit));
    digitalWrite(latch_pin, HIGH);

    ++digit;
    if (digit > num_digits) {
        digit = 0;
    }
}


/**
Return the largest value that the display can show.
*/
int16_t FourDigits::get_max_value() {
  return max_value;
}

/**
Return the current value held in display.
*/
int16_t FourDigits::get_value() {
  return _value;
}


/**
Change the value to be shown by the display.

If a value too big to display is given, the value 9999
will be shown instead.

Args:
    given (uint16_t): New value to use in display.
*/
void FourDigits::set_value(int16_t given) {
    // Constrain value
    given = (given < min_value) ? min_value : given;
    given = (given > max_value) ? max_value : given;
    bool has_changed = (_value != given);
    _value = given;
    if (has_changed) {
        update_bit_patterns();
    }
}


void FourDigits::update_bit_patterns() {
    byte index;
    bool is_zero;
    uint16_t value = _value;

    // Thousands
    index = value / 1000;
    value -= index * 1000;    // Avoid using the modulo operator at all costs!
    is_zero = (index == 0);
    digits[0] = is_zero ? 0xFF : segment_bits[index];

    // Hundreds
    index = value / 100;
    value -= index * 100;
    is_zero = is_zero ? (index == 0) : false;
    digits[1] = is_zero ? 0xFF : segment_bits[index];

    // Tens
    index = value / 10;
    value -= index * 10;
    is_zero = is_zero ? (index == 0) : false;
    digits[2] = is_zero ? 0xFF : segment_bits[index];

    // Ones
    digits[3] = segment_bits[value % 10];
}


} // namespace seven_segments
