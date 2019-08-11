#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#define flameSensorPin A5

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int flameState = analogRead(flameSensorPin)/342;
  switch (flameState)
  {
  case 2:
  Serial.println("Safe");
    break;
  case 1:
  Serial.println("Warning!");
  break;
  case 0:
  Serial.println("Danger!!!");
  break;
  }
  delay(1000);
}