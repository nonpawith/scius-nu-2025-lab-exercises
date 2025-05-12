/* 
Lab 8: Display HR and SpO2 on OLED

Goal: Use I2C OLED to show real-time readings.
Task: Display heart rate and oxygen saturation on OLED.
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MAX30100_PulseOximeter.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);
PulseOximeter pox;

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  pox.begin();
}

void loop() {
  pox.update();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("HR: ");
  display.print(pox.getHeartRate());
  display.println(" bpm");
  display.print("SpO2: ");
  display.print(pox.getSpO2());
  display.println(" %");
  display.display();
  delay(1000);
}
