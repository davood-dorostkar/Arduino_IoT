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

void getSMS()
{
  Serial.println("Activating SMS Read Mode");
  delay(1000);
  SIM800.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
}

void setup()
{
  delay(5000);
  Serial.begin(9600);
  buffer.reserve(50);
  SIM800.begin(9600);
  Serial.println("Initializing Successful !");
  delay(1000);
  getSMS();
}
void loop()
{
  if (SIM800.available() > 0)
  {
    Serial.println("Just recieved a SMS : ");
    Serial.write(SIM800.read());
  }
}