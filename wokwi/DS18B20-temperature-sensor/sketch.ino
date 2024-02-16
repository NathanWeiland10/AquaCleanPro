#define DELAY 1000
#define ERR -127
#define SENSOR_PIN 16

// DS18B20 Temperature Sensor using ESP32
/*
i. -55 to 125
ii Uses 1 Wire Communication (1 data line (must be pulled HIGH) and 1 gnd wire)
iii. user configurable resolution between 9 to 12-bits
iv. 64-bit Serial Code whihc is unique to each sensor

GND, DQ (must be pulled HIGH), VDD
*/
#include <DallasTemperature.h>
#include <OneWire.h>

OneWire oneWire (SENSOR_PIN);  // creates the OneWire object using a specific pin
DallasTemperature sensor (&oneWire);

void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);
  sensor.begin ();
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor.requestTemperatures ();
  float temp = sensor.getTempCByIndex (0);

  if(temp == ERR){
    Serial.println ("Temperature Sensor Not Found.");
    delay (DELAY);
    return;
  }

  Serial.print ("Temperature: ");
  Serial.print (temp);
  Serial.println ("ºC");
  delay (DELAY);
}
