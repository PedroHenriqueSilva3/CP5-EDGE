#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22
#define LDRPIN 34
#define TRIGPIN 12
#define ECHOPIN 13

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "18.118.177.201";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("esp32vinheria")) break;
    delay(5000);
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  dht.begin();

  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  
}

float readDistanceCM() {
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  int duration = pulseIn(ECHOPIN, HIGH);
  return duration * 0.034 / 200;
}

void loop() { 
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float l = analogRead(LDRPIN);
  float d = readDistanceCM();

  Serial.println(h);
  Serial.println(t);
  Serial.println(l);
  Serial.println(d);

  if (!client.connected()) reconnect();
  client.loop();

  h = dht.readHumidity();
  t = dht.readTemperature();
  l = analogRead(LDRPIN);
  d = readDistanceCM();

  String payload = "{\"temperature\":" + String(t) + 
                   ",\"humidity\":" + String(h) + 
                   ",\"luminosity\":" + String(l) + 
                   ",\"distance\":" + String(d) + "}";

  client.publish("/iot/vinheria/data", payload.c_str());
  Serial.println(payload);
  delay(5000);
}
