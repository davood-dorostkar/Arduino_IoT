#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#define IR 9

void setup()
{
  Serial.begin(9600);
  pinMode(IR, INPUT);
}

void loop()
{
  Serial.println(digitalRead(IR));
  delay(1000);
}