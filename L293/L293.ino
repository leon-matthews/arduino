/**
Drive two motors using L293D module.
*/

#include "L293_arduino.h"

using namespace L293;


auto io1 = ArduinoIO(2, 3, 10);
auto io2 = ArduinoIO(4, 5, 11);

auto motor1 = Motor<ArduinoIO>(io1);
auto motor2 = Motor<ArduinoIO>(io2);


void setup() {}


void loop() {
    motor1.forward();
    motor2.backward();
}
