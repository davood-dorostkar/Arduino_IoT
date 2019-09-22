#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <SoftwareSerial.h>
SoftwareSerial SIM800(2, 3);
String myNumber = "+98xxxxxxxxxx"; 

void callMe()
{
  SIM800.print(F("ATD"));
  SIM800.print(myNumber);
  SIM800.print(F(";\r\n"));
}

void setup()
{
  delay(7000);
  Serial.begin(9600);
  SIM800.begin(9600);
  Serial.println("Initializing ...");
  delay(1000);
  callMe();
}
void loop()
{
  if (SIM800.available() > 0)
    Serial.write(SIM800.read());
}
