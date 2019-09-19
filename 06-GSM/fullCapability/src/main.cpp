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
String number = "+989217803834";
int pirPin = 2;
int lastState = LOW;

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

void sendSMS()
{
  SIM800.println("AT+CMGF=1");
  delay(1000);
  SIM800.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  String SMS = "The door is left open\nMaybe someone is here!\nI will call you";
  SIM800.println(SMS);
  delay(100);
  SIM800.println((char)26);
  delay(1000);
  buffer = readSIM();
}

void callMe()
{
  SIM800.print(F("ATD"));
  SIM800.print(number);
  SIM800.print(F(";\r\n"));
  buffer = readSIM();
}

void setup()
{
  pinMode(pirPin, INPUT);
  delay(5000);
  buffer.reserve(50);
  SIM800.begin(9600);
  delay(1000);
}
void loop()
{
  if (digitalRead(pirPin))
  {
    if (!lastState)
    {
      sendSMS();
      delay(15000);
      callMe();
      lastState = !lastState;
    }
  }
  else
  {
    if (lastState)
      lastState = !lastState;
  }
}
