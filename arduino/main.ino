// ЭТО ПРОСТО ПРИМЕР
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Замените на свои настройки сети
#define WIFI_SSID "Teachers_WIFI"
#define WIFI_PASSWORD "Nis12345"

// И это тоже
#define FIREBASE_HOST "FIREBASE_DATABASE_URL"
#define FIREBASE_AUTH "FIREBASE_API_KEY"
#define FIREBASE_CONTROL_REF "/device/control"

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600); 
  delay(1000);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected to Wi-Fi");

  // Подключение к БД
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
  Firebase.reconnectWiFi(true);
}

void loop() {
  // Создаем JSON
  String jsonData = "{\"temperature\": 55, \"humidity\": \"a lot\"}";

  // Загружаем наш джэйсончик в БД
  if (Firebase.pushJSON(firebaseData, FIREBASE_CONTROL_REF, jsonData)) {
    Serial.println("Data uploaded successfully");
  } else {
    Serial.print("Failed to upload data, reason: ");
    Serial.println(firebaseData.errorReason());
  }

  delay(5000);
}
