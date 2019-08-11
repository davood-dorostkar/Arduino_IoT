#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#define IRSender 9
#define IRReciever 11
bool state = 1;

void setup()
{
  Serial.begin(9600);
  pinMode(IRSender, OUTPUT);
  pinMode(IRReciever, INPUT);
}

void loop()
{
if(digitalRead(IRReciever))  Serial.println("Clear");
else Serial.println("Obstacle!");
delay(500);
}