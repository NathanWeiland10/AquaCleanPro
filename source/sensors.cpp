#include "sensors.hpp"
#include "Arduino.h"
#include <SoftwareSerial.h>

#define PH_SLOPE 143.133
#define PH_OFFSET 526.035

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
    float sample = ((float) analogRead(pin) - PH_OFFSET) / PH_SLOPE;
    sampleArr[index] = sample;
    index = (index == NUM_SAMPLES - 1) ? 0 : index + 1;
    return sample;
}

/// @brief Default constructor for DistanceSensor class
/// @param rx Receiver pin for serial communication
/// @param tx Transmission pin for serial communication
DistanceSensor::DistanceSensor(int rx, int tx){
    SoftwareSerial serialComm(rx,tx);
}

/// @brief Gets distance value from DistanceSensor
/// @return Distance in centimeters (-1.0 if error)
float DistanceSensor::getValue(){
    unsigned char data[4] = {};

    // Get 4 bytes of data
    do{
        for (int i = 0; i < 4; i++){
            data[i] = serialComm.read();
        }
    } while (serialComm.read() == 0xff);

    serialComm.flush();

    // Calculate and return distance in cm
    if (data[0] == 0xff){
        int sum = (data[0] + data[1] + data[2]) & 0x00FF;

        if (sum == data[3]){
            return ((float) (data[1] << 8) + data[2]) / 10;
        }
    }
    // If error, return -1.0
    else return -1.0f;
}
