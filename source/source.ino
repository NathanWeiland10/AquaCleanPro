#include "Arduino.h"
#include <WiFiManager.h>

WifiManager wifiManager; ///< Wifi manager instance used to create WiFi portal
WifiManagerParameter runtimeParam; ///< Device runtime parameter configured in WiFi portal

int totalRuntime = -1; ///< Total time in seconds that the device will run before shutting down. Initialized at -1 until configured from WiFi portal.
int runtime = 0; ///< Time in seconds that the device has been active.
hw_timer_t *runtimeTimer = NULL; ///< Hardware timer used to increment runtime every second.

/// @brief Interrupt service routine that increments runtime every second.
void IRAM_ATTR onTimer(){
    runtime++;
}

/// @brief Runs once on start-up
void setup() {
    initTimer();
}

/// @brief Main update loop
void loop() {
    wifiManager.process();
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
    wifiManager.setConfigPortalBlocking(false);
    const char* runtimeHtml = "<br/><label for='runtime'>Runtime</label><br><input type='radio' name='runtime' value='15' checked> 15 minutes <br><input type='radio' name='runtime' value='30'> 30 minutes <br><input type='radio' name='runtime' value='60'> 1 hour";
    
    new (&runtimeParam) WiFiManagerParameter(runtimeHtml); 
    wifiManager.addParameter(&runtimeParam);
    wifiManager.setSaveParamCallback(saveParamCallback);

    std::vector<const char *> menu = {"wifi","param","sep","restart","exit"};
    wifiManager.setMenu(menu);
    wifiManager.setClass("invert"); // Dark mode
    wifiManager.setConfigPortalTimeout(600);
    wifiManager.autoConnect("AquaClean Pro Setup"); 
}

/// @brief Saves runtime setting from WiFi portal to device
void saveParamCallback(){
    if(wifiManager.server->hasArg("runtime")) {
        totalRuntime = stoi(wifiManager.server->arg("runtime"));
    }
}