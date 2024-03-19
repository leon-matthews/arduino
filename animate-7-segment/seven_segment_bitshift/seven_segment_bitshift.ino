
#include <stdint.h>


using byte = uint8_t;

const byte pin_a = 0;
const byte pin_b = 1;
const byte pin_c = 2;
const byte pin_d = 3;
const byte pin_e = 4;
const byte pin_f = 5;
const byte pin_g = 6;
const byte pin_dp = 7;

/**
Output pins for digits.

The decimal-point is handled separately.
*/
const byte pins[] = {pin_a, pin_b, pin_c, pin_d, pin_e, pin_f, pin_g};

// Single digit bit-pattern in order of: a, b, c, d, e, f, g
const byte digits[] = {
  0x7E,   // 0
  0x30,   // 1
  0x6D,   // 2
  0x79,   // 3
  0x33,   // 4
  0x5B,   // 5
  0x5F,   // 6
  0x70,   // 7
  0x7F,   // 8
  0x7B,   // 9
  0x77,   // A
  0x1F,   // B
  0x4E,   // C
  0x3D,   // D
  0x4F,   // E
  0x47,   // F
};


void clear() {
  // Turn off digit
  digitalWrite(pin_dp, LOW);
  for(const byte &pin : pins) {
    digitalWrite(pin, LOW);
  }
}


void write_segment(const byte& pin, const byte& state) {
  digitalWrite(pin, !digitalRead(pin));
  delay(70);
  digitalWrite(pin, state);
  delay(0);
}

/**
Write the given digit to the 7-digit pins.
Animate using ordering.
*/
void write_digit(const byte& digit) {
  /*
  for(int i=0; i<7; i++) {
    digitalWrite(pins[i], ((1<<i) & digit));
    delay(100);
  }
  */
  write_segment(pin_f, (1<<1) & digit);
  write_segment(pin_a, (1<<6) & digit);
  write_segment(pin_b, (1<<5) & digit);
  write_segment(pin_c, (1<<4) & digit);
  write_segment(pin_d, (1<<3) & digit);
  write_segment(pin_e, (1<<2) & digit);
  write_segment(pin_g, (1<<0) & digit);
}


void setup() {
  // Set all pins to output
  pinMode(pin_dp, OUTPUT);
  for(const byte &pin : pins) {
    pinMode(pin, OUTPUT);
  }
  clear();
}


// the loop function runs over and over again forever
void loop() {
  for(const byte &digit : digits) {
    write_digit(digit);
    delay(600);
  }
}
