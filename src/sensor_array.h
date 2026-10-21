#pragma once

#include <Adafruit_MAX31856.h>
#include "types.h"
#include "rate_tracker.h"

// Owns all three thermocouple channels and produces one SensorFrame
// per call, instead of exposing three independent sensor objects
// that the caller has to loop over and assemble itself.
class SensorArray
{
public:
    SensorArray();

    bool begin();
    void readAll(unsigned long timestampMs, SensorFrame &frame);

private:
    Adafruit_MAX31856 _ch1;
    Adafruit_MAX31856 _ch2;
    Adafruit_MAX31856 _ch3;

    RateTracker _rate1;
    RateTracker _rate2;
    RateTracker _rate3;

    static void readChannel(Adafruit_MAX31856 &device, RateTracker &tracker,
                             unsigned long timestampMs,
                             float &outTemp, float &outRate, bool &outValid);
};
