# 📿 Smart Bracelet – IoT Communication Prototype

This project implements a **Smart Bracelet communication prototype** using an **ESP32** and a **FastAPI backend server**.

The system demonstrates **wireless communication between a wearable device and a backend server** using WiFi and HTTP requests.

The bracelet sends scan data to a server when a button is pressed, and the server receives and displays the data.

This project focuses **only on the communication architecture** between the bracelet and the backend.

The **wearable hardware design and advanced backend features have not been implemented yet.**

This project demonstrates the **core communication layer required for a smart wearable device.**

------------------------------------------------------------

## 🚀 Features

• ESP32 WiFi communication  
• Button-triggered scan event  
• HTTP POST communication  
• FastAPI backend server  
• JSON data transmission  
• Real-time server response  
• Communication layer prototype

------------------------------------------------------------

## ⚠️ Project Scope

This project currently implements **only the communication component** of a smart bracelet system.

Implemented:

• ESP32 WiFi communication  
• Button-triggered data transmission  
• HTTP POST requests  
• Basic FastAPI server  
• Data reception and display

Not yet implemented:

• Physical wearable bracelet design  
• Enclosure or wearable hardware  
• Battery-powered operation  
• Mobile application  
• Cloud backend  
• Database storage  
• User authentication
• Production backend system

This project serves as a **proof-of-concept for smart wearable communication.**

------------------------------------------------------------

## 🛠 Hardware Requirements

ESP32 Development Board  
Push Button  
Jumper Wires  
Breadboard (optional)

Note:

The current implementation uses a **basic ESP32 development setup** and is not yet integrated into a wearable form factor.

------------------------------------------------------------

## ⚙️ Pin Configuration

Button → GPIO 18

The button uses INPUT_PULLUP configuration:

Not Pressed → HIGH  
Pressed → LOW

------------------------------------------------------------

## 📁 Project Structure

smart-bracelet/

README.md  
smart_bracelet.ino  
server.py

------------------------------------------------------------

## 📡 System Overview

The Smart Bracelet connects to WiFi and waits for a button press.

When the button is pressed:

1. ESP32 connects to server
2. JSON data is created
3. HTTP POST request is sent
4. Server receives data
5. Server prints data
6. Response returned to ESP32

------------------------------------------------------------

## 🔧 ESP32 Firmware

The ESP32 program:

• Connects to WiFi  
• Monitors button input  
• Sends JSON data to server  
• Displays server response

Example JSON data sent:

{
"id":"1",
"product":"milk"
}

Server address in code:

const char* serverURL = "http://YOUR_IP_ADDRESS:8000/scan";

Replace YOUR_IP_ADDRESS with the IP address of the computer running the server.

Enter WiFi credentials:

const char* ssid = "YOUR_WIFI_NAME";

const char* password = "YOUR_WIFI_PASSWORD";

------------------------------------------------------------

## 🌐 FastAPI Backend Server

The backend server receives scan data from the ESP32.

Create a file named:

server.py

Add the following code:

from fastapi import FastAPI, Request

app = FastAPI()

@app.post("/scan")
async def scan_data(request: Request):

    body = await request.body()

    data = body.decode("utf-8")

    print("Received:", data)

    return {
        "status": "received",
        "data": data
    }

This server implementation is a **basic prototype backend** designed only to demonstrate communication.

------------------------------------------------------------

## 🧪 Running the Server

Install dependencies:

pip install fastapi uvicorn

Start the server:

uvicorn server:app --host 0.0.0.0 --port 8000

Make sure the ESP32 and server computer are connected to the same WiFi network.

------------------------------------------------------------

## 📡 How It Works

1 ESP32 connects to WiFi

2 Button press triggers scan event

3 JSON data is sent to server

4 Server receives request

5 Server prints data

6 Response returned to ESP32

------------------------------------------------------------

## 📟 Serial Monitor Output Example

Connecting to WiFi...

HTTP Response code: 200

Server response:

{"status":"received","data":"{\"id\":\"1\",\"product\":\"milk\"}"}

Baud Rate: 115200

------------------------------------------------------------

## 🖥 Server Terminal Output Example

Received: {"id":"1","product":"milk"}

------------------------------------------------------------

## 🔧 Required Libraries

ESP32 Libraries:

WiFi.h  
HTTPClient.h

Python Libraries:

fastapi  
uvicorn

------------------------------------------------------------

## 🎯 Applications

IoT communication prototypes

Smart wearable systems

Wireless data collection

Embedded IoT experiments

------------------------------------------------------------

## 🔮 Future Improvements

Wearable bracelet hardware design

Battery-powered operation

Cloud backend integration

Database storage

Mobile application

Secure HTTPS communication

RFID/NFC integration

User interface

------------------------------------------------------------

## 👨‍💻 Author

Mohammed Azhar Sait H
