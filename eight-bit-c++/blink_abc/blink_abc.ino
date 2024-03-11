
class LedIO {
    public:
        virtual void off() = 0;
        virtual void on() = 0;
        virtual void sleep(int milliseconds) = 0;
};


class ToggleLED {
  public:
    ToggleLED(LedIO& io) : io{io} {}

    void toggle() {
      if(on) {
        io.off();
        io.sleep(200);
      } else {
        io.on();
        io.sleep(100);
      }
      on = !on;
    }

  private:
    bool on{true};
    LedIO& io;
};


class  LedArduinoIO : public LedIO {
    public:

        LedArduinoIO(int led_pin) : led_pin{led_pin} {
            pinMode(led_pin, OUTPUT);
        }

        void off() override {
            digitalWrite(led_pin, LOW);
        }

        void on() override {
            digitalWrite(led_pin, HIGH);
        }

        virtual void sleep(int milliseconds) override {
          delay(milliseconds);
        }

    private:
        int led_pin;
};


LedArduinoIO io = LedArduinoIO(LED_BUILTIN);
ToggleLED led = ToggleLED(io);


void setup() {}


void loop() {
  led.toggle();
}
