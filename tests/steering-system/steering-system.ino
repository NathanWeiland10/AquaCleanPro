#include "Arduino.h"
#include "motor.hpp"
#include "steering-system.hpp"

#define TEMP_PIN 1
#define PH_PIN 2
#define DIST_RX_PIN 3
#define DIST_TX_PIN 4
#define LEFT_MOTOR_E_PIN 5
#define LEFT_MOTOR_M_PIN 6
#define RIGHT_MOTOR_E_PIN 5
#define RIGHT_MOTOR_M_PIN 6
#define POSTGREST_URL "http://aquacleanpro.org:3000/water_data"
#define TURN_WITHIN_DISTANCE 30

WiFiManager wifiManager; ///< WiFi manager instance used to create WiFi portal
WiFiManagerParameter runtimeParam; ///< Device runtime parameter configured in WiFi portal

int totalRuntime = -1; ///< Total time in seconds that the device will run before shutting down. Initialized at -1 until configured from WiFi portal.
int runtime = 0; ///< Time in seconds that the device has been active.
hw_timer_t *runtimeTimer = NULL; ///< Hardware timer used to increment runtime every second.

TemperatureSensor tempSensor(TEMP_PIN);
PHSensor phSensor(PH_PIN);
DistanceSensor distSensor(DIST_RX_PIN, DIST_TX_PIN);
Motor leftMotor(LEFT_MOTOR_E_PIN, LEFT_MOTOR_M_PIN);
Motor rightMotor(RIGHT_MOTOR_E_PIN, RIGHT_MOTOR_M_PIN);
SteeringSystem steeringSystem(leftMotor, rightMotor);

/// @brief Interrupt service routine that increments runtime every second.
void IRAM_ATTR onTimer(){
    runtime++;
    steeringSystem.update();
}

/// @brief Runs once on start-up. Initializes WiFi, ISR, and Serial connection
void setup() {
    Serial.begin(115200);
    initTimer();
    initWifiPortal();
    steeringSystem.go();
}

/// @brief Main update loop
void loop() {
    wifiManager.process();
    
    uploadMeasurements();
    steer();
}

/// @brief Initializes the hardware timer used to calculate device runtime.
void initTimer(){
    runtimeTimer = timerBegin(0, 80, true);
    timerAttachInterrupt(runtimeTimer, &onTimer, true);
    timerAlarmWrite(runtimeTimer, 1000000, true);
    timerAlarmEnable(runtimeTimer);
}

/// @brief Initializes the WiFi portal to obtain network credentials.
void initWifiPortal(){
    wifiManager.resetSettings(); // Remove in real build
    wifiManager.setConfigPortalBlocking(true);
    const char* runtimeHtml = "<br/><label for='runtime'>Runtime</label><br><input type='radio' name='runtime' value='15' checked> 15 minutes <br><input type='radio' name='runtime' value='30'> 30 minutes <br><input type='radio' name='runtime' value='60'> 1 hour";
    
    new (&runtimeParam) WiFiManagerParameter(runtimeHtml); 
    wifiManager.addParameter(&runtimeParam);
    wifiManager.setSaveParamsCallback(saveParamCallback);

    std::vector<const char *> menu = {"wifi","param","sep","restart","exit"};
    wifiManager.setMenu(menu);
    wifiManager.setClass("invert"); // Dark mode
    wifiManager.setConfigPortalTimeout(600);
    wifiManager.autoConnect("AquaClean Pro Setup"); 
}

/// @brief Saves runtime setting from WiFi portal to device
void saveParamCallback(){
    if(wifiManager.server->hasArg("runtime")) {
        totalRuntime = wifiManager.server->arg("runtime").toInt();
    }
}

/// @brief Uploads the temperature and pH data to PostgREST (currently uploads fake data)
/// @return The HTTP response code
int httpUpload(float temp, float ph){
    if (WiFi.status() == WL_CONNECTED) { 
      HTTPClient http;
      http.begin(POSTGREST_URL);
      int httpResponseCode = http.POST("{ \"temp\": " + String(temp) + ", \"ph\": " + String(ph) + " }");
      http.end();
      return httpResponseCode;
    }
    else return 0;
}

/// @brief Gets and uploads temperature and pH measurements to PostgREST
/// @return Returns the HTTP response code
int uploadMeasurements(){
    float temp = tempSensor.getValue();
    float ph = phSensor.getValue();

    return httpUpload(temp, ph);
}

/// @brief Detects walls and steers the craft around them
void steer(){
    if (distSensor.getValue() < TURN_WITHIN_DISTANCE)
    {
        steeringSystem.turnRight();
    }
}