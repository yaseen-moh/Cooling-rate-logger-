#include <Arduino.h>
#include "temperature_sensor.h"
#include "config.h"
#include "display_manager.h"
#include "data_logger.h"

//Global array of sensor objects

TemperatureSensor sensors[3] = {
    TemperatureSensor(SENSOR_1_CS_PIN),
    TemperatureSensor(SENSOR_2_CS_PIN),
    TemperatureSensor(SENSOR_3_CS_PIN)
};

DisplayManager display;

DataLogger logger;

unsigned long lastReadingTime = 0;

void setup() {

    // Note: communication at for serial, 9600 baud
    Serial.begin(BAUD_RATE);
    delay(1000);

    Serial.println(F("=== Cooling Rate Temperature Logger (Liquid) ==="));
    Serial.println(F("Initializing Display..."));

    if (!display.begin())
    {
        Serial.println(F("ERROR: Failed to start display "));
        Serial.println(F("Check wiring for display and restart"));
        while (1);
    }

    Serial.println(F("Display initialized successfully!")); // will double check, might just print everytime regardless

    //Initialize sensor
    Serial.println(F("Initializing Sensors..."));

    for (int i = 0; i < 3;i++)
    {
        if (!sensors[i].begin())
        {
            Serial.println(F("ERROR: Failed to initialize sensor "));
            Serial.println(i + 1);
            Serial.println();
            Serial.print(F("Check wiring for sensor "));
            Serial.print(i + 1);
            Serial.println(F(" and restart"));
            while (1);
        }
    }
    Serial.println(F("All sensors initialized successfully!"));


    /*
    //SD card logger
    Serial.println(F("Initializing Data Logger..."));

    if (!logger.begin())
    {
        Serial.println(F("ERROR: Failed to initialize data logger!! "));
        Serial.println(F("Check wiring for micro SD and restart"));
        while (1);
    }
    Serial.println(F("Data Logger initialized successfully!"));
    */

}


void loop() {

    //check if 1000 ms passed
    if (millis() - lastReadingTime >= 1000)
    {
        lastReadingTime += 1000; // add exactly 1000ms

        TemperatureReading readings[3];
        for (int i = 0; i < 3; i++)
        {
            readings[i] = sensors[i].readTemperature(lastReadingTime);
        }

        // time print
        Serial.println();
        Serial.print(F("=== Time: "));
        Serial.print(lastReadingTime / 1000.0, 1); // lastReadingTime --> timestamp, temp sensor h & cpp
        Serial.println(F("s ==="));

        for (int i = 0; i < 3; i++)
        {
            if (readings[i].isValid)
            {
                // sensor
                Serial.print(F("Sensor "));
                Serial.print(i + 1);
                Serial.print(F(": "));

                // temp
                Serial.print(F("Temperature: "));
                Serial.print(readings[i].temperature, 2); // 2 dec places
                Serial.print(F(" C | "));

                // cooling rate
                Serial.print(F("Rate: "));
                Serial.print(readings[i].coolingRate, 3);
                Serial.println(F(" C/s"));

            } else
            {
                Serial.println(F("Error: Invalid reading (sensor fault detected) in sensor "));
                Serial.println(i + 1);
            }
        }
        // ---
        // 1 sec before next reading (1 Hz rate)
        // delay(1000);
        // replaced for code at beginning of loop
        // ---

        display.showReadings(readings, 3);
        //logger.writeData(readings,3);
    }
}
