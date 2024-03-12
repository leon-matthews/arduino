#pragma once


namespace MAX7219 {


/**
Example of IO interface needed for MAX7219 class.
*/
class IO {
    void send_command(uint8_t address, uint8_t data);
};


/**
Direct interface to MAX7219 and MAX7221 chips.

Try the `MAX7219::Digits` and `MAX7219::Matrix` subclasses instead of this
one in the common case where you'll be using a multi-digit 7-segment LED
display, or an 8x8 LED matrix.

These chips provide easy addressing and automatic refresh up to
8-digits of 7-segment display, or 64 individual LEDs.

Chip stores values up to 64 LEDs and refreshes them in banks of 8 at a rate
of at least 800Hz (faster if less than 8 digits enabled). The output drive
is automatially current limited, with PWM brightness control.

The two chips are almost identical. The MAX7221 slews its drive pins to reduce
EMI, has less range in brightness, and changes the behaviour of its CS/LOAD pin
to be fully SPI compliant.

BCD decode-mode is currently disabled during setup and is not supported
by this driver.
*/
template <typename IO>
class MAX7219 {
    private:
        IO& io;

    public:
        MAX7219<IO>(IO& io) : io{io} {}

        /**
        Set the value of all LEDs to off.
        */
        void blank() {
            set_digits(0x00);
        }

        /**
        Send a 'No-Op' command.

        Args:
            count:
                Number of times to repeat command.
                Defaults to 1.

        Used when chaining displays together.
        */
        void noop(uint8_t count=1) {
            uint8_t i = 0;
            do {
                io.send_command(0x00, 0x00);
                ++i;
            } while(i < count);
        }

        /**
        Set global display brightness.

        Args:
            brightness:
                Value between 0 and 15

        The PWM duty-cycles varies from 1/32 to 31/32 for the MAX7219,
        and 1/16 to 15/16 for the MAX7221.
        */
        void set_brightness(uint8_t brightness) {
            brightness = (brightness > 15) ? 15 : brightness;
            io.send_command(0x0a, brightness);
        }

        /**
        Set the bit pattern for the given digit.

        Args:
            digit:
                Zero-indexed digit number (0-7).
            pattern:
                Bit pattern to send.

        */
        void set_digit(uint8_t digit, uint8_t pattern) {
            io.send_command((digit + 1), pattern);
        }

        /**
        Set the bit pattern for all digits.
        */
        void set_digits(uint8_t pattern) {
            for(uint8_t i = 0; i < 8; ++i) {
                set_digit(i, pattern);
            }
        }

        /**
        Start up display with useful defaults.
        */
        void setup() {
            io.send_command(0x09, 0x00);
            io.send_command(0x0a, 0x03);
            io.send_command(0x0b, 0x07);
            io.send_command(0x0c, 0x01);
            io.send_command(0x0f, 0x00);
        }

        /**
        Shutdown LEDs, enter low-power state.

        Args:
            enable:
                Set to false to disable shutdown mode.

        Commands are still accepted while shutdown mode is active.
        */
        void shutdown_mode(bool enable=true) {
            io.send_command(0x0c, enable);
        }

        /**
        Enable test pattern.

        Args:
            enable:
                Set to false to disable test mode.

        All LEDs lit with full brightness. Returns to previous state when
        test is over.
        */
        void test_mode(bool enable=true) {
            io.send_command(0x0f, enable);
        }
};


/**
Interface with up to 8 digits of LED 7-segment display.

TODO: Brainstorm API.
*/
template <typename IO>
class Digits : public MAX7219<IO>  {};


/**
Interface with a 8x8 LED matrix.

TODO: Brainstorm API.
*/
template <typename IO>
class Matrix : public MAX7219<IO> {};


}
