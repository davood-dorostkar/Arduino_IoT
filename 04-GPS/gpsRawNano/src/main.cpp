#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <SoftwareSerial.h>
int RX = 8;
int TX = 9;
SoftwareSerial gpsPort(RX, TX);

void setup()
{
  Serial.begin(9600);
  gpsPort.begin(9600);
}

void loop()
{
  while (gpsPort.available() > 0)
    Serial.write(gpsPort.read());
}
