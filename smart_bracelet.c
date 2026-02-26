#include <WiFi.h>
#include <HTTPClient.h>

#define button 18

const char* ssid = "";
const char* password = "";

const char* serverURL = "http://192.168.137.58:8000/test/scan";

int state = HIGH;

void setup() {

  Serial.begin(115200);

  pinMode(button, INPUT_PULLUP);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  /* Serial.println("\nConnected to WiFi");
  Serial.println(WiFi.localIP()); */
}

void loop() {

  state = digitalRead(button);

  if (state == LOW) {

    sendDataToBackend();

    delay(2000);   // debounce delay
  }
}

void sendDataToBackend() {

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin(serverURL);

    http.addHeader("Content-Type", "application/json");

    String jsonData = "{\"id\":\"1\",\"product\":\"milk\"}";

    int httpResponseCode = http.POST(jsonData);

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode > 0) {

      String response = http.getString();

      Serial.println("Server response:");
      Serial.println(response);
    }

    http.end();
  }

  else {

    Serial.println("WiFi not connected");
  }
}

