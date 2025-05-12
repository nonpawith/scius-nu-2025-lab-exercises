/*
Lab 10: Monitoring Station UI

Goal: Build a real-time HR and SpO2 monitoring dashboard.
Task: Combine OLED, buzzer, and LED into a mini patient monitor.
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MAX30100_PulseOximeter.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define BUZZER_PIN 23
#define LED_PIN 14

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
PulseOximeter pox;

void setup() {
  Serial.begin(115200);
  if (!pox.begin()) {
    Serial.println("MAX30100 init failed");
    while (1);
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  
  // Combine OLED and buzzer from Labs 8 and 9
  // Display 'NORMAL' or 'ALERT' message on OLED based on values
  // Trigger buzzer and LED alerts accordingly

  pox.update();

  float hr = pox.getHeartRate();
  float spo2 = pox.getSpO2();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("HR: ");
  display.print(hr);
  display.println(" bpm");

  display.print("SpO2: ");
  display.print(spo2);
  display.println(" %");

  if (spo2 < 92 || hr < 50 || hr > 120) {
    display.println("ALERT!");
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
  } else {
    display.println("NORMAL");
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  display.display();
  delay(1000);
}
