/*
Lab 11: 1-Minute Data Logger

Goal: Store readings and analyze session stats.
Task: Log 60 HR and SpO2 readings, calculate and show min, max, avg.

*/

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

PulseOximeter pox;

float hr_data[60];
float spo2_data[60];

void setup() {
  Serial.begin(115200);
  if (!pox.begin()) {
    Serial.println("MAX30100 init failed");
    while (1);
  }
  Serial.println("Collecting data for 60 seconds...");
}

void loop() {

  // Use arrays to store 60 readings (one per second)
  // After 60 seconds, calculate min/max/avg and show on OLED or Serial

  for (int i = 0; i < 60; i++) {
    pox.update();
    hr_data[i] = pox.getHeartRate();
    spo2_data[i] = pox.getSpO2();
    Serial.print(".");
    delay(1000);
  }

  float hr_min = 999, hr_max = 0, hr_sum = 0;
  float spo2_min = 999, spo2_max = 0, spo2_sum = 0;

  for (int i = 0; i < 60; i++) {
    hr_sum += hr_data[i];
    if (hr_data[i] < hr_min) hr_min = hr_data[i];
    if (hr_data[i] > hr_max) hr_max = hr_data[i];

    spo2_sum += spo2_data[i];
    if (spo2_data[i] < spo2_min) spo2_min = spo2_data[i];
    if (spo2_data[i] > spo2_max) spo2_max = spo2_data[i];
  }

  Serial.println("\n\n=== SESSION SUMMARY ===");
  Serial.printf("HR Min: %.1f bpm\n", hr_min);
  Serial.printf("HR Max: %.1f bpm\n", hr_max);
  Serial.printf("HR Avg: %.1f bpm\n", hr_sum / 60.0);

  Serial.printf("SpO2 Min: %.1f %%\n", spo2_min);
  Serial.printf("SpO2 Max: %.1f %%\n", spo2_max);
  Serial.printf("SpO2 Avg: %.1f %%\n", spo2_sum / 60.0);

  while (1); // Halt after summary
}
