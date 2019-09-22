#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <Sim800l.h>
Sim800l sim;
char *myNumber = "+98xxxxxxxxxx";
char *SMS = "Hello, I am Arduino Uno.\nNice to meet you!";

void setup()
{
  Serial.begin(9600);
  sim.begin();
  delay(8000);
  sim.sendSms(myNumber, SMS);
  delay(3000);
  sim.callNumber(myNumber);
}

void loop()
{
}