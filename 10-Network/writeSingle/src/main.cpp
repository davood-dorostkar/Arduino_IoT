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
const char *netPassword = "Ikad77646301";
bool wifiState = 0;
WiFiClient myClient;

// ThingSpeak
#define channelID 701131
const int field1 = 1;
const char *writeAPIkey = "LLL6T8BKZ4LUWWTJ";

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

void thingSpeakCheck(int sentData)
{
  if (sentData == 200)
  {
    Serial.println("Channel updated successful.");
  }
  else
  {
    Serial.println("Problem updating channel.");
  }
}

void setup()
{
  Serial.begin(115200);
  ThingSpeak.begin(myClient);
  WiFi.begin(netName, netPassword);
  delay(4000);
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
    long value = random(20, 40);
    int sentData = ThingSpeak.writeField(channelID, field1, value, writeAPIkey);
    thingSpeakCheck(sentData);
    delay(30000);
  }
  else
    Serial.println("Could not connect to network");
}