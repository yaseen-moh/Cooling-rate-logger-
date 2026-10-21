
#include "display_manager.h"
#include "config.h"

// #include <SPI.h> // U8G2 library (4W_HW_SPI mode) handles SPI internally


DisplayManager::DisplayManager()
    : _display(U8G2_R0, OLED_CS, OLED_DC, OLED_RESET)

{

}

bool DisplayManager::begin()
{
    _display.begin();
    return true;
}

void DisplayManager::showReadings(TemperatureReading reading[], int numSensors)
{
    _display.firstPage();
    do
    {
        // Set font (small font)
        _display.setFont(u8g2_font_6x10_tf);

        // time
        _display.setCursor(0, 10);
        _display.print("Time: ");
        _display.print(reading[0].timestamp / 1000.0, 1);
        _display.print("s");

        for (int i = 0; i < numSensors; i++)
        {
            int y = 26 + (i * 13);

            _display.setCursor(0, y);

            _display.print("S");
            _display.print(i + 1);
            _display.print(": ");
            _display.print(reading[i].temperature, 1); // 1 dec
            _display.print("C");
            _display.print(" | ");
            _display.print(reading[i].coolingRate, 3);
            _display.print("C/s");

        }

    } while (_display.nextPage());
}
