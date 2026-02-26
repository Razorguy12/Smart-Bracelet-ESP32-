# 📿 Smart Bracelet – IoT Scan System

A WiFi-enabled Smart Bracelet prototype built using an ESP32 and a FastAPI backend server.

The bracelet sends scan data to a backend server whenever a button is pressed. This project demonstrates a simple IoT wearable device that communicates with a backend system using HTTP POST requests.

The backend server is implemented using FastAPI and runs locally on the same WiFi network as the ESP32.

---

## 🚀 Features

- ESP32 WiFi connectivity
- Button-triggered scan event
- FastAPI backend server
- HTTP POST communication
- JSON data transmission
- Real-time server response
- Lightweight wearable prototype

---

## 🛠 Hardware Requirements

- ESP32 Development Board
- Push Button
- Jumper Wires
- Breadboard (optional)
- Battery Pack (optional)

---

## ⚙️ Pin Configuration

Component : ESP32 Pin

Button : GPIO 18

The button uses INPUT_PULLUP configuration:

Not Pressed → HIGH  
Pressed → LOW

---

## 📁 Project Structure

smart-bracelet/

 ├── smart_bracelet.ino  
 ├── server.py  
 └── README.md

---

## 🔧 ESP32 Firmware

The ESP32 program:

- Connects to WiFi
- Monitors the button state
- Sends JSON data to the server
- Prints the server response to Serial Monitor

Example JSON data sent:

{
  "id": "1",
  "product": "milk"
}

Server address used in the code:

const char* serverURL = "http://YOUR_IP_ADDRESS:8000/test/scan";

Replace YOUR_IP_ADDRESS with the IP address of the computer running the FastAPI server.

Enter WiFi credentials in the code:

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

---

## 🌐 FastAPI Backend Server

The backend server is written using FastAPI and receives scan data from the Smart Bracelet.

Create a file named server.py and add the following code:

from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI()

class ScanData(BaseModel):
    id: str
    product: str


@app.get("/")
def home():
    return {
        "message": "Smart Bracelet Server Running"
    }


@app.post("/test/scan")
def scan(data: ScanData):

    print("Scan Received")
    print("ID:", data.id)
    print("Product:", data.product)

    return {
        "status": "success",
        "message": "Scan received",
        "id": data.id,
        "product": data.product
    }

---

## 🧪 Running the Server

Install dependencies:

pip install fastapi uvicorn

Start the server:

uvicorn server:app --host 0.0.0.0 --port 8000

Make sure the ESP32 and the server computer are connected to the same WiFi network.

---

## 📡 How It Works

1. ESP32 connects to WiFi
2. Device monitors button input
3. Button press triggers scan event
4. JSON data is sent to FastAPI server
5. Server processes request
6. Response is returned to ESP32

---

## 📟 Serial Monitor Output Example

Connecting to WiFi...
HTTP Response code: 200
Server response:
{"status":"success","message":"Scan received","id":"1","product":"milk"}

Baud Rate: 115200

---

## 🔮 Future Improvements

- Battery powered bracelet
- RFID or NFC integration
- Mobile app integration
- HTTPS support
- Cloud database
- OLED display
- Vibration feedback

---

## 🎯 Applications

- Smart retail systems
- Inventory tracking
- IoT wearable devices
- Access control

---

## 👨‍💻 Author

Mohammed Azhar Sait
