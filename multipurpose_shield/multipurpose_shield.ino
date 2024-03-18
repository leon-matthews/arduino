
#include <stdint.h>

#include "beeper.h"
#include "leds.h"
#include "potentiometer.h"
#include "primes.h"
#include "seven_segments.h"

using seven_segments::FourDigits;


// defining three key input
const byte key1 = A1;
const byte key2 = A2;
const byte key3 = A3;


// Program states
void do_counting();
void show_potentiometer();
void (*run)();


// Four digit LED display
FourDigits display = FourDigits(4, 7, 8);


void setup () {
    beeper::init();
    beeper::beep();
    
    leds::init();

    run = do_counting;

    pinMode(key1, INPUT);
    pinMode(key2, INPUT);
    pinMode(key3, INPUT);
}


void loop() {
    run();
    display.show();
}


/**
Use buttons S1 & S2 to count up and down by primes.
*/
void do_counting() {
    static int16_t prime = 2;
    static int16_t temp = 0;
    static int16_t max_value = display.get_max_value();

    if (digitalRead(key1) == LOW ) {
        // Show previous prime
        prime = previous_prime(prime);
    }
    else if (digitalRead(key2) == LOW) {
        // Show next prime
        temp = next_prime(prime);
        if (temp < max_value) {
            prime = temp;
        }
    }
    else if (digitalRead(key3) == LOW) {
        // Switch to analog reading
        run = show_potentiometer;
    }

    // Update values
    display.set_value(prime);
    leds::show_lsb(prime);
}


/**
Show the analog value of the potentiometer.
*/
void show_potentiometer() {
    uint16_t value = potentiometer::update();
    display.set_value(value);
    leds::show_lsb(value);

    // Switch to counting mode??
    if ((digitalRead(key1) == LOW ) || (digitalRead(key2) == LOW)) {
        run = do_counting;
    }
}
