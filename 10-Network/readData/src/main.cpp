#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// WiFi
const char *netName = "SanatBazzar";
const char *netPassword = "xxxxxxxx";
bool wifiState = 0;
WiFiClient myClient;

// ThingSpeak
#define channelID 701131
const int readField = 1;
const char *readAPIkey = "xxxxxxxxxxxxxxxx";

void wifiStatusCheck()
{
  while ((WiFi.status() == WL_CONNECTED) && wifiState == 0)
  {
    Serial.println("Connected!");
    wifiState = 1;
  }
  while ((WiFi.status() == WL_DISCONNECTED) && wifiState == 1)
  {
    Serial.println("Disconnected!");
    wifiState = 0;
  }
}

void thingSpeakCheck()
{
  int readStatus = ThingSpeak.getLastReadStatus();
  if ((readStatus == 200))
  {
    Serial.println("Channel read successful.");
  }
  else
  {
    Serial.println("Problem reading channel.");
  }
}

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(netName, netPassword);
  delay(4000);
  ThingSpeak.begin(myClient);
  Serial.println("");
  Serial.println("Connecting... ");
  Serial.println("");
}

void loop()
{
  delay(2000);
  wifiStatusCheck();
  if (wifiState)
  {
    int readData = ThingSpeak.readIntField(channelID, readField, readAPIkey);
    thingSpeakCheck();
    Serial.println(readData);
    delay(5000);
  }
  else
    Serial.println("Could not connect to network");
}