

#ifndef CCRL_DATA_STRUCTURES_H
#define CCRL_DATA_STRUCTURES_H

struct TemperatureReading
{
    int sensorID;
    float temperature;
    unsigned long timestamp;
    float coolingRate;
    bool isValid;
};



#endif //CCRL_DATA_STRUCTURES_H