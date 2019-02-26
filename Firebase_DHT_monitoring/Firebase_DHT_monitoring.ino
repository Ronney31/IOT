#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include "DHT.h"

const char* ssid = "Wifi_ssid";
const char* password = "wifi_password";
#define FIREBASE_HOST "firbaseProject_url"

#define DHTPIN 14 //data pin for dht ( in NodeMcu D5 GPIO is 14 )
#define DHTTYPE DHT11 //DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  Serial.print("connecting");
  
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  
  dht.begin();
  Serial.println("");
  
  Serial.println("WiFi Connected Successfully!");

  Serial.println(WiFi.localIP()); // Gets the WiFi shield's IP address and pring the IP on serial monitor
  Serial.println("connecting to Firebase");
  Firebase.begin(FIREBASE_HOST);
  Serial.println("connected");
  
}

void loop() {
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.println("");

  Firebase.setFloat ("Humi",h);
  Firebase.setFloat ("Temp",t);
  Firebase.setFloat ("Heat",hic);
  delay (500);  

}
