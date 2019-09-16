#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <SPI.h>
#include <MFRC522.h>

#define CSPin 10
#define ResetPin 9
MFRC522 RFIDmodule(CSPin, ResetPin);
MFRC522::MIFARE_Key key;

int blockNumber = 61;
byte myData[16] = {" Sanatbazar.com "};
byte empty[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte writtenData[18];

int writeBlock(int blockNumber, byte dataAddress[])
{
  int largestModulo4Number = blockNumber / 4 * 4;
  int trailerBlock = largestModulo4Number + 3;
  if (blockNumber > 2 && (blockNumber + 1) % 4 == 0)
  {
    Serial.print(blockNumber);
    Serial.println(" is a trailer block number:");
    return 2;
  }
  Serial.print(blockNumber);
  Serial.println(" is a data block number:");

  byte status = RFIDmodule.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(RFIDmodule.uid));
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("PCD_Authenticate() failed: ");
    Serial.println(RFIDmodule.GetStatusCodeName(status));
    return 3;
  }

  status = RFIDmodule.MIFARE_Write(blockNumber, dataAddress, 16);

  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("MIFARE_Write() failed: ");
    Serial.println(RFIDmodule.GetStatusCodeName(status));
    return 4;
  }
  Serial.println("Data was written to selected block");
}

int readBlock(int blockNumber, byte dataAddress[])
{
  int largestModulo4Number = blockNumber / 4 * 4;
  int trailerBlock = largestModulo4Number + 3;

  byte status = RFIDmodule.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(RFIDmodule.uid));

  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("PCD_Authenticate() failed (read): ");
    Serial.println(RFIDmodule.GetStatusCodeName(status));
    return 3;
  }

  byte buffersize = 18;
  status = RFIDmodule.MIFARE_Read(blockNumber, dataAddress, &buffersize);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("MIFARE_read() failed: ");
    Serial.println(RFIDmodule.GetStatusCodeName(status));
    return 4;
  }
  Serial.println("Data was successfully read");
}

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  RFIDmodule.PCD_Init();
  Serial.println("Approximate your RFID tag...");

  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }
}

void loop()
{
  if (!RFIDmodule.PICC_IsNewCardPresent())
  {
    return;
  }
  if (!RFIDmodule.PICC_ReadCardSerial())
  {
    return;
  }
  Serial.println("Found a tag");
  writeBlock(blockNumber, myData);
  readBlock(blockNumber, writtenData);
  Serial.print("Your written data is: ");
  Serial.println(String((char*)writtenData));
  Serial.println("");
}