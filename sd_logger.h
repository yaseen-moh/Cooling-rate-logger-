#pragma once

#include <SD.h>
#include "types.h"

class SdLogger
{
public:
    SdLogger();

    bool begin();
    void append(const SensorFrame &frame);

private:
    const char* _path;
    char _lineBuf[96]; // one CSV row built in memory, then written in one shot
};
