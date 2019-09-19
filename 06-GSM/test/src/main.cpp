#include <Arduino.h>

#include <SoftwareSerial.h>
SoftwareSerial SIM800(2, 3);
int timeout;
String buffer;
String number = "+989217803834";

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

void getSMS()
{
  Serial.println("SIM800800L Read an SMS");
  delay(1000);
  SIM800.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
  Serial.write("Unread Message done");
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
  delay(1000);
  // sendSMS();
  // delay(15000);
  // callMe();
  // getSMS();
}
void loop()
{
  if (SIM800.available() > 0)
  {
    Serial.println("Just recieved a SMS : ");
    Serial.write(SIM800.read());
  }
}
