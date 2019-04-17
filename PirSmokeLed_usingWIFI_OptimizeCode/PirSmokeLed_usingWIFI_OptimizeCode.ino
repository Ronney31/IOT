#include <ESP8266WiFi.h>
#include <MQ2.h>  //simplified

const char* ssid = "Moto G (5S) Plus 4321";
const char* password = "iotSession71";

int LED = D0 ;
int FAN = D1 ;

// somke sensor
int Analog_Input = A0;
int lpg, co, smoke;
MQ2 mq2(Analog_Input);

WiFiServer server(80); // Creates a server that listens for incoming connections on the specified port, here in  this case port is 80.
WiFiClient client;

void setup(){
  Serial.begin(115200);
  
  pinMode(LED, OUTPUT);
  pinMode(FAN, OUTPUT);
  
  digitalWrite(LED, LOW);
  digitalWrite(FAN, LOW);

  //connection to wifi 
  Serial.println();
  Serial.println();
  Serial.print("Connection to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println('WiFi connected');

  //Starting server
  server.begin();
  Serial.println("Server Started");

  mq2.begin();
 
  //Printing the IP address
  Serial.println("Use this url to connected with NodeMCU ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); // Gets the WiFi shield's IP address and pring the IP on serial monitor
  Serial.println("/home");
}

void httpProtocolScript(){
    client.println("HTTP/1.1  200  OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<h1><center> WELCOME  TO IOT SMART WORLD </center></h1>");
    client.println("<h3><l> we are going to control LED & FAN and monitoring smoke sensor </l></h3>");
    client.println("please change the url to see the change ");
    client.println("<br>");
    client.println("</html>");
    client.stop();
    delay(1);
}
void httpProtocolScript(String Device, String control, String smokeData){
    String message = Device + " is " + control ;
    client.println("HTTP/1.1  200  OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<h1><center> WELCOME  TO IOT SMART WORLD </center></h1>");
    client.println(message);
    client.println("<br>");
    client.println(smokeData);
    client.println("</html>");
    client.stop();
    delay(1);
}

void loop(){
  lpg = mq2.readLPG();
  co = mq2.readCO();
  smoke = mq2.readSmoke();
  String smokeValues = "LPG:- " + String(lpg) + "   Co2:- " + String(co) + "   smoke:- " + String(smoke) ;

  Serial.println("**********************************");
  Serial.println(smokeValues);
  
  //check if a cliend has connected
  client = server.available();
  if (!client){
    return;
  }

  //wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  } 
  
  // Read the first line of the request 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  //Match the request and operate the light and fan
  if (request.indexOf("/home") != -1) {
    httpProtocolScript();
  }
  if (request.indexOf("/ledOn") != -1) {
    digitalWrite(LED, HIGH);
    Serial.println("LED is ON");
    httpProtocolScript("LED","ON",smokeValues);
  }
  if (request.indexOf("/ledOff") != -1) {
    digitalWrite(LED, LOW);
    Serial.println("LED is OFF");
    httpProtocolScript("LED","OFF",smokeValues);
  }
  if (request.indexOf("/fanOn") != -1) {
    digitalWrite(FAN, HIGH);
    Serial.println("FAN is ON");
    httpProtocolScript("FAN","ON",smokeValues);
  }
  if (request.indexOf("/fanOff") != -1) {
    digitalWrite(FAN, LOW);
    Serial.println("FAN is OFF");
    httpProtocolScript("FAN","OFF",smokeValues);
  }
  
}
