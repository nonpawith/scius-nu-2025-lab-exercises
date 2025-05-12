# ESP32 Lab Exercises

This repository contains 12 hands-on lab exercises using the ESP32 microcontroller for SCIUSNU students. The labs progress from basic hardware control to sensor integration and real-time data transmission.

## 🔧 Hardware Used
- ESP32-WROOM-32 DevKit v1
- OLED Display (I2C, SSD1306)
- LEDs (on GPIO 14, 25, 26, 27)
- Buzzer (on GPIO 23)
- MAX30100 or MAX30102 (Heart Rate & SpO₂ Sensor)

## 📚 Lab Structure

| Lab | Title                             | Description                                                             |
|-----|-----------------------------------|-------------------------------------------------------------------------|
| 1   | Blinking LED                      | Basic LED control using digital output and delay                        |
| 2   | Multi-LED Sequencer               | Create light patterns using multiple LEDs                               |
| 3   | Buzzer Beep                       | Generate sound using a buzzer and PWM                                   |
| 4   | Display Status on OLED            | Show text or sensor status on OLED via I2C                              |
| 5   | Simultaneous Multi-Tool Control   | Operate LEDs, buzzer, and OLED together                                 |
| 6   | Alarm Simulation                  | Trigger alert based on a condition (e.g., fake threshold detection)     |
| 7   | MAX30100 Connection               | Interface the MAX30100 sensor and read raw data                         |
| 8   | Display HR and SpO₂ on OLED       | Process and display real-time data from MAX30100                        |
| 9   | Buzzer Alert System               | Sound alarm when HR or SpO₂ go beyond normal range                      |
| 10  | Monitoring Station UI             | Build OLED-based mini monitoring interface                              |
| 11  | 1-Minute Data Logger              | Record sensor readings over time to serial or memory                    |
| 12  | Wi-Fi Transmission                | Send HR and SpO₂ data wirelessly to an online dashboard                 |

## 🚀 Getting Started

1. Clone this repository:
    ```bash
    git clone https://github.com/YOUR_USERNAME/esp32-lab-exercises.git
    ```
2. Open each lab folder (e.g., `Lab1`) in the Arduino IDE.
3. Upload to your ESP32 DevKit via USB.
4. Follow instructions and code comments inside each `.ino` file.

## 👩‍🔬 Educational Purpose

- These labs are intended for hands-on classroom demonstrations.
- No advanced electronics knowledge required.
- Encourages system integration, debugging, and creative application development.

## 📌 Notes

- Ensure all I2C devices (OLED and MAX30100) share the same SDA/SCL pins.
- Use resistors or shielding to improve sensor accuracy when necessary.
- Compatible with both MAX30100 and MAX30102 (with minor code changes).
