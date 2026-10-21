

#ifndef CCRL_DISPLAY_MANAGER_H
#define CCRL_DISPLAY_MANAGER_H

#include <U8g2lib.h>
#include "data_structures.h"


class DisplayManager
{
    public:
        DisplayManager();

        bool begin();
        void showReadings(TemperatureReading reading[], int numSensors);
        // maybe have a isDisplayConnected here

    private:
        U8G2_SSD1309_128X64_NONAME0_1_4W_HW_SPI _display;




};



#endif //CCRL_DISPLAY_MANAGER_H