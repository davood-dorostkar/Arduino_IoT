#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <SPI.h>
#include <MFRC522.h>

#define ResetPin 9
#define CSPin 10
MFRC522 RFID(CSPin, ResetPin);

void setup()
{
	Serial.begin(9600);
	SPI.begin();
	RFID.PCD_Init();
	delay(10);
	RFID.PCD_DumpVersionToSerial();
	Serial.println("Approximate your RFID tag...");
}

void loop()
{
	if (!RFID.PICC_IsNewCardPresent())
	{
		return;
	}
	if (!RFID.PICC_ReadCardSerial())
	{
		return;
	}
	RFID.PICC_DumpToSerial(&(RFID.uid));
}