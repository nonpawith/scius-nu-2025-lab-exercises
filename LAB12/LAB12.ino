/*
Lab 12: Wi-Fi Transmission

Goal: Send real-time sensor data to a server or app.
Task: Transmit readings using HTTP or MQTT over Wi-Fi.
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include "MAX30100_PulseOximeter.h"

// Replace with your Wi-Fi / mobile hotspot
const char* ssid = "Your_SSID";
const char* password = "Your_Password";

// Replace with your server
const char* serverName = "https://your-server.com/submit";

PulseOximeter pox;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  if (!pox.begin()) {
    Serial.println("MAX30100 init failed");
    while (1);
  }
}

void loop() {
  pox.update();
  float hr = pox.getHeartRate();
  float spo2 = pox.getSpO2();

  if (WiFi.status() == WL_CONNECTED && hr > 0 && spo2 > 0) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"hr\":" + String(hr, 1) + ",\"spo2\":" + String(spo2, 1) + "}";
    int httpResponseCode = http.POST(payload);
    Serial.print("POST Response: ");
    Serial.println(httpResponseCode);
    http.end();
  } else {
    Serial.println("WiFi not connected or invalid reading");
  }

  delay(2000);
}
