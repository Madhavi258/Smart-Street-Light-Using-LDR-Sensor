#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ESP8266WiFi.h>

#define WIFI_SSID "Enter Your SSID Here"
#define WIFI_PASSWORD "Enter Password Here"
#define FIREBASE_HOST "smartlight-76187.firebaseio.com"
#define FIREBASE_AUTH "oQc5XawK0KCcg1TYkbeRWQBhfVIeG1FZ8yV5FAF4"
//SoftwareSerial NodeMCU(A0, D0);
 
int sdata = 0; // The variable resistor value will be stored in sdata.
 
void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(A0 ,INPUT);
  // connect to wifi.
  pinMode(D0,OUTPUT);
  digitalWrite(D0, HIGH);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 
   
}
 
void loop()
{

if (Firebase.failed()) // Check for errors 
{
Serial.println("Error");
delay(1000);
}
else
{
sdata = analogRead(A0);  
Firebase.setInt("LDRStatus",sdata);
if(Firebase.getInt("LDRStatus")<= 200)
{
  digitalWrite(D0, LOW);
  Serial.print("It's DARK, Turn on the LED : ");
  Serial.println(Firebase.getInt("LDRStatus"));
}

else {
  digitalWrite(D0, HIGH);
  Serial.print("It's BRIGHT, Turn off the LED : ");
  Serial.println(Firebase.getInt("LDRStatus"));

}

delay(1000);
}


delay(1000);            
}
