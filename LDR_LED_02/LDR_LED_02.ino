int led = 16;

void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  int ldrVal = analogRead(A0);
  float voltage = ldrVal * (5.0/1023.0); //Converting the analog reading 
                                          //(which goes from 0-1023) to a voltage (0-5V)
  if ( voltage < 2 )
  {
     digitalWrite(led,HIGH);
     Serial.println("LED is ON");
  }
  else {
    digitalWrite(led,LOW);
  }
  Serial.println(voltage);
}
