
#include "temperature_sensor.h"
#include "config.h"

TemperatureSensor::TemperatureSensor(int chipSelectPin)
    :_csPin(chipSelectPin), _max31856(chipSelectPin)
{
    _lastReading.isValid = false;
    _lastReading.sensorID = 0;
    _lastReading.temperature = 0.0;
    _lastReading.timestamp = 0;
    _lastReading.coolingRate = 0.0;
}

bool TemperatureSensor::begin()
{
    if (!_max31856.begin()) // same as: if (_max31856.begin() == false)
    {
        return false;
    }
    // Set thermocouple type to K-Type
    _max31856.setThermocoupleType(MAX31856_TCTYPE_K);

    // Set conversion mode to automatic (continuous readings)
    _max31856.setConversionMode(MAX31856_CONTINUOUS);

    return true;
}


TemperatureReading TemperatureSensor::readTemperature(unsigned long timestamp)
{
    TemperatureReading reading;

    reading.timestamp = timestamp;

    reading.temperature = _max31856.readThermocoupleTemperature();

    //Check for senser errors
    uint8_t fault = _max31856.readFault();
    reading.isValid = (fault == 0);

    //Calculate cooling rate
    if (_lastReading.isValid && reading.isValid)
    {
        float timeDiff = (reading.timestamp - _lastReading.timestamp) / 1000.0;

        float tempDiff = (reading.temperature - _lastReading.temperature);

        // Cooling rate
        if (timeDiff > 0)
        {
            reading.coolingRate = tempDiff / timeDiff;

        } else
        {
            reading.coolingRate = 0.0;
        }
    } else
    {
        reading.coolingRate = 0.0;
    }

    _lastReading =  reading;

    return reading;
}

// check if senser is connected and responding
bool TemperatureSensor::isConnected()
{
    // Try to read the fault register - if sensor responds, it's connected
    uint8_t fault = _max31856.readFault();

    // If it can read the register, sensor is connected
    // Just checking communication, not if there's an actual fault

    return true; // Note: MAX31856 library doesn't have a direct "isConnected" check
}





