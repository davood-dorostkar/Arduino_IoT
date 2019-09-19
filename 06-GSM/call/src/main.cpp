#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <SoftwareSerial.h>
SoftwareSerial SIM800(2, 3);
int timeout;
String buffer;
String number = "+98xxxxxxxxxx";

String readSIM()
{
  timeout = 0;
  while (!SIM800.available() && timeout < 12000)
  {
    delay(13);
    timeout++;
  }
  if (SIM800.available())
  {
    return SIM800.readString();
  }
}

void callMe()
{
  SIM800.print(F("ATD"));
  SIM800.print(number);
  SIM800.print(F(";\r\n"));
  buffer = readSIM();
  Serial.println(buffer);
}

void setup()
{
  delay(5000);
  Serial.begin(9600);
  buffer.reserve(50);
  SIM800.begin(9600);
  Serial.println("Initializing Successful !");
  delay(5000);
  callMe();
}
void loop()
{
}