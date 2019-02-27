## IOT Monitoring DHT senson via Firebase ( NodeMcu )
This project helps to connect your NodeMcu with internet without depending upon any thirdparty app or website ( _thingspeak, blynk, etc_ )
just uploading and fetching data directly from Firebase.

### Library Required
- ArduinoJson version 5.13.4  _download from Library Manager_
- DHT (adafruit)	_download from Library Manager_
- Firebase 	https://github.com/FirebaseExtended/firebase-arduino

**Including Libraries and defining constant for ssid and password.**
```
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include "DHT.h"

const char* ssid = "Wifi_ssid";
const char* password = "wifi_password";
#define FIREBASE_HOST "firbaseProject_url"
```

**defining variable to store the host address to update data ( _firbase project url_ )**
```
#define FIREBASE_HOST "firbaseProject_url"
```

**WiFi Initializing**

_Initializes the WiFi library's network settings and provides the current status and checking whether it is connected to a network or not_
```
WiFi.begin(ssid, password);
Serial.print("connecting");

while(WiFi.status() != WL_CONNECTED){
	delay(500);
	Serial.print(".");
}
```


**Initiating DHT sensor**
```
dht.begin()
```

**Initiating Firebase connection**
```
Firebase.begin(FIREBASE_HOST);
```

**Reading data from dht sensor accordingly**
```
float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true); // in Fahrenheit
float hic = dht.computeHeatIndex(t, h, false);
```

**Sending data to Firebase with _Tag ("Humi",..)_**
```
Firebase.setFloat ("Humi",h);
Firebase.setFloat ("Temp",t);
Firebase.setFloat ("Heat",hic);
```

#### Create project on **Firbase**
	use the project url in arduino code and to create application.
	
#### create simple app on **MIT APP INVERTOR**
- you can use IOT_aby_01.aia to import all the labels, firebasedb and other fields.
- add the firebase project url and clear other fields	


![Screenshot](https://github.com/Ronney31/IOT/blob/master/Firebase_DHT_monitoring/App/Res/pic2.JPEG)

![Screenshot](https://github.com/Ronney31/IOT/blob/master/Firebase_DHT_monitoring/App/Res/pic1.JPEG)

![Screenshot](https://github.com/Ronney31/IOT/blob/master/Firebase_DHT_monitoring/App/Res/serialMonitoring.png)
