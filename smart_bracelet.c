#include <WiFi.h>
#include <HTTPClient.h>

#define BUTTON 18
#define BUZZER 25
#define RXD2 16
#define TXD2 17

const char* ssid = "AzharSait";
const char* password = "azhar121206";
const char* serverURL = "";
const int WatchID = 1001;

HardwareSerial scanner(2);

bool lastButtonState = HIGH;

// 🛒 Cart
#define MAX_ITEMS 20
String pids[MAX_ITEMS];
int qtys[MAX_ITEMS];
int itemCount = 0;

// 📦 Cache
#define CACHE_SIZE 30
struct CachedItem {
  String pid;
  int qty;
};
CachedItem cache[CACHE_SIZE];
int cacheCount = 0;

// 🔁 WiFi reconnect timer
unsigned long lastAttempt = 0;

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  scanner.begin(9600, SERIAL_8N1, RXD2, TXD2);

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  WiFi.begin(ssid, password);   // 🔥 non-blocking start
  Serial.println("WiFi starting...");
}

void loop() {

  // 🔁 NON-BLOCKING WiFi reconnect
  if (WiFi.status() != WL_CONNECTED) {
    if (millis() - lastAttempt > 5000) {
      Serial.println("Trying WiFi reconnect...");
      WiFi.begin(ssid, password);
      lastAttempt = millis();
    }
  }

  // 🔁 Sync cache if WiFi is back
  sendCachedData();

  bool currentState = digitalRead(BUTTON);

  if (lastButtonState == HIGH && currentState == LOW) {

    Serial.println("\nButton Pressed → Triggering scan...");
    triggerScan();
    readBarcode();

    // ✅ wait for release (important fix)
    while (digitalRead(BUTTON) == LOW) {
      delay(10);
    }

    delay(200);
    Serial.println("Ready for next scan...");
  }

  lastButtonState = currentState;
}

void triggerScan() {
  uint8_t cmd[] = {0x7E, 0x00, 0x08, 0x01, 0x00, 0x02, 0x01, 0xAB, 0xCD};
  scanner.write(cmd, sizeof(cmd));
  Serial.println("Trigger sent");
}

void readBarcode() {

  byte buffer[150];
  int index = 0;

  unsigned long startTime = millis();

  while (millis() - startTime < 3000) {
    while (scanner.available()) {
      if (index < 149) {
        buffer[index++] = scanner.read();
      }
    }
  }

  char temp[100];
  int j = 0;

  for (int i = 0; i < index; i++) {
    if (buffer[i] >= 32 && buffer[i] <= 126) {
      temp[j++] = (char)buffer[i];
    }
  }
  temp[j] = '\0';

  if (j == 0) {
    Serial.println("Scan failed");
    beepError();
    return;
  }

  String barcode = String(temp);

  if (barcode.startsWith("31")) {
    barcode = barcode.substring(2);
  }

  Serial.print("PID: ");
  Serial.println(barcode);

  processBarcode(barcode);
}

void processBarcode(String pid) {

  for (int i = 0; i < itemCount; i++) {
    if (pids[i] == pid) {
      qtys[i]++;
      Serial.println("Item exists → Qty updated");
      sendToBackend(pid, qtys[i]);
      return;
    }
  }

  if (itemCount < MAX_ITEMS) {
    pids[itemCount] = pid;
    qtys[itemCount] = 1;

    Serial.println("New item added");

    sendToBackend(pid, 1);

    itemCount++;
  } else {
    Serial.println("Cart full!");
    beepError();
  }
}

void sendToBackend(String pid, int qty) {

  if (pid.length() == 0) {
    Serial.println("Invalid PID");
    return;
  }

  // 📦 Cache if no WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi OFF → caching");

    if (cacheCount < CACHE_SIZE) {
      cache[cacheCount].pid = pid;
      cache[cacheCount].qty = qty;
      cacheCount++;
    } else {
      Serial.println("Cache full");
      beepError();
    }
    return;
  }

  HTTPClient http;
  http.begin(serverURL);
  http.addHeader("Content-Type", "application/json");

  String json = "{\"product_code\": \"" + String(pid) +
                "\", \"scanner_id\": \"" + String(WatchID) +
                "\", \"quantity\": " + qty + "}";

  Serial.println(json);

  int code = http.POST(json);

  Serial.print("HTTP Code: ");
  Serial.println(code);

  if (code > 0 && code < 300) {
    Serial.println(http.getString());
    beepSuccess();
  } else {
    Serial.println(http.getString());
    beepError();
  }

  http.end();
}

void sendCachedData() {

  if (WiFi.status() != WL_CONNECTED) return;
  if (cacheCount == 0) return;

  Serial.println("Syncing cache...");

  for (int i = 0; i < cacheCount; i++) {

    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    String json = "{\"product_code\": \"" + cache[i].pid +
                  "\", \"scanner_id\": \"" + String(WatchID) +
                  "\", \"quantity\": " + cache[i].qty + "}";

    Serial.println(json);

    int code = http.POST(json);

    Serial.print("HTTP Code: ");
    Serial.println(code);

    if (code > 0 && code < 300) {
      beepSuccess();
    } else {
      beepError();
    }

    http.end();
  }

  cacheCount = 0;
  Serial.println("Cache cleared");
}

// 🔔 Buzzer
void beepSuccess() {
  digitalWrite(BUZZER, HIGH);
  delay(150);
  digitalWrite(BUZZER, LOW);
}

void beepError() {
  digitalWrite(BUZZER, HIGH);
  delay(400);
  digitalWrite(BUZZER, LOW);
}