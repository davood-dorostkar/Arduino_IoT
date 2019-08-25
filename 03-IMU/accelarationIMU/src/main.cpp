#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <Wire.h>
const int MPU = 0x68;
float AccX, AccY, AccZ;
float velX, velY, velZ;
float posX, posY, posZ;
float lastTime, thisTime, duration;

void accelerationCalc()
{
  float accelConversionRatio = 16384.0;
  int attempts = 20;
  AccX = 0;
  AccY = 0;
  AccX = 0;
  for (int counter = 0; counter < attempts; counter++)
  {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    AccX += (Wire.read() << 8 | Wire.read()) / accelConversionRatio;
    AccY += (Wire.read() << 8 | Wire.read()) / accelConversionRatio;
    AccZ += (Wire.read() << 8 | Wire.read()) / accelConversionRatio;
  }
  AccX = AccX / attempts * 9.81;
  AccY = AccY / attempts * 9.81;
  AccZ = (AccZ / attempts - 1) * 9.81;
  Serial.print("X Acceleration: ");
  Serial.print(AccX, 6);
  Serial.print("\t");
  Serial.print("Y Acceleration: ");
  Serial.print(AccY, 6);
  Serial.print("\t");
  Serial.print("Z Acceleration: ");
  Serial.print(AccZ, 6);
  Serial.println();
}

void velocityCalc()
{
  velX += AccX * duration;
  velY += AccY * duration;
  velZ += AccZ * duration;
  //   Serial.print("X Velocity: ");
  //   Serial.print(velX);
  //   Serial.print("\t");
  //   Serial.print("Y Velocity: ");
  //   Serial.print(velY);
  //   Serial.print("\t");
  //   Serial.print("Z Velocity: ");
  //   Serial.print(velZ);
  //   Serial.println();
}

void positionCalc()
{
  posX += velX * duration;
  posY += velY * duration;
  posZ += velZ * duration;
  //   Serial.print("X Position: ");
  //   Serial.print(posX);
  //   Serial.print("\t");
  //   Serial.print("Y Position: ");
  //   Serial.print(posY);
  //   Serial.print("\t");
  //   Serial.print("Z Position: ");
  //   Serial.print(posZ);
  //   Serial.println();
}

void initIMU()
{
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
}

void setup()
{
  Serial.begin(115200);
  initIMU();
}

void loop()
{
  lastTime = thisTime;
  thisTime = millis();
  duration = (thisTime - lastTime) / 1000;
  accelerationCalc();
  Serial.println("=====================");
  velocityCalc();
  Serial.println("=====================");
  positionCalc();
  Serial.println("=====================");
  Serial.println("=====================");
  Serial.println("=====================");
}