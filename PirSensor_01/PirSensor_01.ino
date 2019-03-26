 
int led = 16;      //D0
int sensor = 13;   //D7
int state = LOW;   //by default no motion
int val = 0;       //store the sensor value

void setup() {
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  Serial.begin(115200);      // initialize serial
}

void loop(){
  val = digitalRead(sensor);     // reading sensor value
  if (val == HIGH) {             // check if the sensor is HIGH
      digitalWrite(led, HIGH);   // turn LED ON
      delay(100);                // delay 100 milliseconds 
     
      if (state == LOW) {
          Serial.println("Motion detected!"); 
          state = HIGH;          // update variable state to HIGH
      }
  } 
  else {
      digitalWrite(led, LOW);    // turn LED OFF
      delay(200);                // delay 200 milliseconds 

      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;             // update variable state to LOW
    }
  }
}
