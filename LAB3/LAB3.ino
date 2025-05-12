/*
Lab 3: Buzzer Beep

Goal: Generate tone using PWM.
Task: Use PWM on GPIO 23 to play a beep.
*/

void setup() {
  ledcSetup(0, 2000, 8);
  ledcAttachPin(23, 0);
}

void loop() {
  ledcWrite(0, 127); // 50% duty cycle
  delay(500);
  ledcWrite(0, 0);   // off
  delay(500);
}
