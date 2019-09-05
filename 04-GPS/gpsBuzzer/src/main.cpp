#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

int buzzer = 5;
int RXPin = 2;
int TXPin = 3;
int GPSBaud = 9600;
SoftwareSerial gpsSerial(RXPin, TXPin);
TinyGPSPlus gps;

void setup()
{
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);
}

void loop()
{
  while (gpsSerial.available() > 0)
  {
    double latitude = gps.location.lat();
    double longitude = gps.location.lng();
    if ((longitude < 35.804159 && longitude > 35.572190) || (latitude < 51.640727 && latitude > 51.073654))
    {
      tone(buzzer, 500);
    };
  }
}
