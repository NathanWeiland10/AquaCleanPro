#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <WiFiManager.h>
#include <HTTPClient.h>

#include "tinyaes/aes.hpp"
#include "Arduino.h"
#include "sensors.hpp"

#define AES128 1

const char* POSTGREST_URL = "http://aquacleanpro.org:3000/water_data"; ///< PostgREST URL for water data table
WiFiManager wifiManager; ///< WiFi manager instance used to create WiFi portal
WiFiManagerParameter runtimeParam; ///< Device runtime parameter configured in WiFi portal

int totalRuntime = -1; ///< Total time in seconds that the device will run before shutting down. Initialized at -1 until configured from WiFi portal.
int runtime = 0; ///< Time in seconds that the device has been active.
hw_timer_t *runtimeTimer = NULL; ///< Hardware timer used to increment runtime every second.
struct AES_ctx ctx;
unsigned char key = "<ENTER KEY HERE>";
unsigned char iv = "<ENTER IV HERE>";

/// @brief Interrupt service routine that increments runtime every second.
void IRAM_ATTR onTimer(){
    runtime++;
}

void setup() 
{
    Serial.begin(115200);
    initTimer();
    initWifiPortal();

    // Set up the context for later encrypting
    AES_init_ctx_iv(&ctx, key, iv);
    // TODO, gather info from sensors, compile into json
}

void loop() 
{
    wifiManager.process();
    httpUpload(100, 7);
    delay(1000);
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

void httpUpload(double temp, double ph)
{
  if (WiFi.status() == WL_CONNECTED) 
  { 
    // Set up the connection
    HTTPClient http;
    http.begin(POSTGREST_URL);
    // Encrypt the buffer
    char data[100];
    sprintf(data, "[{\"time\":\"%s\",\"temp\":%f,\"ph\":%f}]", String(10 * sin(runtime)), temp, ph);
    // Pad buffer to be divisible by 16
    size_t paddedLength = strlen(data) + 16 - (strlen(data) % 16);
    unsigned char paddedData[paddedLength];
    // Copy data to paddedData, but add padding at the end
    for(int i = 0; i < paddedLength; i++)
    {
        if (i < strlen(testData))
        {
            paddedData[i] = testData[i];
        }
        else
        {
            paddedData[i] = 16 - (strlen(testData) % 16);
        }
    }
    AES_CBC_encrypt_buffer(&ctx, paddedData, paddedLength);
    // Send out encrypted buffer
    int httpResponseCode = http.POST(data);
    Serial.println(httpResponseCode);
    http.end();
  }
}
