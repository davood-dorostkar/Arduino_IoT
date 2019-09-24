#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <Sim800l.h>
Sim800l SIM800;
char *myNumber = "+98xxxxxxxxxx";
char *SMS = "Hello, I am Arduino Uno.\nNice to meet you!";

void setup()
{
  SIM800.begin();
  delay(8000);
  SIM800.sendSms(myNumber, SMS);
  delay(3000);
  SIM800.callNumber(myNumber);
}

void loop()
{
}