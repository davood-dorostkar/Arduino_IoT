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
float GyroX, GyroY, GyroZ;
float angleXaccel, angleYaccel, angleXgyro, angleYgyro, angleZgyro;
int counter = 0;

void ErrorCalibration()
{
  float accelConversionRatio = 16384.0;
  float gyroConversionRatio = 131.0;
  int attempts = 1000;

  while (counter < attempts)
  {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    AccX = (Wire.read() << 8 | Wire.read()) / accelConversionRatio;
    AccY = (Wire.read() << 8 | Wire.read()) / accelConversionRatio;
    AccZ = (Wire.read() << 8 | Wire.read()) / accelConversionRatio;
    angleXaccel += atan(AccY / AccZ)*180/PI;
    angleYaccel += (atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180 / PI);
    counter++;
  }

  angleXaccel /= attempts;
  angleYaccel /= attempts;
  counter = 0;

  while (counter < attempts)
  {
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    GyroX = Wire.read() << 8 | Wire.read();
    GyroY = Wire.read() << 8 | Wire.read();
    GyroZ = Wire.read() << 8 | Wire.read();

    angleXgyro += (GyroX / gyroConversionRatio);
    angleYgyro += (GyroY / gyroConversionRatio);
    angleZgyro += (GyroZ / gyroConversionRatio);
    counter++;
  }

  angleXgyro /= attempts;
  angleYgyro /= attempts;
  angleZgyro /= attempts;
  counter = 0;

  Serial.print("angleXaccel: ");
  Serial.println(angleXaccel);
  Serial.print("angleYaccel: ");
  Serial.println(angleYaccel);
  Serial.print("angleXgyro: ");
  Serial.println(angleXgyro);
  Serial.print("angleYgyro: ");
  Serial.println(angleYgyro);
  Serial.print("angleZgyro: ");
  Serial.println(angleZgyro);
  Serial.println();
}
void setup()
{
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
}

void loop()
{
  ErrorCalibration();
  Serial.println("=====================");
}