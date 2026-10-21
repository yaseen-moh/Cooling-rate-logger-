

#ifndef CCRL_TEMPERATURE_SENSOR_H
#define CCRL_TEMPERATURE_SENSOR_H

#include <Adafruit_MAX31856.h> // look in .ini file for lib info
#include "data_structures.h"


class TemperatureSensor
{
    public:
        TemperatureSensor(int chipSelectPin);

        bool begin();
        TemperatureReading readTemperature(unsigned long timestamp);
        bool isConnected();

    private:
        int _csPin;
        Adafruit_MAX31856 _max31856;
        TemperatureReading _lastReading;

};


#endif //CCRL_TEMPERATURE_SENSOR_H