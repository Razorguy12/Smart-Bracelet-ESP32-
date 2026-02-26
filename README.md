# 📿 Smart Bracelet – IoT Scan Device

A WiFi-enabled Smart Bracelet prototype built using an ESP32 that sends product scan data to a backend server when a button is pressed.

This project demonstrates a simple IoT wearable device capable of communicating with a backend system using HTTP POST requests.

The bracelet works as a wireless scan trigger, making it suitable for smart retail, attendance tracking, and inventory systems.

---

## 🚀 Features

- WiFi connectivity using ESP32
- Button-triggered scan event
- HTTP POST communication
- JSON data transmission
- Real-time server interaction
- Lightweight wearable prototype

---

## 🛠 Hardware Requirements

- ESP32 Development Board
- Push Button
- Jumper Wires
- Breadboard (optional)
- Battery Pack (optional for wearable use)

---

## ⚙️ Pin Configuration

| Component | ESP32 Pin |
|----------|-----------|
| Button   | GPIO 18   |

The button uses INPUT_PULLUP configuration:

- Not Pressed → HIGH  
- Pressed → LOW

---

## 📡 How It Works

1. ESP32 connects to WiFi.
2. The device continuously monitors the button state.
3. When the button is pressed:
   - A scan event is triggered
   - JSON data is generated
   - HTTP POST request is sent to the backend server
4. Server response is displayed on the Serial Monitor.

---

## 🧠 Data Format Sent

Example JSON payload:

{
  "id": "1",
  "product": "milk"
}

---

## 🌐 Server Endpoint

Example server URL:

http://192.168.137.58:8000/test/scan

You can modify this in the code:

const char* serverURL = "YOUR_SERVER_URL";

---

## 📶 WiFi Configuration

Enter your WiFi credentials in the code:

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

---

## 🔧 Required Libraries

The following libraries are included with the ESP32 package:

- WiFi.h
- HTTPClient.h

---

## 🔌 Installation

1. Install ESP32 Board Support

Open Arduino IDE

Tools → Board → Boards Manager

Search and install:

ESP32 by Espressif Systems

---

2. Upload Code

1. Connect ESP32 via USB
2. Open project in Arduino IDE
3. Select Board → ESP32 Dev Module
4. Upload the code

---

## 📟 Serial Monitor Output

Example output:

Connecting to WiFi...
HTTP Response code: 200
Server response:
Scan successful

Baud Rate: 115200

---

## 📁 Project Structure

smart-bracelet/
 ├── smart_bracelet.ino
 └── README.md

---

## 🔮 Future Improvements

- Battery-powered wearable design
- Mobile app integration
- Secure HTTPS communication
- RFID or NFC support
- Cloud backend integration
- OLED display
- Vibration feedback

---

## 🎯 Applications

- Smart retail systems
- Inventory tracking
- Smart attendance systems
- IoT wearable devices
- Access control

---

## 👨‍💻 Author

Mohammed Azhar Sait
