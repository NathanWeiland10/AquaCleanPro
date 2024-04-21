#include "battery.hpp"
#include "Arduino.h"


Battery battery();
void setup(){
    Serial.begin(115200);
}

void loop(){
    Serial.print(battery.getCharge());
    Serial.println("%");
    delay(1000);
}