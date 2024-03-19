
#include <stdint.h>


using byte = uint8_t;


const byte a = 0;
const byte b = 1;
const byte c = 2;
const byte d = 3;
const byte e = 4;
const byte f = 5;
const byte g = 6;
const byte dp = 7;

const byte pins[] = {a, b, c, d, e, f, g, dp};


// Segments to display, in order to animate them.
const byte digit_0[] = {a, b, c, d, e, f};
const byte digit_1[] = {b, c};
const byte digit_2[] = {a, b, g, e, d};
const byte digit_3[] = {a, b, c, d, g};
const byte digit_4[] = {f, g, b, c};
const byte digit_5[] = {a, f, g, c, d};
const byte digit_6[] = {a, f, e, d, c, g};
const byte digit_7[] = {f, a, b, c};
const byte digit_8[] = {f, a, b, c, d, e, g};
const byte digit_9[] = {d, c, b, a, f, g};
const byte digit_A[] = {e, f, a, b, c, g};
const byte digit_B[] = {f, e, d, c, g};
const byte digit_C[] = {a, f, e, d};
const byte digit_D[] = {g, e, d, c, b};
const byte digit_E[] = {a, f, e, d, g};
const byte digit_F[] = {a, f, e, g};


const byte digits[] = {
  *digit_0,
  *digit_1,
  *digit_2,
  *digit_3,
  *digit_4,
  *digit_5,
  *digit_6,
  *digit_7,
  *digit_8,
  *digit_9,
  *digit_A,
  *digit_B,
  *digit_C,
  *digit_D,
  *digit_E,
  *digit_F,
};


void setup() {
  // Set all pins to output
  for(const byte &pin : pins) {
    pinMode(pin, OUTPUT);
  }
}


inline void clear_digit() {
  // Turn off digit
  for(const byte &pin : pins) {
    digitalWrite(pin, LOW);
  }
}


/**
Draw digit with animation.
*/
template <size_t N>
void write_digit(const byte (& digit)[N]) {
  for(const byte &pin : digit) {
    digitalWrite(pin, HIGH);
    delay(20);
  }
  delay(500);
  clear_digit();
  delay(500);
}


// the loop function runs over and over again forever
void loop() {
  write_digit(digit_0);
  write_digit(digit_1);
  write_digit(digit_2);
  write_digit(digit_3);
  write_digit(digit_4);
  write_digit(digit_5);
  write_digit(digit_6);
  write_digit(digit_7);
  write_digit(digit_8);
  write_digit(digit_9);
  write_digit(digit_A);
  write_digit(digit_B);
  write_digit(digit_C);
  write_digit(digit_D);
  write_digit(digit_E);
  write_digit(digit_F);
}
