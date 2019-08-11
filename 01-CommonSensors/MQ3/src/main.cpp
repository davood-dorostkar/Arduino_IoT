#include <Arduino.h>
/*
SanatBazar
Arduino Tutorial Series
Author: Davood Dorostkar
Website: www.sanatbazar.com

*/

#define sensorPin A0
#define RL 200
#define R0 1471

float Alcohol_density(float ratio)
{
  float density = (0.2333 * ratio + 0.2499) / (pow(ratio, 2) +0.1666 * ratio -0.003644);
  return density;
}

float sensorRead()
{
  int i = 0;
  float VRL = 0;
  do
  {
    VRL = VRL + analogRead(sensorPin);
    i++;
  } while (i < 100);
  return VRL / 100;
}

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  float VRL = sensorRead() * 5 / 1023;
  float Rs = RL * (5 - VRL) / VRL;
  float ratio = Rs / R0;
  float density = Alcohol_density(ratio);
  Serial.print("Alcohol density is = ");
  Serial.print(density);
  Serial.println("mg/L");
  if (density < 3)
    Serial.println("Safe");
  else if (density > 3 && density < 6)
    Serial.println("Warning");
  else if (density > 6 && density < 10)
    Serial.println("Danger");
  else if (density > 10)
    Serial.println("Extremely high");
  Serial.println("\n\n");
  delay(1000);
}