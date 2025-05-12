/*
Lab 4: Display Status on OLED

Goal: Use I2C OLED for display.
Task: Show current LED state and buzzer status on OLED.
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("LED 1 ON");
  display.println("Buzzer OFF");
  display.display();
  delay(1000);
}
