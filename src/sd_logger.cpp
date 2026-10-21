#include "sd_logger.h"
#include "hardware_config.h"
#include <stdio.h>

SdLogger::SdLogger()
    : _path("temp_log.csv")
{
}

bool SdLogger::begin()
{
    if (!SD.begin(Pins::SD_CS))
    {
        return false;
    }

    if (SD.exists(_path))
    {
        SD.remove(_path);
    }

    File f = SD.open(_path, FILE_WRITE);
    if (!f)
    {
        return false;
    }

    f.println("Time_s,S1_Temp_C,S1_Rate_C/s,S2_Temp_C,S2_Rate_C/s,S3_Temp_C,S3_Rate_C/s");
    f.close();
    return true;
}

void SdLogger::append(const SensorFrame &frame)
{
    File f = SD.open(_path, O_APPEND);
    if (!f)
    {
        return;
    }

    int len = snprintf(_lineBuf, sizeof(_lineBuf), "%.3f", frame.timestampMs / 1000.0f);
    for (int i = 0; i < NUM_CHANNELS && len < (int)sizeof(_lineBuf); i++)
    {
        len += snprintf(_lineBuf + len, sizeof(_lineBuf) - len, ",%.2f,%.3f",
                         frame.temperatureC[i], frame.coolingRateCs[i]);
    }

    f.println(_lineBuf);
    f.close();
}
