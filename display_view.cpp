#include "display_view.h"
#include "hardware_config.h"
#include <stdio.h>

DisplayView::DisplayView()
    : _panel(U8G2_R0, Pins::OLED_CS, Pins::OLED_DC, Pins::OLED_RESET)
{
}

bool DisplayView::begin()
{
    _panel.begin();
    return true;
}

void DisplayView::render(const SensorFrame &frame)
{
    _panel.firstPage();
    do
    {
        _panel.setFont(u8g2_font_6x10_tf);

        snprintf(_lineBuf, sizeof(_lineBuf), "Time: %.1fs", frame.timestampMs / 1000.0f);
        _panel.setCursor(0, 10);
        _panel.print(_lineBuf);

        for (int i = 0; i < NUM_CHANNELS; i++)
        {
            int y = 26 + (i * 13);
            snprintf(_lineBuf, sizeof(_lineBuf), "S%d: %.1fC | %.3fC/s",
                     i + 1, frame.temperatureC[i], frame.coolingRateCs[i]);
            _panel.setCursor(0, y);
            _panel.print(_lineBuf);
        }
    } while (_panel.nextPage());
}
