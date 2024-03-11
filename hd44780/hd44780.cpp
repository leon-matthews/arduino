
#include "hd44780.h"


namespace hd44780 {


/**
Clear display and send cursor home.

This command takes up to 1.6ms to run. Commands sent when display is busy
will be ignored.
*/
void HD44780::clear() {
    command(0x01);
    _delay_ms(3);
}


void HD44780::command(byte order) {
    hardware.command(order);
    _delay_us(53);
}


/**
Send command 'Function set' using current value of `flags`.
*/
void HD44780::command_function_set() {
    byte value = 0x20;
    if (flags & Flags::eight_bit_mode) {
        value |= 0x10;
    }
    if (flags & Flags::two_line_mode) {
        value |= 0x08;
    }
    if (flags & Flags::font_type) {
        value |= 0x04;
    }
    command(value);
}


/**
Send command 'Display on/off and cursor' using current value of `flags`.
*/
void HD44780::command_display_on_off_and_cursor() {
    byte value = 0x08;
    if (flags & Flags::blink_cursor) {
        value |= 0x01;
    }
    if (flags & Flags::show_cursor) {
        value |= 0x02;
    }
    if (flags & Flags::show_display) {
        value |= 0x04;
    }
    command(value);
}


/**
Send command 'Entry  mode set' using current value of `flags`.
*/
void HD44780::command_entry_mode_set() {
    byte value = 0x04;
    if (flags & Flags::display_shift) {
        value |= 0x01;
    }
    if (flags & Flags::cursor_shift) {
        value |= 0x02;
    }
    command(value);
}


/*
TODO

Allow creation of custom characters. 8 custom characters can be
created in emphemeral RAM after display is running. They appear
in ASCII codes 0 through 7, inclusive.

1. Enter CG RAM mode by sending command byte with start address of CGRAM (see below).
2. Send eight bytes data. Only the 5 LSB bits are used.
3. Return to normal DD RAM mode by sending command byte with address.
4. Print ASCII codes 0-7 to see new characters.

  +=======+==============+
  | ASCII |    Address   |
  +=======+======+=======+
  |    0  |  64  |  0x40 |
  |    1  |  72  |  0x48 |
  |    2  |  80  |  0x50 |
  |    3  |  88  |  0x58 |
  |    4  |  96  |  0x60 |
  |    5  | 104  |  0x68 |
  |    6  | 112  |  0x70 |
  |    7  | 120  |  0x78 |
  +=======+======+=======+

Experiment with changing CG RAM contents while custom characters are already on
the screen. Animation city!

*/
void HD44780::create_custom(byte ascii, const byte rows[8]) {
    ascii = (ascii > 7) ? 7 : ascii;
    byte address = 0x40 + (ascii * 8);
    command(address);
    for( byte i=0; i<8; ++i) {
        write(rows[i]);
    }
    cursor_move(address);
}


/**
Enable or disable cursor's blinking.
*/
void HD44780::cursor_blink(bool do_blink) {
    if( do_blink ) {
        flags |= Flags::blink_cursor;
    } else {
        flags &= ~Flags::blink_cursor;
    }
    command_display_on_off_and_cursor();
}


/**
Send cursor home.

This command takes up to 1.6ms to run. Commands sent when display is busy
will be ignored.
*/
void HD44780::cursor_home() {
    command(0x02);
    _delay_ms(1.6);
}


/**
Move cursor left one position.
*/
void HD44780::cursor_left() {
    command(0x10);
}


/**
Show or hide cursor.
*/
void HD44780::cursor_show(bool show_cursor) {
    if( show_cursor ) {
        flags |= Flags::show_cursor;
    } else {
        flags &= ~Flags::show_cursor;
    }
    command_display_on_off_and_cursor();
}


/**
Move cursor to the given address.

The addresses are the strangest part of working with the HD44780 chip. Note
how they are neither contigous, nor do they increment row by row.

    40 x 2 LCD
    0x00......................................0x27
    0x40......................................0x67

    20 x 4 LCD
    0x00..................0x13
    0x40..................0x53
    0x14..................0x27
    0x54..................0x67

    20 x 2 LCD
    0x00..................0x13
    0x40..................0x53

    16 x 2 LCD
    0x00..............0x0F
    0x40..............0x4F

*/
void HD44780::cursor_move(uint8_t address) {
    address = address > 0x67 ? 0x67 : address;
    command(0x80 | address);
}


/**
Move cursor right one position.
*/
void HD44780::cursor_right() {
    command(0x14);
}


/**
Move entire display left one position.
*/
void HD44780::display_left() {
    command(0x18);
}


/**
Move entire display right one position.
*/
void HD44780::display_right() {
    command(0x1E);
}


/**
Show or hide entire display.
*/
void HD44780::display_show(bool show_display) {
    if( show_display ) {
        flags |= Flags::show_display;
    } else {
        flags &= ~Flags::show_display;
    }
    command_display_on_off_and_cursor();
}


/**
Initialise display and MCU.

The display will ignore all commands for at least 10ms after power-up,
including these.
*/
void HD44780::init() {
    hardware.init();
    _delay_ms(100);
    reset();
}


/**
Clear the display and reset it to its default power-on state.

Credit to `Donald Weiman <http://web.alfredstate.edu/faculty/weimandn/>`_ for
documenting this process far more clearly than the datasheet does.
The Wikipedia article on the `HD44780 controller
<https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller>`_ also contains
some valuable information on the reset process.
*/
void HD44780::reset() {
    // Step 1: Power on, then delay > 100 ms
    // Taken care of in `init()` function

    // Steps 2 through 4:
    // Ensure consistent mode before sending 'real' function set command.
    command(0x30);
    _delay_ms(4.1);
    command(0x30);
    command(0x30);

    // Step 5:
    // We are now ready to send our 'real' function set instruction.
    flags |= Flags::eight_bit_mode;
    flags |= Flags::two_line_mode;
    flags &= ~Flags::font_type;
    command_function_set();

    // Step 6: Clear display flags
    command(0x08);

    // Step 7: Clear display
    clear();

    // Step 8: Entry mode set
    flags &= ~Flags::display_shift;
    flags |= Flags::cursor_shift;
    command_entry_mode_set();

    // Steps 9 and 10: Turn display on, set cursor options.
    flags |= Flags::show_display;
    flags &= ~Flags::show_cursor;
    flags &= ~Flags::blink_cursor;
    command_display_on_off_and_cursor();
}


void HD44780::write(byte character) {
    hardware.write(character);
    _delay_us(53);
}



} // namespace hd44780
