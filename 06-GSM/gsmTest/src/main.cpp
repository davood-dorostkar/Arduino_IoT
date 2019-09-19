#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial SIM800(2, 3); //SIM800L Tx >> 2 & Rx >> 3

void updateSerial()
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
  SIM800.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  SIM800.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  SIM800.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  SIM800.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  SIM800.println("AT+COPS?"); //Check whether it has registered in the network
  updateSerial();
}

void loop()
{
  updateSerial();
}
