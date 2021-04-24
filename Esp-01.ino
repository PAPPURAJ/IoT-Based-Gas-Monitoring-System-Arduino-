#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "iotgas-d7f88-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "dSd1lRLSO6QIkzmXPL2iwpG9B28899I1lHrV5YNZ"
#define WIFI_SSID "EDU123456"
#define WIFI_PASSWORD "123456789"



FirebaseData firebaseData;
FirebaseJson json;


void setup() {
  
    Serial.begin(9600);



  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}






void writeDB(String field,String value){
 Firebase.setString(firebaseData, "/"+field,value );
  
}



void loop() {
  
      process("1");

}




String d;
void process(String no){
    if(Serial.available()){

    d=Serial.readString();

   if(d.substring(0,3)=="CO2")
      writeDB("Data/CO2-"+no,d.substring(4));



  else if(d.substring(0,2)=="CO")
      writeDB("Data/CO-"+no,d.substring(3));



  else if(d.substring(0,3)=="CH4")
      writeDB("Data/CH4-"+no,d.substring(4));

  else if(d.substring(0,3)=="TEM")
      writeDB("Data/Temp-"+no,d.substring(4));


  else if(d.substring(0,3)=="LAT")
      writeDB("Location/Lat-"+no,d.substring(4));


  else if(d.substring(0,3)=="LON")
      writeDB("Location/Lon-"+no,d.substring(4));
  

    
  else
    writeDB("Error "+no,d);
 
   delay(1700);

}
}
