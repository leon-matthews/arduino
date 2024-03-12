/**
Playing around with URL2003 and Unipolar stepper.
*/


const uint8_t in1{8}, in2{9}, in3{10}, in4{11};


void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


void wave_drive(uint8_t ms) {
  // A
  digitalWrite(in4, LOW);
  digitalWrite(in1, HIGH);
  delay(ms);

  // B
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(ms);

  // C
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  delay(ms);

  // D
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(ms); 
}


void full_step(uint8_t ms) {
  // A
  digitalWrite(in4, LOW);
  digitalWrite(in2, HIGH);
  delay(ms);

  // B
  digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  delay(ms);

  // C
  digitalWrite(in2, LOW);
  digitalWrite(in4, HIGH);
  delay(ms);

  // D
  digitalWrite(in3, LOW);
  digitalWrite(in1, HIGH);
  delay(ms);
}


void half_step(uint8_t ms) {
  // A
  digitalWrite(in4, LOW);
  digitalWrite(in2, HIGH);
  delay(ms);

  // B
  digitalWrite(in1, LOW);
  delay(ms);

  // C
  digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  delay(ms);

  // D
  digitalWrite(in2, LOW);
  delay(ms);

  // E
  digitalWrite(in2, LOW);
  digitalWrite(in4, HIGH);
  delay(ms);

  // F
  digitalWrite(in3, LOW);
  delay(ms);

  // G
  digitalWrite(in3, LOW);
  digitalWrite(in1, HIGH);
  delay(ms);

  // H
  digitalWrite(in4, LOW);
  delay(ms);
}


uint8_t ms = 100;
bool led = false;
void loop() {
  //full_step(ms);
  half_step(ms);
  //wave_drive(ms);
  digitalWrite(LED_BUILTIN, led);
  led = ! led;
}
