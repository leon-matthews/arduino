
#include "hd44780.h"
#include "interfaces.h"

using hd44780::ArduinoEightWire;
using hd44780::LCD_4x20;

// Animated icons
/*
const byte heart1[8] = {0, 10, 31, 31, 31, 14, 4, 0};
const byte heart2[8] = {17, 0, 10, 31, 31, 14, 4, 17};
const byte thermometer1[8] = {4, 10, 10, 10, 14, 31, 31, 14};
const byte thermometer2[8] = {4, 10, 14, 14, 14, 31, 31, 14};
*/

const byte bean0[8] = {  0,  0,  0,  0,  0,  1,  3,  7};
const byte bean1[8] = {  0,  3, 15, 31, 31, 31, 24,  7};
const byte bean2[8] = {  0, 24, 18, 22,  6, 14, 28, 28};
const byte bean3[8] = { 12, 13,  9, 11,  3,  3,  0,  0};
const byte bean4[8] = { 31, 31, 31, 31, 30, 28,  0,  0};
const byte bean5[8] = { 24, 16,  0,  0,  0,  0,  0,  0};



// LCD display
auto interface = ArduinoEightWire(10, 11, 12, 2, 3, 4, 5, 6, 7, 8, 9);
auto lcd = LCD_4x20(interface);


void print(const char* string) {
    for (int i=0; string[i] != 0; i++) {
        lcd.write(string[i]);
    }
}


void setup() {
    lcd.init();
    lcd.create_custom(0, bean0);
    lcd.create_custom(1, bean1);
    lcd.create_custom(2, bean2);
    lcd.create_custom(3, bean3);
    lcd.create_custom(4, bean4);
    lcd.create_custom(5, bean5);
}


void loop() {
    lcd.cursor_move(0x41);
    lcd.write(0);
    lcd.write(1);
    lcd.write(2);
    print(" Coffee Addict");
    lcd.cursor_move(0x15);
    lcd.write(3);
    lcd.write(4);
    lcd.write(5);
    print(" Parking Only!");


    while(true) {
        /*
        lcd.create_custom(0, heart1);
        lcd.create_custom(1, thermometer1);
        delay(500);

        lcd.create_custom(0, heart2);
        lcd.create_custom(1, thermometer2);
        delay(500);
        */
    }
}
