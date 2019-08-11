#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#define photocellPin A5

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println(analogRead(photocellPin));
  delay(1000);
}