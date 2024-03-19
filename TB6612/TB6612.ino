/**
Play around with TB6612 motor driver
*/

const uint8_t pwm_a{8}, ain1{9}, ain2{10}, pwm_b{7}, bin1{5}, bin2{6}, stby{11};


void setup() {
  pinMode(pwm_a, OUTPUT);
  pinMode(ain1, OUTPUT);
  pinMode(ain2, OUTPUT);
  pinMode(pwm_b, OUTPUT);
  pinMode(bin1, OUTPUT);
  pinMode(bin2, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(stby, HIGH);
  digitalWrite(pwm_a, HIGH);
  digitalWrite(pwm_b, HIGH);
}

void loop() {
  // Forwards
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(ain1, HIGH);
  digitalWrite(ain2, LOW);
  digitalWrite(bin1, HIGH);
  digitalWrite(bin2, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(3000);

  // Coast A, Short B
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, LOW);
  digitalWrite(bin1, HIGH);
  digitalWrite(bin2, HIGH);
  delay(1000);

  // Backwards
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, HIGH);
  digitalWrite(bin1, LOW);
  digitalWrite(bin2, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  delay(3000);

  // Short A, Coast B
  digitalWrite(ain1, HIGH);
  digitalWrite(ain2, HIGH);
  digitalWrite(bin1, LOW);
  digitalWrite(bin2, LOW);
  delay(1000);
}
