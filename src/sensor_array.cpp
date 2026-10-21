#include "sensor_array.h"
#include "hardware_config.h"

SensorArray::SensorArray()
    : _ch1(Pins::SENSOR_1_CS),
      _ch2(Pins::SENSOR_2_CS),
      _ch3(Pins::SENSOR_3_CS)
{
}

bool SensorArray::begin()
{
    bool allOk = true;
    allOk &= _ch1.begin();
    allOk &= _ch2.begin();
    allOk &= _ch3.begin();

    Adafruit_MAX31856* devices[NUM_CHANNELS] = { &_ch1, &_ch2, &_ch3 };
    for (int i = 0; i < NUM_CHANNELS; i++)
    {
        devices[i]->setThermocoupleType(MAX31856_TCTYPE_K);
        devices[i]->setConversionMode(MAX31856_CONTINUOUS);
    }

    return allOk;
}

void SensorArray::readChannel(Adafruit_MAX31856 &device, RateTracker &tracker,
                               unsigned long timestampMs,
                               float &outTemp, float &outRate, bool &outValid)
{
    outTemp  = device.readThermocoupleTemperature();
    outValid = (device.readFault() == 0);

    if (outValid)
    {
        outRate = tracker.update(outTemp, timestampMs);
    }
    else
    {
        outRate = 0.0f;
        tracker.reset(); // don't let a fault poison the next valid delta
    }
}

void SensorArray::readAll(unsigned long timestampMs, SensorFrame &frame)
{
    frame.timestampMs = timestampMs;

    readChannel(_ch1, _rate1, timestampMs, frame.temperatureC[0], frame.coolingRateCs[0], frame.valid[0]);
    readChannel(_ch2, _rate2, timestampMs, frame.temperatureC[1], frame.coolingRateCs[1], frame.valid[1]);
    readChannel(_ch3, _rate3, timestampMs, frame.temperatureC[2], frame.coolingRateCs[2], frame.valid[2]);
}
