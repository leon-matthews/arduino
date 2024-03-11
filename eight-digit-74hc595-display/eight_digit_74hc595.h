#pragma once

#include <stdint.h>


namespace eight_digit_74hc595 {


// Active low, segments A, B, C, D, E, F, G, DP
constexpr uint8_t numeric_bits[10] = {
    0x03,   // 0
    0x9f,   // 1
    0x25,   // 2
    0x0d,   // 3
    0x99,   // 4
    0x49,   // 5
    0x41,   // 6
    0x1f,   // 7
    0x01,   // 8
    0x09,   // 9
};


/**
I/O needed for the Display class.
*/
class ExampleIO {
    public:
        void send_bytes(uint8_t first, uint8_t second);
};


template <typename IO>
class Display {
private:
    const static uint8_t num_digits = 8;

    // Bit patterns for each digit in display
    uint8_t current = 0;
    uint8_t digits[num_digits] = {};

    // Hardware abstraction layer
    IO& io;

public:
    Display<IO>(IO& io): io{io} {
        erase();
    }

    /**
    Turn off all LEDs, leaving display memory alone.

    See:
        EightDigit74HC595::fill()
    */
    void blank() {
        io.send_bytes(0xff, 0x00);
    }

    /**
    Turn off all LEDs and clear display memory.

    See:
        EightDigit74HC595::fill()
    */
    void erase() {
        for(uint8_t i=0; i < num_digits; ++i) {
            digits[i] = 0xff;
        }
        blank();
    }

    /**
    Turn on all LEDs, leaving display memory alone.

    Args:
        bits:
            The bit pattern to use. Defaults to 0x00, all LEDs on.

    See:
        EightDigit74HC595::blank()
    */
    void fill(uint8_t pattern = 0x00) {
        io.send_bytes(pattern, 0xff);
    }

    void set_bits(uint8_t digit, uint8_t pattern) {
      if (digit >= num_digits) {
            digit = 0;
        }
      digits[digit] = ~(pattern << 1);
    }

    /**
    Set a single digit to an integer.

    Args:
        digit:
            Zero-indexed, counted right to left. 0 to 7.
        value:
            Value to show, 0 to 9.
        show_decimal:
            Show decimal point. Defaults to false.

    */
    void set_digit(uint8_t digit, uint8_t value, bool show_decimal=false) {
        if (digit >= num_digits) {
            digit = 0;
        }
        if (value > 9) {
            value = 0;
        }
        digits[digit] = show_decimal ? numeric_bits[value] - 1 : numeric_bits[value];
    }

    /**
    Main display routine.

    Lights up a different digit of the display each time it's called.

    Must be called many hundreds or thousands of times per second to display
    all digits.
    */
    void refresh() {
        uint8_t mask = (1 << (current + 4) % num_digits);
        io.send_bytes(digits[current], mask);
        ++current;
        if(current >= num_digits) {
            current = 0;
        }
    }

    /**
    Rotate all digits left by one place.

        ABCDEFGH -> BCDEFGHA

    */
    void rotate_left() {
        shift_left(digits[num_digits-1]);
    }

    /**
    Rotate all digits right by one place.

        ABCDEFGH -> HABCDEFG

    */
    void rotate_right() {
        shift_right(digits[0]);
    }

    /**
    Shift all digits left by one place.

    Args:
        bits:
            Bit pattern to shift in at right-most position.
            Defaults to 0xff, all LEDs off.
    */
    void shift_left(uint8_t pattern=0xff) {
        for(uint8_t i=0; i < num_digits - 1; ++i) {
            digits[i] = digits[i+1];
        }
        digits[num_digits-1] = pattern;
    }

    /**
    Shift all digits right by one place.

    Args:
        bits:
            Bit pattern to shift into left-most position.
            Defaults to 0xff, all LEDs off.
    */
    void shift_right(uint8_t pattern=0xff) {
        for(int8_t i=num_digits - 1; i >= 0; --i)
        {
            digits[i+1] = digits[i];
        }
        digits[0] = pattern;
    }
};


}
