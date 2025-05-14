// ESP32 OLED + MAX30100 + LED + Buzzer Control via Web Server with Real-Time Chart and Prettified UI

#include <WiFi.h>               // WiFi connection library
#include <WebServer.h>          // Web server to host control UI
#include <Wire.h>               // I2C communication library
#include <Adafruit_GFX.h>       // Graphics support for OLED
#include <Adafruit_SSD1306.h>   // OLED driver
#include <ArduinoJson.h>        // JSON parser for HTTP requests
#include "MAX30100_PulseOximeter.h" // Heart rate & SpO2 sensor library

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
#define BUZZER_PIN 23
int ledPins[] = {25, 26, 27, 14}; // Define LED control pins

const char* ssid = "Your_SSID";         // Wi-Fi SSID
const char* password = "Your_Password"; // Wi-Fi password

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // OLED object
PulseOximeter pox;               // Pulse oximeter object
WebServer server(80);            // HTTP server on port 80

float bpm = 0, spo2 = 0;
uint32_t lastMeasure = 0;

// Callback for heartbeat detection
void onBeatDetected() {
  Serial.println("Beat!");
}

// Serve the main HTML UI
void handleRoot() {
  server.send(200, "text/html", R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
    <title>ESP32 Health Monitor</title>
    <style>
      /* Basic styling for UI */
      body { font-family: Arial; margin: 20px; }
      h2 { color: #2E86C1; }
      input, label { margin: 5px; }
      canvas { max-width: 100%; height: auto; }
    </style>
    </head>
    <body>
    <h2>ESP32 Control Panel</h2>

    <!-- OLED Text Input -->
    <label>OLED Text:</label>
    <input id='oledText'><br>

    <!-- LED Controls -->
    <label>LEDs:</label><br>
    <input type='checkbox' id='led0'>25
    <input type='checkbox' id='led1'>26
    <input type='checkbox' id='led2'>27
    <input type='checkbox' id='led3'>14<br>

    <!-- Buzzer Control -->
    <label>Buzzer:</label><input type='checkbox' id='buzzer'><br>
    <button onclick='sendData()'>Send</button>

    <!-- Live readings section -->
    <h2>Real-Time Readings</h2>
    <div>Heart Rate: <span id='bpm'>--</span> bpm</div>
    <div>SpO2: <span id='spo2'>--</span> %</div>
    <canvas id='chart'></canvas>

    <!-- Chart.js library for plotting data -->
    <script src='https://cdn.jsdelivr.net/npm/chart.js'></script>
    <script>
      const bpmSpan = document.getElementById('bpm');
      const spo2Span = document.getElementById('spo2');
      let chartCtx = document.getElementById('chart').getContext('2d');

      // Initialize line chart for HR and SpO2
      let chart = new Chart(chartCtx, {
        type: 'line',
        data: {
          labels: [],
          datasets: [
            { label: 'BPM', borderColor: 'red', data: [], fill: false },
            { label: 'SpO2', borderColor: 'blue', data: [], fill: false }
          ]
        },
        options: {
          responsive: true,
          animation: false,
          scales: { y: { min: 0, max: 150 } }
        }
      });

      // Append new data to chart every second
      function updateChart(bpm, spo2) {
        let now = new Date().toLocaleTimeString();
        if (chart.data.labels.length > 20) {
          chart.data.labels.shift();
          chart.data.datasets[0].data.shift();
          chart.data.datasets[1].data.shift();
        }
        chart.data.labels.push(now);
        chart.data.datasets[0].data.push(bpm);
        chart.data.datasets[1].data.push(spo2);
        chart.update();
      }

      // Request current readings from ESP32 every second
      function fetchReadings() {
        fetch('/readings').then(res => res.json()).then(data => {
          bpmSpan.innerText = data.bpm.toFixed(1);
          spo2Span.innerText = data.spo2.toFixed(1);
          updateChart(data.bpm, data.spo2);
        });
      }
      setInterval(fetchReadings, 1000); // Poll every second

      // Send OLED/LED/Buzzer settings to ESP32 via POST
      function sendData() {
        fetch('/control', {
          method: 'POST',
          headers: {'Content-Type': 'application/json'},
          body: JSON.stringify({
            text: document.getElementById('oledText').value,
            led0: document.getElementById('led0').checked,
            led1: document.getElementById('led1').checked,
            led2: document.getElementById('led2').checked,
            led3: document.getElementById('led3').checked,
            buzzer: document.getElementById('buzzer').checked
          })
        });
      }
    </script>
    </body></html>
  )rawliteral");
}

// Handle control commands sent from web UI
void handleControl() {
  if (!server.hasArg("plain")) return server.send(400, "text/plain", "No body");
  StaticJsonDocument<256> doc;
  DeserializationError err = deserializeJson(doc, server.arg("plain"));
  if (err) return server.send(400, "text/plain", "Bad JSON");

  // OLED text display
  if (doc.containsKey("text")) {
    display.clearDisplay();
    display.setCursor(2, 2);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println(doc["text"].as<String>());
    display.display();
  }

  // LED toggling
  for (int i = 0; i < 4; i++) {
    String key = "led" + String(i);
    if (doc.containsKey(key)) {
      digitalWrite(ledPins[i], doc[key] ? HIGH : LOW);
    }
  }

  // Buzzer control
  if (doc.containsKey("buzzer")) {
    digitalWrite(BUZZER_PIN, doc["buzzer"] ? HIGH : LOW);
  }

  server.send(200, "text/plain", "OK");
}

// Provide current sensor readings
void handleReadings() {
  StaticJsonDocument<128> doc;
  doc["bpm"] = bpm;
  doc["spo2"] = spo2;
  String output;
  serializeJson(doc, output);
  server.send(200, "application/json", output);
}

// Setup peripherals and start server
void setup() {
  Serial.begin(115200);
  Serial.println("\nBooting…");

  // GPIOs
  for (int i = 0; i < 4; ++i) pinMode(ledPins[i], OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  /* ---------- Wi-Fi ---------- */
  WiFi.mode(WIFI_STA);                    // be sure we are a station
  WiFi.begin(ssid, password);
  unsigned long t0 = millis();
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED && millis() - t0 < 10000) {
    delay(500); Serial.print('.');
  }
  if (WiFi.status() != WL_CONNECTED) {    // timeout → fallback AP
    Serial.println("\nHome network not found, starting fallback AP");
    WiFi.softAP("ESP32_HealthMonitor");
    Serial.print("ESP32 AP IP: ");  Serial.println(WiFi.softAPIP());
  } else {
    Serial.print("\nESP32 IP: ");  Serial.println(WiFi.localIP());
  }

  /* ---------- I²C devices ---------- */
  Wire.begin(21, 22);         // SDA, SCL
  Wire.setClock(400000);      // 400 kHz, fast but safe for MAX30100

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("-- OLED not responding - check wiring");
  }

  if (!pox.begin()) {
    Serial.println("-- MAX30100 not responding - check wiring & power");
    // don’t freeze; carry on so at least the web UI comes up
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);

  /* ---------- Web server ---------- */
  server.on("/",           handleRoot);
  server.on("/control",   HTTP_POST, handleControl);
  server.on("/readings",  HTTP_GET,  handleReadings);
  server.begin();
  Serial.println("Web server started");
}

// Main loop updates sensor and handles web clients
void loop() {
  server.handleClient();
  pox.update();
  if (millis() - lastMeasure > 1000) {
    lastMeasure = millis();
    bpm = pox.getHeartRate();
    spo2 = pox.getSpO2();
  }
}