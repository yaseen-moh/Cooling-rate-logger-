#pragma once

// Tracks one channel's previous (temp, time) pair and derives dT/dt.
// Kept separate from the sensor driver so the rate math can be tested
// or swapped (e.g. smoothed) without touching SPI/MAX31856 code.
class RateTracker
{
public:
    RateTracker();

    float update(float temperatureC, unsigned long timestampMs);
    void  reset();

private:
    float _prevTemp;
    unsigned long _prevTime;
    bool _hasPrev;
};
