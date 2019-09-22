#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <SoftwareSerial.h>
SoftwareSerial SIM800(2, 3);

void getSMS()
{
  Serial.println("Switching to SMS read mode");
  delay(1000);
  SIM800.println("AT+CNMI=2,2,0,0,0"); 
  delay(1000);
}

void setup()
{
  delay(7000); 
  Serial.begin(9600);
  SIM800.begin(9600);
  Serial.println("Initializing ...");
  delay(1000);
  getSMS();
}
void loop()
{

  if (SIM800.available() > 0)
    Serial.write(SIM800.read());
}
