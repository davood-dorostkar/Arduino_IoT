#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#define sensorPin A0
#define RL 200
#define R0ratio 0.9914

float sensorRead()
{
  int i = 0;
  float VRL = 0;
  do
  {
    VRL = VRL + analogRead(sensorPin);
    i++;
  } while (i < 100);
  return (VRL / 100);
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  float VRL = sensorRead() * 5 / 1023;
  float Rs = RL * (5 - VRL) / VRL;
  float R0 = Rs / R0ratio;
  Serial.print("R0 = ");
  Serial.println(R0);
  delay(1000);
}