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
// float accX, accY, accZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float accErrorX, accErrorY, gyroErrorX, gyroErrorY, gyroErrorZ;
float lastTime, thisTime, duration;

// float errorAccAngleX = -1.22;
// float errorAccAngleY = 0.13;
// float errorGyroVelX = -3.37;
// float errorGyroVelY = 0.82;
float errorGyroVelZ = 1.07;

void initIMU()
{
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
}

// void readAccelerometer()
// {
//   float accelConversionRatio = 16384.0;
//   Wire.beginTransmission(MPU);
//   Wire.write(0x3B);
//   Wire.endTransmission(false);
//   Wire.requestFrom(MPU, 6, true);
//   accX = (Wire.read() << 8 | Wire.read()) / accelConversionRatio;
//   accY = (Wire.read() << 8 | Wire.read()) / accelConversionRatio;
//   accZ = (Wire.read() << 8 | Wire.read()) / accelConversionRatio;
//   accAngleX = atan(accY / accZ) * 180 / PI - errorAccAngleX;
//   accAngleY = (atan(-1 * accX / sqrt(pow(accY, 2) + pow(accZ, 2))) * 180 / PI) - errorAccAngleY;
// }

void readGyroscope()
{
  float gyroConversionRatio = 131.0;
  Wire.beginTransmission(MPU);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);
  // GyroX = (Wire.read() << 8 | Wire.read()) / gyroConversionRatio - errorGyroVelX;
  // GyroY = (Wire.read() << 8 | Wire.read()) / gyroConversionRatio - errorGyroVelY;
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
  // readAccelerometer();
  readGyroscope();
  lastTime = thisTime;
  thisTime = millis();
  duration = (thisTime - lastTime) / 1000;

  // gyroAngleX += GyroX * duration;
  // gyroAngleY += GyroY * duration;
  yaw += GyroZ * duration;
  // roll = 0.95 * gyroAngleX + 0.05 * accAngleX;
  // pitch = 0.95 * gyroAngleY + 0.05 * accAngleY;
  motor.write(map(yaw, -90, 90, 0, 180));
}