// Firebase Library
#include <FirebaseArduino.h>
// ESP library
#include <ESP8266WiFi.h>
// Software Serial library
#include <SoftwareSerial.h>
// Change the "HOST_NAME" with your host name from firebase console
#define FIREBASE_HOST "HOST_NAME"
// Change the "FIREBASE_AUTH_TOKEN" with your authentication token from firebase console
#define FIREBASE_AUTH "FIREBASE_AUTH_TOKEN"
// Replace SSID with your hotspot or wifi's name
#define WIFI_SSID "SSID"
// Replace PASSWORD with your wifi's password
#define WIFI_PASSWORD "PASSWORD"
//Pin 6 - RX , Pin 5 - TX
SoftwareSerial s(D6, D5);
void setup()
{
  s.begin(115200);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());
  // Notify Firebase to setup a client ot access the database
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void loop()
{
  // Path of your data bucket
  String mypath = "/Mecanum_Wheels_Robot";
  // Create a firebase object instance to get the data dump
  FirebaseObject object = Firebase.get(mypath);
  // Put the recieved data in data variable
  int data = object.getString("Drive").toInt();
  Serial.println(data);
  if (s.available() > 0)
  {
    // Read the data sending notifier
    char c = s.read();
    s.write(data);
  }
  delay(1);
}
