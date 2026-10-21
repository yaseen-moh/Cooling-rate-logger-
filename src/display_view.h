#pragma once

#include <U8g2lib.h>
#include "types.h"

class DisplayView
{
public:
    DisplayView();

    bool begin();
    void render(const SensorFrame &frame);

private:
    U8G2_SSD1309_128X64_NONAME0_1_4W_HW_SPI _panel;
    char _lineBuf[32]; // formatted once per line, then printed
};
