## CONTROLLING LIGHT AND FAN USING WIFI ( _INTERNET_ ), NODEMCU ESP8266
This is a simple project to control your device using local host. 
In this, I am controlling ( _ON/OFF_ ) of LED and FAN only, But the project can be 
extended futher.

**Defining constant variable for ssid and password**
```
const char* ssid = "HOTSPOT_NAME";
const char* password = "PASSWORD";
```

**Defining pins of nodemcu for led and fan**
```
int LED = D1 ;
int FAN = D2 ;
```
**Starting server at port 80 of my system**
```
WiFiServer server(80); 
```
**Setting the data rate in bits per second for serial data transmission**
```
Serial.begin(115200);  //opening serial port, set data rate to 115200
```
 **Configures the specified pin to behave either as an input or an output**
 ```
 pinMode(LED, OUTPUT);
 pinMode(FAN, OUTPUT);
 ```
 
 **Writint a HIGH or a LOW value to a digital pin**
 
 _its voltage will be set to the corresponding value: 5V (or 3.3V on 3.3V boards) for HIGH, 0V (ground) for LOW_
 ```
 digitalWrite(LED, LOW);
 digitalWrite(FAN, LOW);
 ```

**WiFi Initializing**

_Initializes the WiFi library's network settings and provides the current status_
```
WiFi.begin(ssid, password);
```

_checking whether it is connected to a network or not_
```
while(WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
}
```

**Starting Server**

_Tells the server to begin listening for incoming connections_
```
server.begin();
```

**Checking if the client is connected or not**
```
WiFiClient client = server.available();
if (!client){
  return;
}
```

**Read the first line of the request**
```
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();
```
_ Flush will waits until all outgoing characters in buffer have been sent_


**Match the request and operate the light and fan**

```
  if (request.indexOf("/ledOn") != -1) {
    digitalWrite(LED, HIGH);
    Serial.println("LED is ON");

    client.println("HTTP/1.1  200  OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("LED is ON");
    client.println("</html>");
    client.stop();
    delay(1);
  }
```

![Screenshot](https://github.com/Ronney31/IOT/blob/master/controlling_led_fan_using_wifi/pic%201.JPEG)
![Screenshot](https://github.com/Ronney31/IOT/blob/master/controlling_led_fan_using_wifi/pic%202.JPEG)
![Screenshot](https://github.com/Ronney31/IOT/blob/master/controlling_led_fan_using_wifi/pic%203.JPEG)
