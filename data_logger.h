

#ifndef CCRL_DATA_LOGGER_H
#define CCRL_DATA_LOGGER_H

#include <SPI.h>
#include <SD.h>
#include "data_structures.h"


class DataLogger
{

    public:
        DataLogger();
        void writeData(TemperatureReading readings[], int numSensors);
        bool begin();


    private:
        int _csPin;
        const char* _filename;
        bool _headerWritten;


};



#endif //CCRL_DATA_LOGGER_H