/*
Lab 6: Alarm Simulation

Goal: Synchronize buzzer, LEDs, and OLED.
Task: LEDs blink, buzzer sounds, OLED shows 'ALERT' for 10s.
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int leds[] = {25, 26, 27, 14};
Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define LEDC_PIN     23
#define LEDC_FREQ    2000
#define LEDC_RES     8

void setup() {
  for (int i = 0; i < 4; i++) pinMode(leds[i], OUTPUT);
  ledcAttach(LEDC_PIN, LEDC_FREQ, LEDC_RES); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  for (int j = 0; j < 20; j++) {
    for (int i = 0; i < 4; i++) digitalWrite(leds[i], HIGH);
    ledcWrite(LEDC_PIN, 128);  // 50% duty cycle
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("!!! ALERT !!!");
    display.display();
    delay(250);
    for (int i = 0; i < 4; i++) digitalWrite(leds[i], LOW);
    ledcWrite(LEDC_PIN, 0);    // Off
    delay(250);
  }
}
