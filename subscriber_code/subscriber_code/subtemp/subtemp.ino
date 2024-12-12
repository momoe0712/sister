#include <WiFiS3.h>
#include <PubSubClient.h>

// Konfigurasi WiFi
const char* ssid = "momo";
const char* password = "felix223";

// Konfigurasi MQTT
const char* mqtt_server = "broker.hivemq.com";
const char* topic = "sensor/dht11";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Pesan diterima di topic [");
  Serial.print(topic);
  Serial.print("]: ");
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
  }
  Serial.println();
}

void setup_wifi() {
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
    if (client.connect("Arduino_R4_Client")) {
      Serial.println("Terhubung");
      client.subscribe(topic);
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
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}