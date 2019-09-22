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

void sendSMS()
{
  SIM800.println("AT+CMGF=1");
  delay(1000);
  SIM800.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  String SMS = "Hello! I am Arduino.\nNice to meet you";
  SIM800.println(SMS);
  delay(100);
  SIM800.println((char)26);
  delay(1000);
}

void setup()
{
  delay(5000);
  Serial.begin(9600);
  SIM800.begin(9600);
  Serial.println("Initializing Successful !");
  delay(1000);
  sendSMS();
}
void loop()
{
}