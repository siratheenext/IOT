#define DHTPIN 27
#define DHTTYPE DHT22
#define LED_PIN 23
#define BUTTON_PIN 18

#include <DHT.h>
#include <Wire.h>
#include "RTClib.h"
#include <WiFi.h>
#include <PubSubClient.h>

DHT dht(DHTPIN, DHTTYPE);
RTC_DS3231 rtc;

// WiFi + MQTT
// const char* ssid = "misochoyu_2.4G";
// const char* password = "misochoyu";
// const char* mqtt_server = "192.168.1.112"; // IP เครื่อง Node-RED/MQTT Broker

const char* ssid = "Next";
const char* password = "0972854443";
const char* mqtt_server = "172.20.10.4"; //ใช่เน็ตมือถือ

WiFiClient espClient;
PubSubClient client(espClient);

bool overheatStarted = false;
bool buttonPressed = false;
unsigned long overheatStartMillis = 0;
unsigned long overheatDuration = 0;

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  dht.begin();
  rtc.begin();

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  DateTime now = rtc.now();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("อ่านค่า DHT22 ไม่ได้");
    delay(2000);
    return;
  }

  Serial.print("🕒 ");
  Serial.print(now.timestamp());
  Serial.print(" 🌡️ Temp: ");
  Serial.print(temp);
  Serial.print("°C 💧 Humidity: ");
  Serial.print(hum);
  Serial.println("%");

  // เริ่มจับเวลาเมื่อเกิน 39
  if (temp > 39.0 && !overheatStarted) { //ใส่เป็น 25.0 ได้เพื่อเอาไว้ test
    Serial.println("🔥 อุณหภูมิเกิน 39 → เริ่มจับเวลา");
    overheatStarted = true;
    buttonPressed = false;
    overheatStartMillis = millis();
    digitalWrite(LED_PIN, HIGH);
  }

  // กดปุ่ม = หยุดจับเวลา
  if (overheatStarted && digitalRead(BUTTON_PIN) == LOW && !buttonPressed) {
    buttonPressed = true;
    overheatDuration = millis() - overheatStartMillis;
    digitalWrite(LED_PIN, LOW);

    Serial.print("🛑 หยุดจับเวลา: ");
    Serial.print(overheatDuration / 1000);
    Serial.println(" วินาที");

    // รีเซ็ตให้พร้อมรอบถัดไป
    overheatStarted = false;
  }

  // ส่งข้อมูลแบบ JSON ไป Node-RED
  String payload = "{";
  payload += "\"temp\":" + String(temp, 1) + ",";
  payload += "\"hum\":" + String(hum, 1) + ",";
  payload += "\"duration\":" + String(overheatDuration / 1000);
  payload += "}";

  client.publish("healthmonitor/data", payload.c_str());

  delay(2000);
}
