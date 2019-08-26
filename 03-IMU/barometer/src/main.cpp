#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <SFE_BMP180.h>
#include <Wire.h>
SFE_BMP180 pressure;

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing Barometer sensor");
  while (!pressure.begin())
    ;
}

void loop()
{
  char lag;
  double T, P, p0 = 1013.25, altitude;
  lag = pressure.startTemperature();
  delay(lag);
  pressure.getTemperature(T);
  Serial.print("Temperature: ");
  Serial.print(T);
  Serial.println(" C");

  lag = pressure.startPressure(3);
  delay(lag);
  pressure.getPressure(P, T);
  Serial.print("Pressure: ");
  Serial.print(P);
  Serial.println(" mbar ");

  altitude = pressure.altitude(P, p0);
  Serial.print("Altitude: ");
  Serial.print(altitude, 0);
  Serial.println(" meters");
  Serial.println();

  delay(2000);
}