#include "battery.hpp"
#-.include "Arduino.h"

Battery::Battery(int pinNum, float volt){
    pin = pinNum;
    voltage = volt;
}

float Battery::getCharge(){
    return analogRead(pinNum) * (5.0 / (4095.0 / (voltage / 5.0)));
}