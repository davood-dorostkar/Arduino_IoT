#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#include <Servo.h>
Servo motor;
#include <Wire.h>
const int MPU = 0x68;
float GyroX, GyroY, GyroZ;
float gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float gyroErrorX, gyroErrorY, gyroErrorZ;
float lastTime, thisTime, duration;

float errorGyroVelX = -3.37;
float errorGyroVelY = 0.82;
float errorGyroVelZ = 1.07;

void initIMU()
{
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
}

void readGyroscope()
{
  float gyroConversionRatio = 131.0;
  Wire.beginTransmission(MPU);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);
  GyroX = (Wire.read() << 8 | Wire.read()) / gyroConversionRatio - errorGyroVelX;
  GyroY = (Wire.read() << 8 | Wire.read()) / gyroConversionRatio - errorGyroVelY;
  GyroZ = (Wire.read() << 8 | Wire.read()) / gyroConversionRatio - errorGyroVelZ;
}

void setup()
{
  Serial.begin(115200);
  initIMU();
  motor.attach(3);
}
void loop()
{
  readGyroscope();
  lastTime = thisTime;
  thisTime = millis();
  duration = (thisTime - lastTime) / 1000;

  yaw += GyroZ * duration;
  Serial.println(yaw);
  motor.write(map(yaw, -90, 90, 180, 0));
}