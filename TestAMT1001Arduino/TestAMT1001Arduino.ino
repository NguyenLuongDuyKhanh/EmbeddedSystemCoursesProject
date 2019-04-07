#include "amt1001_ino.h"

#define tempPin A0
#define humPin A1

void setup()
{
  pinMode(tempPin,INPUT);
  pinMode(humPin,INPUT);
  Serial.begin(9600);
}
void loop()
{
  // Get Temperature
  uint16_t step = analogRead(tempPin);
  uint16_t temperature = amt1001_gettemperature(step);
  Serial.print("Nhiet: ");
  Serial.println(temperature);
  
  // Get Humidity
  uint16_t step1 = analogRead(humPin);
  double volt = (double)step1 * (5.0 / 1023.0);
  uint16_t humidity = amt1001_gethumidity(volt);
  Serial.print("am: ");
  Serial.println(humidity);
  delay(100);
}
