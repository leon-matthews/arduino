#pragma once

#include <stdint.h>

#include <util/delay.h>

#include "common.h"
#include "interfaces.h"


typedef uint8_t byte;


namespace hd44780 {


namespace Flags
{
    constexpr byte blink_cursor   = (1 << 0);
    constexpr byte show_cursor    = (1 << 1);
    constexpr byte show_display   = (1 << 2);
    constexpr byte eight_bit_mode = (1 << 3);
    constexpr byte two_line_mode  = (1 << 4);
    constexpr byte font_type      = (1 << 5);
    constexpr byte display_shift  = (1 << 6);
    constexpr byte cursor_shift   = (1 << 7);
}

/*
TODO

Expose to user-level DISPLAY_SHIFT & CURSOR_SHIFT as we did with
the display_XXX() and cursor_XXX() methods. See the Adafruit library
for ideas for function names.
*/


/**
Hardware-agnostic driver for HD447480-based LCD displays.

Hardware-level communication in handled by an instance of
an `hd44780::Interface` sub-class, for example `ArduinoEightWire`.

Software operations are purposely true to the hardware. See the
classes `LCD_4x20` and `LCD_2x16` for a more convenient interface.
*/
class HD44780
{
    protected:
        byte flags;
        byte address;
        void command_display_on_off_and_cursor();
        void command_function_set();
        void command_entry_mode_set();
        void init_mcu();
        const Interface& hardware;

    public:
        HD44780(const Interface& interface) : hardware(interface) {};
        void init();
        void clear();
        void create_custom(byte ascii, const byte rows[8]);
        void cursor_blink(bool do_blink);
        void cursor_home();
        void cursor_left();
        void cursor_move(uint8_t address);
        void cursor_right();
        void display_left();
        void display_right();
        void display_show(bool show_display);
        void cursor_show(bool show_cursor);
        void command(byte order);
        void reset();
        void write(byte character);
};


/*
TODO

Take care of line-wrapping, full screen scrolling, etc...
*/
class LCD_4x20 : public HD44780
{
    public:
        LCD_4x20(const Interface& interface) : HD44780(interface) {};
};


} // namespace hd44780
