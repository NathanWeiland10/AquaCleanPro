#include "sensors.hpp"
#include "Arduino.h"

/// @brief Default constructor for the base Sensor class.
Sensor::Sensor(){
    pin = 0;
    index = 0;
    memset(sampleArr, 0, NUM_SAMPLES);
}

/// @brief Adds a single sample to the sample array.
/// @return The value of the sample taken.
float Sensor::sample(){
    float sample = analogRead(pin);
    sampleArr[index] = sample;
    index = (index == NUM_SAMPLES - 1) ? 0 : index + 1;
    return sample;
}

/// @brief Sorts the samples and returns the median value.
/// @return The median value of the samples taken.
float Sensor::getValue(){
    sort();
    return sampleArr[NUM_SAMPLES / 2];
}

/// @brief Sorts the sample array by value so that the median can be found.
void Sensor::sort()
{
    int i, j;
    bool swapped;
    for (i = 0; i < NUM_SAMPLES - 1; i++) {
        swapped = false;
        for (j = 0; j < NUM_SAMPLES - i - 1; j++) {
            if (sampleArr[j] >sampleArr[j + 1]) {
                float tmp = sampleArr[j];
                sampleArr[j] = sampleArr[j + 1];
                sampleArr[j + 1] = tmp;
                swapped = true;
            }
        }
 
        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }
}

/// @brief Constructor for the TemperatureSensor class.
/// @param pinNum The pin number connected to the temperature sensor.
TemperatureSensor::TemperatureSensor(int pinNum){
    pin = pinNum;
    tempSensor = DS18B20(pin);
}

/// @brief Adds a single sample to the sample array.
/// @return The value of the sample taken.
float TemperatureSensor::sample(){
    float sample = tempSensor.getTempF();
    sampleArr[index] = sample;
    index = (index == NUM_SAMPLES - 1) ? 0 : index + 1;
    return sample;
}

/// @brief Constructor for the pH sensor class
/// @param pinNum The pin number connected to the pH sensor
PHSensor::PHSensor(int pinNum){
    pin = pinNum;
}

/// @brief Adds a single sample to the sample array.
/// @return The value of the sample taken.
float PHSensor::sample(){
    float sample = analogRead(pin);
    sampleArr[index] = sample;
    index = (index == NUM_SAMPLES - 1) ? 0 : index + 1;
    return sample;
}

/// @brief Sorts the samples and returns the median value.
/// @return The median value of the samples taken converted to a pH value
float PHSensor::getValue(){
    sort();
    return sampleArr[NUM_SAMPLES / 2] * (3.3 / 4095.0);
}