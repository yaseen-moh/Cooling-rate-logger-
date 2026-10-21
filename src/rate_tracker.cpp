#include "rate_tracker.h"

RateTracker::RateTracker()
    : _prevTemp(0.0f), _prevTime(0), _hasPrev(false)
{
}

float RateTracker::update(float temperatureC, unsigned long timestampMs)
{
    float rate = 0.0f;

    if (_hasPrev)
    {
        float dtSeconds = (timestampMs - _prevTime) / 1000.0f;
        if (dtSeconds > 0.0f)
        {
            rate = (temperatureC - _prevTemp) / dtSeconds;
        }
    }

    _prevTemp = temperatureC;
    _prevTime = timestampMs;
    _hasPrev  = true;

    return rate;
}

void RateTracker::reset()
{
    _hasPrev = false;
}
