#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#define piezoelectricPin A0

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  float piezoV = analogRead(piezoelectricPin) * 5.0 / 1023.0;
  Serial.println(piezoV);
}
