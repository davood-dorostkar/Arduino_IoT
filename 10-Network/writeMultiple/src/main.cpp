#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <dht.h>

// Sensor
#define sensorPin D0
dht DHT;
float temp;
float humidity;

// WiFi
const char *netName = "SanatBazzar";
const char *netPassword = "Ikad77646301";
bool wifiState = 0;
WiFiClient myClient;

// ThingSpeak
#define channelID 701131
const int field1 = 1;
const int field2 = 2;
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

// void thingSpeakCheck(int sentTempData, int sentHumidData)
// {
//   if ((sentTempData == 200) && (sentHumidData == 200))
void thingSpeakCheck(int sentHumidData)
{
  if ((sentHumidData == 200))
  {
    Serial.println("Channel update successful.");
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
  DHT.read22(sensorPin);
  float temperature = DHT.temperature;
  float humidity = DHT.humidity;
  wifiStatusCheck();
  if (wifiState)
  {
    // int sentTempData = ThingSpeak.writeField(channelID, field1, temperature, writeAPIkey);
    int sentHumidData = ThingSpeak.writeField(channelID, field2, humidity, writeAPIkey);
    // thingSpeakCheck((int)sentTempData, (int)sentHumidData);
    thingSpeakCheck((int)sentHumidData);
    delay(30000);
  }
  else
    Serial.println("Could not connect to network");
}