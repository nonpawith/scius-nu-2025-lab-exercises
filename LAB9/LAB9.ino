/*
Lab 9: Buzzer Alert System

Goal: Provide auditory alerts for abnormal values.
Task: Sound buzzer if SpO2 < 92% or HR < 50 or > 120 bpm.
*/

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

PulseOximeter pox;
const int buzzerPin = 23;

void setup() {
  Serial.begin(115200);
  pox.begin();
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  pox.update();
  float hr = pox.getHeartRate();
  float spo2 = pox.getSpO2();

  if (spo2 < 92 || hr < 50 || hr > 120) {
    tone(buzzerPin, 1000);
  } else {
    noTone(buzzerPin);
  }

  delay(1000);
}
