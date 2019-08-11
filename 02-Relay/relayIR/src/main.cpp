#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#define fanPin 3
#define lampPin 2
#include <IRremote.h>
IRrecv irrecv(11);
decode_results results;

String readIR()
{
  String commandIR;
  if (irrecv.decode(&results))
  {
    switch (results.value)
    {
    case 3810010651:
      commandIR = "CH-";
      break;
    case 5316027:
      commandIR = "CH";
      break;
    case 4001918335:
      commandIR = "CH+";
      break;
    case 1386468383:
      commandIR = "PREV";
      break;
    case 3622325019:
      commandIR = "NEXT";
      break;
    case 553536955:
      commandIR = "PLAY/PAUSE";
      break;
    case 4034314555:
      commandIR = "VOL-";
      break;
    case 2747854299:
      commandIR = "VOL+";
      break;
    case 3855596927:
      commandIR = "EQ";
      break;
    case 3238126971:
      commandIR = "0";
      break;
    case 2538093563:
      commandIR = "100+";
      break;
    case 4039382595:
      commandIR = "200+";
      break;
    case 2534850111:
      commandIR = "1";
      break;
    case 1033561079:
      commandIR = "2";
      break;
    case 1635910171:
      commandIR = "3";
      break;
    case 2351064443:
      commandIR = "4";
      break;
    case 1217346747:
      commandIR = "5";
      break;
    case 71952287:
      commandIR = "6";
      break;
    case 851901943:
      commandIR = "7";
      break;
    case 465573243:
      commandIR = "8";
      break;
    case 1053031451:
      commandIR = "9";
      break;

    default:
      break;
    }
    irrecv.resume();
  }
  return commandIR;
}

void doLamp(const String &input)
{
  if (input == "VOL-")
  {
    digitalWrite(lampPin, HIGH);
  }
  else if (input == "VOL+")
  {
    digitalWrite(lampPin, LOW);
  }
}

void doFan(const String &input)
{
  if (input == "CH-")
  {
    digitalWrite(fanPin, HIGH);
  }
  else if (input == "CH+")
  {
    digitalWrite(fanPin, LOW);
  }
}

void arduinoInit()
{
  digitalWrite(fanPin,HIGH);
  digitalWrite(lampPin,HIGH);
}
void setup()
{
  pinMode(fanPin, OUTPUT);
  pinMode(lampPin, OUTPUT);
  irrecv.enableIRIn();
  arduinoInit();
}

void loop()
{
  String commandIR = readIR();
  if (commandIR == "CH-" || commandIR == "CH+")
  {
    doFan(commandIR);
  }
  if (commandIR == "VOL-" || commandIR == "VOL+")
  {
    doLamp(commandIR);
  }
}