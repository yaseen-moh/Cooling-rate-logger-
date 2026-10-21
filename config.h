
#ifndef CCRL_CONFIG_H
#define CCRL_CONFIG_H

// Hardware Pin Config


/*
#define SPI_SCK_PIN  13
#define SPI_MISO_PIN 12
#define SPI_MOSI_PIN 11
*/

// MAX31856 Chip Select Pins
#define SENSOR_1_CS_PIN 10
#define SENSOR_2_CS_PIN 9
#define SENSOR_3_CS_PIN 8

// Sampling Configuration
#define SAMPLE_RATE_HZ 1        // (1 Hz)
#define BAUD_RATE 9600

// Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_MOSI 11
#define OLED_CLK 13
#define OLED_DC 5
#define OLED_CS 6
#define OLED_RESET 4

//SD
#define SD_CS_PIN 7



#endif //CCRL_CONFIG_H