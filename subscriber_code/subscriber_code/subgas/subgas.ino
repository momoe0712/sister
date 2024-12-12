#include <WiFi.h>
#include <PubSubClient.h>

// Konfigurasi WiFi
const char* ssid = "momo";
const char* password = "felix223";

// Konfigurasi MQTT
const char* mqtt_server = "broker.hivemq.com";
const char* topic = "sensor/mq09";

// Pin Buzzer
#define BUZZER_PIN 9 // Ganti sesuai dengan pin yang digunakan untuk buzzer

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
    if (client.connect("Arduino_Client")) {
      Serial.println("Terhubung");
      client.subscribe(topic);  // Subscribe ke topik
    } else {
      Serial.print("Gagal, rc=");
      Serial.print(client.state());
      Serial.println(" Coba lagi dalam 5 detik");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Mengonversi payload menjadi string
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println("Pesan diterima: " + message);

  // Mengambil nilai sensor dari pesan dan memeriksa apakah lebih dari 2000
  int mq_value = message.substring(message.indexOf(":") + 2).toInt();
  if (mq_value > 2000) {
    digitalWrite(BUZZER_PIN, HIGH);  // Nyalakan buzzer
    Serial.println("Buzzer ON!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);   // Matikan buzzer
    Serial.println("Buzzer OFF!");
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(BUZZER_PIN, OUTPUT);  // Set pin buzzer sebagai output
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
