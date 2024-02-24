#include <DallasTemperature.h>
#include <OneWire.h>

const int PH_PIN = 32, 
          TEMP_PIN = 22, 
          PH_ERROR = -127, 
          DELAY = 100;

float phVal = 0, tempVal = 0;
int readVal = 0;

OneWire oneWire (TEMP_PIN);  // creates the OneWire object using a specific pin
DallasTemperature sensor (&oneWire);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(PH_PIN, INPUT);
  sensor.begin ();
}

void loop() {
  // put your main code here, to run repeatedly:
  readVal = analogRead(PH_PIN);
  //Read value / 4095 (max value of 12 bit int) * 14 (highest value of ph)
  phVal = ((float) readVal / 4095.0) * 14;
  Serial.print("Current PH: ");
  Serial.print(phVal);

  sensor.requestTemperatures ();
  float tempVal = sensor.getTempCByIndex (0);

  if(tempVal == PH_ERROR){
    Serial.println ("Temperature Sensor Not Found.");
    delay (DELAY);
    return;
  }

  Serial.print ("Temperature: ");
  Serial.print (tempVal);
  Serial.println ("ºC");
  delay(DELAY); // this speeds up the simulation
}
