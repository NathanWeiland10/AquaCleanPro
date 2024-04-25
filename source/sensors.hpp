#pragma once

#define NUM_SAMPLES 8

class PHSensor {
    public:
        PHSensor(int pin);

        float sample();

        float getValue();
    private:
      void sort();

      int pin;
      int index;
      float sampleArr[NUM_SAMPLES];
};