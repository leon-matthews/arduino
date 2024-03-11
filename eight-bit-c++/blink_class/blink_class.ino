
class  LedArduinoIO {
    public:
        LedArduinoIO(int led_pin) : led_pin{led_pin} {
            pinMode(led_pin, OUTPUT);
        }
        void off() {
            digitalWrite(led_pin, LOW);
        }
        void on() {
            digitalWrite(led_pin, HIGH);
        }

    private:
        int led_pin;
};


LedArduinoIO led = LedArduinoIO(LED_BUILTIN);


void setup() {}


void loop() {
  led.on();
  delay(100);
  led.off();
  delay(100);
}
