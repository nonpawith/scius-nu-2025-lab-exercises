/*
Lab 1: Blinking LED

Goal: Understand digital output and pin control.
Task: Blink LED on GPIO 2 with different intervals.
*/ 

void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(500);
}