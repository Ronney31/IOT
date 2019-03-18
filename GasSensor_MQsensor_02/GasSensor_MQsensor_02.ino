#include <ESP8266WiFi.h>
#include <MQ2.h>  //simplified

int Analog_Input = A0;
int lpg, co, smoke;

MQ2 mq2(Analog_Input);

void setup(){
  Serial.begin(9600);
  mq2.begin();
}
void loop(){
  
  lpg = mq2.readLPG();
  co = mq2.readCO();
  smoke = mq2.readSmoke();
  
  Serial.print("LPG: ");
  Serial.print(lpg);
  Serial.print("\t CO: ");
  Serial.print(co);
  Serial.print("\t SMOKE: ");
  Serial.print(smoke);
  Serial.println("\n******************************************************");
  delay(1000);
}
