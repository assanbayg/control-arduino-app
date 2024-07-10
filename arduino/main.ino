// This is code I wrote in 2022...

// Первым делом нам нужно загрузить код для модуля ESP8266, чтобы связать её с нашей базой данных:
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "FIREBASE_DATABASE_URL"
#define FIREBASE_AUTH "FIREBASE_API_KEY"
#define WIFI_SSID "Teachers_WIFI"
#define WIFI_PASSWORD "Nis12345"

String values, sensor_data;

void setup(){
  Serial.begin(9600); 
  delay(1000);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
}
void loop() {

 bool Sr =false;
 
  while(Serial.available()){
    sensor_data=Serial.readString(); 
    Sr=true;    
    }
  
delay(1000);

  if(Sr==true){  
    
  values=sensor_data;
  

  int fristCommaIndex = values.indexOf(',');
  int secondCommaIndex = values.indexOf(',', fristCommaIndex+1);
  int thirdCommaIndex = values.indexOf(',', secondCommaIndex + 1);
  
 
  String ultrasonic_value = values.substring(0, fristCommaIndex);

  Firebase.setString("ultrasonic_value",ultrasonic_value);
   delay(10);


  delay(10);
  
  
  Firebase.pushString("previous_ultrasonic_value",ultrasonic_value);
   
  
  
  delay(1000);
  
  if (Firebase.failed()) {  
      return;
  }
  
}   
}


// ●	Далее мы загружаем код в саму Arduino для работы ультразвукового датчика:
int trigger_pin = 2;
int echo_pin = 3;

int time;
int distance; 
String value;

void setup()
{
  pinMode (trigger_pin, OUTPUT); 
  pinMode (echo_pin, INPUT);
  Serial.begin(9600); 
  delay(2000);  
}

 
void loop()
{
  value = get_distance_Value();
  delay(1000);
  Serial.flush();
  delay(1000);
  Serial.print(value);
  delay(2000);
}

String get_distance_Value()
{
  digitalWrite(trigger_pin, 1);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, 0);
  time = pulseIn(echo_pin, 1);

  distance = (time * 34) / 2;
  return String(distance);  
}

