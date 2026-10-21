#pragma once

// Grouped by subsystem instead of one flat block of #defines.

namespace Pins
{
    constexpr int SENSOR_1_CS = 10;
    constexpr int SENSOR_2_CS = 9;
    constexpr int SENSOR_3_CS = 8;

    constexpr int OLED_MOSI  = 11;
    constexpr int OLED_CLK   = 13;
    constexpr int OLED_DC    = 5;
    constexpr int OLED_CS    = 6;
    constexpr int OLED_RESET = 4;

    constexpr int SD_CS = 7;
}

namespace Screen
{
    constexpr int WIDTH  = 128;
    constexpr int HEIGHT = 64;
}

namespace Timing
{
    constexpr unsigned long SAMPLE_PERIOD_MS = 1000UL; // 1 Hz
}

namespace SerialPort
{
    constexpr long BAUD_RATE = 9600;
}
