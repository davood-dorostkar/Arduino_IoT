#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <SoftwareSerial.h>
SoftwareSerial SIM800(2, 3); //SIM800L Tx >> 2 & Rx >> 3

void serialReadWrite()
{
  delay(500);
  while (Serial.available())
    SIM800.write(Serial.read());
  while (SIM800.available())
    Serial.write(SIM800.read());
}

void setup()
{
  Serial.begin(9600);
  SIM800.begin(9600);
  Serial.println("Initializing...");
  delay(1000);
  SIM800.println("AT");
  serialReadWrite();
  SIM800.println("AT+CSQ");
  serialReadWrite();
  SIM800.println("AT+CCID");
  serialReadWrite();
  SIM800.println("AT+CREG?"); 
  serialReadWrite();
  SIM800.println("AT+COPS?");
  serialReadWrite();
}

void loop()
{
  serialReadWrite();
}
