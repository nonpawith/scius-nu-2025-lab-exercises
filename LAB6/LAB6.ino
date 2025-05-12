/*
Lab 6: Alarm Simulation

Goal: Synchronize buzzer, LEDs, and OLED.
Task: LEDs blink, buzzer sounds, OLED shows 'ALERT' for 10s.
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int leds[] = {14, 25, 26, 27};
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  for (int i = 0; i < 4; i++) pinMode(leds[i], OUTPUT);
  ledcSetup(0, 1000, 8);
  ledcAttachPin(23, 0);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  for (int j = 0; j < 20; j++) {
    for (int i = 0; i < 4; i++) digitalWrite(leds[i], HIGH);
    ledcWrite(0, 128);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("!!! ALERT !!!");
    display.display();
    delay(250);
    for (int i = 0; i < 4; i++) digitalWrite(leds[i], LOW);
    ledcWrite(0, 0);
    delay(250);
  }
}
