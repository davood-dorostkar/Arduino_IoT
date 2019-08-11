#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#define photocellPin A5
#define maxLight 870
#define minLight 0

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int photocellRead = analogRead(photocellPin);
  Serial.print("Light intensity is: ");
  Serial.print(map(photocellRead, minLight, maxLight, 0, 100) );
  Serial.println(" %");
  delay(2000);
}