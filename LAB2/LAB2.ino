/*
Lab 2: Multi-LED Sequencer

Goal: Control multiple outputs.
Task: Blink LEDs in sequence: GPIO 25 → 26 → 27 → 14.
*/

int leds[] = {25, 26, 27, 14};

void setup() {
  for (int i = 0; i < 4; i++)
    pinMode(leds[i], OUTPUT);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH);
    delay(200);
    digitalWrite(leds[i], LOW);
  }
}
