#include "sensors.hpp"

PHSensor phSensor(26);

void setup() 
{
  Serial.begin(115200);
}
void loop() {
  for (int i = 0; i < 32; i++){
    phSensor.sample();
    delay(100);
  }
  Serial.println(phSensor.getValue());
}
