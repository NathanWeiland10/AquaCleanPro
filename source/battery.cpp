#include "battery.hpp"
#include "Arduino.h"

Battery::Battery(int pinNum, float volt){
    pin = pinNum;
    voltage = volt;
}

float Battery::getCharge(){
    return (( (float) analogRead(pin) / 4095) * 5) / voltage;
}