#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// Konfigurasi WiFi
const char* ssid = "momo";
const char* password = "felix223";

// Konfigurasi MQTT
const char* mqtt_server = "broker.hivemq.com";
const char* topic = "sensor/dht11";

// Konfigurasi DHT
#define DHTPIN 4       // Pin data DHT11
#define DHTTYPE DHT11  // Tipe sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi terhubung");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Menghubungkan ke MQTT...");
    if (client.connect("ESP32_Client")) {
      Serial.println("Terhubung");
    } else {
      Serial.print("Gagal, rc=");
      Serial.print(client.state());
      Serial.println(" Coba lagi dalam 5 detik");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  dht.begin();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Membaca data dari DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Gagal membaca data dari DHT11");
    return;
  }

  // Mengirim data ke MQTT
  String payload = String("Temperature: ") + temperature + "C, Humidity: " + humidity + "%";
  client.publish(topic, payload.c_str());
  Serial.println("Data dikirim: " + payload);

  delay(2000); // Delay untuk pengiriman berikutnya
}