#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <SoftwareSerial.h>
SoftwareSerial SIM800(2, 3); //SIM800L Tx >> 2 & Rx >> 3
String number = "+98xxxxxxxxxx";
int pirPin = 2;
int lastState = LOW;

void sendSMS()
{
  SIM800.println("AT+CMGF=1");
  delay(1000);
  SIM800.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  String SMS = "Something is moving.\nMaybe someone is here!\nI will call you now";
  SIM800.println(SMS);
  delay(100);
  SIM800.println((char)26);
  delay(1000);
}

void callMe()
{
  SIM800.print(F("ATD"));
  SIM800.print(number);
  SIM800.print(F(";\r\n"));
}

void setup()
{
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);
  delay(5000);
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
