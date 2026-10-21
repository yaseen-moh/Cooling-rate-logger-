#pragma once

#include <stdint.h>

constexpr int NUM_CHANNELS = 3;

// Struct-of-arrays instead of an array of per-reading structs.
// One frame = one sample across all channels at one timestamp.
struct SensorFrame
{
    unsigned long timestampMs;
    float temperatureC[NUM_CHANNELS];
    float coolingRateCs[NUM_CHANNELS];
    bool  valid[NUM_CHANNELS];
};

enum class Phase : uint8_t
{
    BOOT,
    IDLE,
    ACQUIRE,
    RENDER,
    PERSIST
};
