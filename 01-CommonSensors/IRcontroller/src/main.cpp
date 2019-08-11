#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <IRremote.h>
#define ledPin 9
int lastLedState = 0;
IRrecv irrecv(11);
decode_results results;

void ledset(const String &input)
{
  int currentLedState;
  if (input == "VOL-")
    currentLedState = lastLedState - 30;
  if (input == "VOL+")
    currentLedState = lastLedState + 30;
  if (currentLedState < 0)
    currentLedState = 0;
  else if (currentLedState > 255)
    currentLedState = 255;
  analogWrite(ledPin, currentLedState);
  lastLedState = currentLedState;
}

String readIR()
{
  String characterIR;
  if (irrecv.decode(&results))
  {
    switch (results.value)
    {
    case 3810010651:
      characterIR = "CH-";
      break;
    case 5316027:
      characterIR = "CH";
      break;
    case 4001918335:
      characterIR = "CH+";
      break;
    case 1386468383:
      characterIR = "PREV";
      break;
    case 3622325019:
      characterIR = "NEXT";
      break;
    case 553536955:
      characterIR = "PLAY/PAUSE";
      break;
    case 4034314555:
      characterIR = "VOL-";
      break;
    case 2747854299:
      characterIR = "VOL+";
      break;
    case 3855596927:
      characterIR = "EQ";
      break;
    case 3238126971:
      characterIR = "0";
      break;
    case 2538093563:
      characterIR = "100+";
      break;
    case 4039382595:
      characterIR = "200+";
      break;
    case 2534850111:
      characterIR = "1";
      break;
    case 1033561079:
      characterIR = "2";
      break;
    case 1635910171:
      characterIR = "3";
      break;
    case 2351064443:
      characterIR = "4";
      break;
    case 1217346747:
      characterIR = "5";
      break;
    case 71952287:
      characterIR = "6";
      break;
    case 851901943:
      characterIR = "7";
      break;
    case 465573243:
      characterIR = "8";
      break;
    case 1053031451:
      characterIR = "9";
      break;

    default:
      break;
    }
    irrecv.resume();
  }
  return characterIR;
}

void setup()
{
  irrecv.enableIRIn();
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  String characterIR = readIR();
  ledset(characterIR);
}