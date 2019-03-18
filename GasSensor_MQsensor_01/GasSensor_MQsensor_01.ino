#include <ESP8266WiFi.h>
const int gasSensorPin = A0;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  int gasAnalogValue = analogRead(gasSensorPin);
  Serial.print("The Gas Analog Values is :- ");
  Serial.println(gasAnalogValue);
  delay(1000);
}
