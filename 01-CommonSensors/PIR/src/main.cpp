#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

int ledPin = 9;
int pirPin = 2;
int lastState = LOW;
void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(pirPin))
  {
    digitalWrite(ledPin, HIGH);
    if (!lastState)
    {
      Serial.println("Somebody is here!");
      lastState = !lastState;
    }
  }
  else
  {
    digitalWrite(ledPin, LOW);
    if (lastState)
    {
      Serial.println("Went away!");
      lastState = !lastState;
    }
  }
}