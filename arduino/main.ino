// This is code I wrote in 2022...

// Первым делом нам нужно загрузить код для модуля ESP8266, чтобы связать её с нашей базой данных:
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Replace with your wifi settings
#define WIFI_SSID "Teachers_WIFI"
#define WIFI_PASSWORD "Nis12345"

// Replace this too
#define FIREBASE_HOST "FIREBASE_DATABASE_URL"
#define FIREBASE_AUTH "FIREBASE_API_KEY"
#define FIREBASE_CONTROL_REF "/device/control"

FirebaseData firebaseData;

void setup(){
  Serial.begin(9600); 
  delay(1000);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.println(".");
  }

  Serial.println();
  Serial.println("Connected to Wi-Fi");

  // Connect to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
  Firebase.reconnectWiFi(true);
}

void loop() {
  // Create a JSON object to hold the data
  String jsonData = "{";
  jsonData += "\"temperature\": ";
  jsonData += "55";
  jsonData += ", \"humidity\": ";
  jsonData += "a lot";
  jsonData += "}";

  // Upload the data to Firebase
  if (Firebase.pushJSON(firebaseData, FIREBASE_CONTROL_REF, jsonData)) {
    Serial.println("Data uploaded successfully");
  } else {
    Serial.print("Failed to upload data, reason: ");
    Serial.println(firebaseData.errorReason());
  }
  
  if (Firebase.failed()) {  
      return;
  }
  

  delay(5000);
}   


// // ●	Далее мы загружаем код в саму Arduino для работы ультразвукового датчика:
// int trigger_pin = 2;
// int echo_pin = 3;

// int time;
// int distance; 
// String value;

// void setup()
// {
//   pinMode (trigger_pin, OUTPUT); 
//   pinMode (echo_pin, INPUT);
//   Serial.begin(9600); 
//   delay(2000);  
// }

 
// void loop()
// {
//   value = get_distance_Value();
//   delay(1000);
//   Serial.flush();
//   delay(1000);
//   Serial.print(value);
//   delay(2000);
// }

// String get_distance_Value()
// {
//   digitalWrite(trigger_pin, 1);
//   delayMicroseconds(10);
//   digitalWrite(trigger_pin, 0);
//   time = pulseIn(echo_pin, 1);

//   distance = (time * 34) / 2;
//   return String(distance);  
// }

