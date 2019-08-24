#include <Arduino.h>

#include <Wire.h>
const int MPU = 0x68; // MPU6050 I2C address
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int counter = 0;

void ErrorCalibration()
{
  float accelConversionRatio = 16384.0;
  float gyroConversionRatio = 131.0;
  int attempts = 2000;
  while (counter < attempts)
  {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    AccX = (Wire.read() << 8 | Wire.read()) / accelConversionRatio;
    AccY = (Wire.read() << 8 | Wire.read()) / accelConversionRatio;
    AccZ = (Wire.read() << 8 | Wire.read()) / accelConversionRatio;
    // Sum all readings
    AccErrorX += ((atan((AccY) / sqrt(pow((AccX), 2) + pow((AccZ), 2))) * 180 / PI));
    AccErrorY += ((atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180 / PI));
    counter++;
  }
  //Divide the sum by 200 to get the error value
  AccErrorX /= attempts;
  AccErrorY /= attempts;
  counter = 0;
  // Read gyro values 200 times
  while (counter < attempts)
  {
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    GyroX = Wire.read() << 8 | Wire.read();
    GyroY = Wire.read() << 8 | Wire.read();
    GyroZ = Wire.read() << 8 | Wire.read();
    // Sum all readings
    GyroErrorX += (GyroX / gyroConversionRatio);
    GyroErrorY += (GyroY / gyroConversionRatio);
    GyroErrorZ += (GyroZ / gyroConversionRatio);
    counter++;
  }
  //Divide the sum by 200 to get the error value
  GyroErrorX /= attempts;
  GyroErrorY /= attempts;
  GyroErrorZ /= attempts;
  // Print the error values on the Serial Monitor
  Serial.print("AccErrorX: ");
  Serial.println(AccErrorX);
  Serial.print("AccErrorY: ");
  Serial.println(AccErrorY);
  Serial.print("GyroErrorX: ");
  Serial.println(GyroErrorX);
  Serial.print("GyroErrorY: ");
  Serial.println(GyroErrorY);
  Serial.print("GyroErrorZ: ");
  Serial.println(GyroErrorZ);
  Serial.println();
}
void setup()
{
  Serial.begin(115200);
  Wire.begin();                // Initialize comunication
  Wire.beginTransmission(MPU); // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);            // Talk to the register 6B
  Wire.write(0x00);            // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);  //end the transmission
}

void loop()
{
  ErrorCalibration();
  delay(500);
}