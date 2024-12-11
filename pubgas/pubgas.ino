#include <WiFi.h>
#include <PubSubClient.h>

// Konfigurasi WiFi
const char* ssid = "momo";
const char* password = "felix223";

// Konfigurasi MQTT
const char* mqtt_server = "broker.hivemq.com";
const char* topic = "sensor/mq09";

// Konfigurasi MQ-09
#define MQ_PIN 34      // Pin analog untuk sensor MQ-09 (ubah sesuai dengan pin yang digunakan)

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
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Membaca nilai dari MQ-09 (sensor gas)
  int mq_value = analogRead(MQ_PIN); // Nilai analog dari sensor MQ-09

  // Mengirim data ke MQTT
  String payload = String("MQ-09 Value: ") + mq_value;
  client.publish(topic, payload.c_str());
  Serial.println("Data dikirim: " + payload);

  delay(2000); // Delay untuk pengiriman berikutnya
}
