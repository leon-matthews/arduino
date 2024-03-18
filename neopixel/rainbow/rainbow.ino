
#include <Adafruit_NeoPixel.h>

const uint8_t pin = 10;
const uint16_t speed = 100;

Adafruit_NeoPixel pixels(1, pin, NEO_RGB + NEO_KHZ800);

  
void setup() {
  pixels.begin();
  pixels.clear(); 
}


void loop() {
  uint8_t max_brightness = 3;
  uint8_t red = max_brightness;
  uint8_t green = 0;
  uint8_t blue = 0;
  
  // Start red
  pixels.setPixelColor(0, red, green, blue);
  pixels.show();

  // Wait on red
  delay(speed * 10);

  // Ramp up green
  for( green=0; green < max_brightness; ++green) {
    pixels.setPixelColor(0, red, green, blue);
    pixels.show();
    delay(speed);
  }

  // Ramp down red
  for( red=max_brightness; red > 0; --red) {
    pixels.setPixelColor(0, red, green, blue);
    pixels.show();
    delay(speed);
  }

  // Wait on green
  delay(speed * 10);

  // Ramp up blue
  for( blue=0; blue < max_brightness; ++blue) {
    pixels.setPixelColor(0, red, green, blue);
    pixels.show();
    delay(speed);
  }

  // Ramp down green
  for( green=max_brightness; green > 0; --green) {
    pixels.setPixelColor(0, red, green, blue);
    pixels.show();
    delay(speed);
  }

  // Wait on blue
  delay(speed * 10);

  // Ramp up red
  for( red=0; red < max_brightness; ++red) {
    pixels.setPixelColor(0, red, green, blue);
    pixels.show();
    delay(speed);
  }

  // Ramp down blue
  for( blue=max_brightness; blue > 0; --blue) {
    pixels.setPixelColor(0, red, green, blue);
    pixels.show();
    delay(speed);
  }
}
