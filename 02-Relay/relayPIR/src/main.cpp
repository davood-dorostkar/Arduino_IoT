#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#define pirPin 3
#define relayPin 2
int lastState = HIGH;

void setup()
{
  pinMode(relayPin, OUTPUT);
  pinMode(pirPin, INPUT);
}

void loop()
{
  if (digitalRead(pirPin))
  {
    digitalWrite(relayPin, LOW);
    if (!lastState)
    {
      lastState = !lastState;
    }
  }
  else
  {
    digitalWrite(relayPin, HIGH);
    if (lastState)
    {
      lastState = !lastState;
    }
  }
}