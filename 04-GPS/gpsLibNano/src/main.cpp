#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
int RX = 8;
int TX = 9;
TinyGPSPlus gps;
SoftwareSerial gpsPort(RX, TX);

void checkGPS()
{
  if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    Serial.println("Couldn't identify Location");
  }

  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("Couldn't identify Date");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10)
      Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Couldn't identify Time");
  }
  Serial.println();
  delay(1000);
}

void setup()
{
  Serial.begin(9600);
  gpsPort.begin(9600);
}

void loop()
{
  while (gpsPort.available() > 0)
    if (gps.encode(gpsPort.read()))
      checkGPS();
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS Device; Try Again Later.");
    while (true)
      ;
  }
}
