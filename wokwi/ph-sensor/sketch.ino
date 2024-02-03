const int PH_PIN = 34;
float phVal = 0;
int readVal = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(PH_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  readVal = analogRead(PH_PIN);
  //Read value / 4095 (max value of 12 bit int) * 14 (highest value of ph)
  phVal = ((float) readVal / 4095.0) * 14;
  Serial.print("Current PH: ");
  Serial.print(phVal);
  Serial.print(" Read value: ");
  Serial.print(readVal);
  Serial.print("\n");
  delay(10); // this speeds up the simulation
}
