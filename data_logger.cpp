#include "config.h"
#include "data_logger.h"
#include <SD.h>

DataLogger::DataLogger()
    : _csPin(SD_CS_PIN), _filename("temp_log.csv"), _headerWritten(false)
{

}

bool DataLogger::begin()
{
    Serial.print(F("Debug: CS Pin = "));
    Serial.println(_csPin);
    Serial.println(F("Debug: Calling SD.begin()..."));

    if (!SD.begin(_csPin))
    {
        Serial.println(F("Debug: SD.begin() FAILED!"));
        return false;
    }
    Serial.println(F("Debug: SD.begin() SUCCESS!")); // Debug



    if (SD.exists(_filename))
    {
        SD.remove(_filename);
    }

    File file = SD.open(_filename, FILE_WRITE);
    if (!file)
    {
        return false;
    }

    file.println("Time_s,S1_Temp_C,S1_Rate_C/s,S2_Temp_C,S2_Rate_C/s,S3_Temp_C,S3_Rate_C/s");
    _headerWritten = true;

    file.close();

    return true;
}


void DataLogger::writeData(TemperatureReading readings[], int numSensors)
{
    File file = SD.open(_filename, O_APPEND);
    if (!file)
    {
        return;
    }

    file.print(readings[0].timestamp / 1000.0);

    for (int i = 0; i < numSensors; i++)
    {
        file.print(",");
        file.print(readings[i].temperature);
        file.print(",");
        file.print(readings[i].coolingRate);
    }
    file.println();

    file.close();
}