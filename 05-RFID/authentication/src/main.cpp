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

String memberID = "81F7C42F";
String tagID = "";
MFRC522 RFIDmodule(CSPin, ResetPin);

boolean readTagID()
{
	if (!RFIDmodule.PICC_IsNewCardPresent())
		return false;
	if (!RFIDmodule.PICC_ReadCardSerial())
		return false;
	tagID = "";
	for (uint8_t i = 0; i < 4; i++)
		tagID.concat(String(RFIDmodule.uid.uidByte[i], HEX));
	tagID.toUpperCase();
	RFIDmodule.PICC_HaltA();
	return true;
}

void setup()
{
	Serial.begin(9600);
	SPI.begin();
	RFIDmodule.PCD_Init();
	Serial.println("Approximate your RFID tag ...");
	Serial.println("");
}

void loop()
{
	while (readTagID())
	{
		if (tagID == memberID)
		{
			Serial.println("You're Welcome!");
		}
		else
		{
			Serial.println("You're not registered!");
		}
		Serial.print(" ID : ");
		Serial.println(tagID);
		Serial.println("");
		delay(2000);
		Serial.println("Approximate your RFID tag ...");
		Serial.println("");
	}
}