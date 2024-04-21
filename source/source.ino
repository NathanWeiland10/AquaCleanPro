#include "Arduino.h"
#include <WiFiManager.h>
#include <HTTPClient.h>
#include "sensors.hpp"
#include "motor.hpp"
#include "steering-system.hpp"
#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMP_PIN 27
#define PH_PIN 26
#define DIST_RX_PIN 14
#define DIST_TX_PIN 13
#define LEFT_MOTOR_E_PIN 17
#define LEFT_MOTOR_M_PIN 16
#define RIGHT_MOTOR_E_PIN 32
#define RIGHT_MOTOR_M_PIN 33
#define POSTGREST_URL "http://aquacleanpro.org:3000/water_data"
#define TURN_WITHIN_DISTANCE 30

WiFiManager wifiManager;            ///< WiFi manager instance used to create WiFi portal
WiFiManagerParameter runtimeParam;  ///< Device runtime parameter configured in WiFi portal

int totalRuntime = -1;            ///< Total time in seconds that the device will run before shutting down. Initialized at -1 until configured from WiFi portal.
int runtime = 0;                  ///< Time in seconds that the device has been active.
hw_timer_t *runtimeTimer = NULL;  ///< Hardware timer used to increment runtime every second.

OneWire oneWireTemp(TEMP_PIN);               ///< OneWire UART comm for temperature sensor
DallasTemperature tempSensor(&oneWireTemp);  ///< Temperature sensor

PHSensor phSensor(PH_PIN);
Motor leftMotor(LEFT_MOTOR_E_PIN, LEFT_MOTOR_M_PIN);
Motor rightMotor(RIGHT_MOTOR_E_PIN, RIGHT_MOTOR_M_PIN);
SteeringSystem steeringSystem(leftMotor, rightMotor);

/// @brief Interrupt service routine that increments runtime every second.
void IRAM_ATTR onTimer() {
  runtime++;
  steeringSystem.update();
}

/// @brief Runs once on start-up. Initializes WiFi, ISR, and Serial connection
void setup() {
  Serial.begin(115200);
  tempSensor.begin();
  initTimer();
  initWifiPortal();
  steeringSystem.go();
}

/// @brief Main update loop
void loop() {
  wifiManager.process();

  Serial.println("Sampling...");
  phSensor.sample();

  Serial.print("Uploading measurements... ");
  int httpResonseCode = uploadMeasurements();
  Serial.println(httpResonseCode);
}

/// @brief Initializes the hardware timer used to calculate device runtime.
void initTimer() {
  runtimeTimer = timerBegin(0, 80, true);
  timerAttachInterrupt(runtimeTimer, &onTimer, true);
  timerAlarmWrite(runtimeTimer, 1000000, true);
  timerAlarmEnable(runtimeTimer);
}

/// @brief Initializes the WiFi portal to obtain network credentials.
void initWifiPortal() {
  wifiManager.resetSettings();
  wifiManager.setConfigPortalBlocking(true);
  const char *runtimeHtml = "<br/><label for='runtime'>Runtime</label><br><input type='radio' name='runtime' value='15' checked> 15 minutes <br><input type='radio' name='runtime' value='30'> 30 minutes <br><input type='radio' name='runtime' value='60'> 1 hour";

  new (&runtimeParam) WiFiManagerParameter(runtimeHtml);
  wifiManager.addParameter(&runtimeParam);
  wifiManager.setSaveParamsCallback(saveParamCallback);

  std::vector<const char *> menu = { "wifi", "param", "sep", "restart", "exit" };
  wifiManager.setMenu(menu);
  wifiManager.setClass("invert");  // Dark mode
  wifiManager.setConfigPortalTimeout(600);
  wifiManager.autoConnect("AquaClean Pro Setup");
}

/// @brief Saves runtime setting from WiFi portal to device
void saveParamCallback() {
  if (wifiManager.server->hasArg("runtime")) {
    totalRuntime = wifiManager.server->arg("runtime").toInt();
  }
}

/// @brief Uploads the temperature and pH data to PostgREST (currently uploads fake data)
/// @return The HTTP response code
int httpUpload(float temp, float ph) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(POSTGREST_URL);
    int httpResponseCode = http.POST("{ \"temp\": " + String(temp) + ", \"ph\": " + String(ph) + " }");
    http.end();
    return httpResponseCode;
  } else return 0;
}

/// @brief Gets and uploads temperature and pH measurements to PostgREST
/// @return Returns the HTTP response code
int uploadMeasurements() {
  tempSensor.requestTemperatures();
  float temp = tempSensor.getTempFByIndex(0);
  float ph = phSensor.getValue();
  Serial.println("    Temp: " + String(temp) + " F");

  Serial.print("    pH: " + String(ph));

  return httpUpload(temp, ph);
}

/// @brief Gets the distance in cm from the ultrasonic sensor
/// @return Returns the distance in cm
float getDistance() {
  float distance;
  unsigned char checksum;
  char header;
  int data_buffer[4];

  Serial2.begin(9600, SERIAL_8N1, DIST_RX_PIN, DIST_TX_PIN);

  // Wait until 4 packets are available
  while (Serial2.available() < 3) {
    delay(100);
  }

  // Read until header is found
  do {
    data_buffer[0] = Serial2.read();
  } while (data_buffer[0] != 0xff);

  // Wait until 3 more packets are found
  while (Serial2.available() < 2) {
    delay(10);
  }

  for (int j = 1; j < 4; j++) {
    data_buffer[j] = Serial2.read();
  }

  // Get distance if checksum is valid
  checksum = data_buffer[0] + data_buffer[1] + data_buffer[2];
  if (data_buffer[3] == checksum) {
    distance = (float)((data_buffer[1] << 8) + data_buffer[2]) / 10;
  } else {
    distance = -1;
  }

  Serial2.end();
  return distance;
}

/// @brief Detects walls and steers the craft around them
void steer() {
  float distance = getDistance();
  Serial.println("Distance: " + String(distance) + " cm");
  if (distance < TURN_WITHIN_DISTANCE) {
    steeringSystem.turnRight();
  }
}
