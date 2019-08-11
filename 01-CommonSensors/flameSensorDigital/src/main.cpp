#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#define flameSensorPin 2

void setup()
{
  Serial.begin(9600);
  pinMode(flameSensorPin,INPUT);
}

void loop()
{
  int flameState = digitalRead(flameSensorPin);
  switch (flameState)
  {
  case LOW:
  Serial.println("Safe");
    break;
  case HIGH:
  Serial.println("Danger!!!");
    break;
  }
  delay(1000);
}