#include <DS18B20.h>
#define NUM_SAMPLES 32

class Sensor{
    public: 
        Sensor();

        float sample();

        float getValue();
    protected:
        void sort();

        int pin;
        int index;
        float sampleArr[NUM_SAMPLES];
};

class TemperatureSensor : public Sensor {
    public:
        TemperatureSensor(int pin);

        float sample();
    private:
        DS18B20 tempSensor = DS18B20(2);
};

class PHSensor : public Sensor {
    public:
        PHSensor(int pin);

        float sample();
        
        float getValue();
};

class DistanceSensor {
    public:
        DistanceSensor(int pin);

        float getValue();
    private:
        int pin;
};