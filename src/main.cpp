#include <Arduino.h>
#include "hardware_config.h"
#include "types.h"
#include "sensor_array.h"
#include "display_view.h"
#include "sd_logger.h"

SensorArray sensors;
DisplayView view;
SdLogger logger;

SensorFrame frame;
Phase phase = Phase::BOOT;
unsigned long nextTick = 0;

static void haltWith(const __FlashStringHelper* msg)
{
    Serial.println(msg);
    while (true)
    {
        // intentional lockup - mirrors the original firmware's fail-stop behavior
    }
}

static void logFrameToSerial(const SensorFrame &f)
{
    Serial.println();
    Serial.print(F("=== t="));
    Serial.print(f.timestampMs / 1000.0f, 1);
    Serial.println(F("s ==="));

    for (int i = 0; i < NUM_CHANNELS; i++)
    {
        if (f.valid[i])
        {
            Serial.print(F("Ch"));
            Serial.print(i + 1);
            Serial.print(F(": "));
            Serial.print(f.temperatureC[i], 2);
            Serial.print(F("C  rate="));
            Serial.print(f.coolingRateCs[i], 3);
            Serial.println(F("C/s"));
        }
        else
        {
            Serial.print(F("Ch"));
            Serial.print(i + 1);
            Serial.println(F(": fault"));
        }
    }
}

void setup()
{
    Serial.begin(SerialPort::BAUD_RATE);
    delay(1000);

    Serial.println(F("=== Liquid Cooling Rate Logger (state-machine build) ==="));

    if (!view.begin())
    {
        haltWith(F("Display init failed - check wiring and restart."));
    }

    if (!sensors.begin())
    {
        haltWith(F("Sensor init failed - check thermocouple wiring and restart."));
    }

    Serial.println(F("Sensors and display ready."));

    // SD logging stays opt-in, same as the original build.
    // if (!logger.begin()) { haltWith(F("SD init failed.")); }

    nextTick = millis();
    phase = Phase::IDLE;
}

void loop()
{
    unsigned long now = millis();

    switch (phase)
    {
        case Phase::IDLE:
            if (now - nextTick >= Timing::SAMPLE_PERIOD_MS)
            {
                nextTick += Timing::SAMPLE_PERIOD_MS; // fixed cadence, not drift-prone
                phase = Phase::ACQUIRE;
            }
            break;

        case Phase::ACQUIRE:
            sensors.readAll(nextTick, frame);
            logFrameToSerial(frame);
            phase = Phase::RENDER;
            break;

        case Phase::RENDER:
            view.render(frame);
            phase = Phase::PERSIST;
            break;

        case Phase::PERSIST:
            // logger.append(frame); // enable once SD wiring is confirmed
            phase = Phase::IDLE;
            break;

        case Phase::BOOT:
        default:
            phase = Phase::IDLE;
            break;
    }
}
