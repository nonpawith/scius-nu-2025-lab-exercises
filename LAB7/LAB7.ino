/*
Lab 7: MAX30100 Connection and Basic Readings

Goal: Understand how to initialize and read HR and SpO2 from the MAX30100.
Task: Connect the sensor via I2C and print values to Serial Monitor.
*/

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

PulseOximeter pox;

void onBeatDetected() {
  Serial.println("Beat!");
}

void setup() {
  Serial.begin(115200);
  if (!pox.begin()) {
    Serial.println("FAILED");
    while (1);
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  pox.update();
  Serial.print("HR: ");
  Serial.print(pox.getHeartRate());
  Serial.print(" bpm / SpO2: ");
  Serial.print(pox.getSpO2());
  Serial.println(" %");
  delay(1000);
}
