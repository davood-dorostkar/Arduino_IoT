#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
Adafruit_LSM303_Mag_Unified compass = Adafruit_LSM303_Mag_Unified(11111);

void setup()
{
  Serial.begin(115200);
  while (!compass.begin())
    ;
  Serial.println("Compass initiated successfully!");
}

void loop()
{
  sensors_event_t compassRead;
  compass.getEvent(&compassRead);
  float heading = 0;
  float counter = 10.0;
  for (int i = 0; i < counter; i++)
  {
    heading += (atan2(compassRead.magnetic.y, compassRead.magnetic.x) * 180 / PI);
    if (heading < 0)
      heading += 360;
  }
  heading /= counter;
  heading = round(heading);
  Serial.print("Compass Heading: ");
  Serial.println(heading);
}