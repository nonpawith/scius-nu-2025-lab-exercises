/*
Lab 3: Buzzer Beep

Goal: Generate tone using PWM.
Task: Use PWM on GPIO 23 to play a beep.
*/

#define LEDC_PIN     23
#define LEDC_FREQ    2000
#define LEDC_RES     8

void setup() {
  // Attach and configure PWM in one line
  ledcAttach(LEDC_PIN, LEDC_FREQ, LEDC_RES); 
}

void loop() {
  ledcWrite(LEDC_PIN, 128);  // 50% duty cycle
  delay(1000);
  ledcWrite(LEDC_PIN, 0);    // Off
  delay(1000);
}
