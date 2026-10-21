# Cooling Rate Logger — state-machine build

Same hardware, same job as the original 3-point thermal monitor: read three
K-type thermocouples through MAX31856 amplifiers, derive cooling rate per
channel, show it live on an SSD1309 OLED, and optionally log it to SD.

This version is a ground-up rewrite of the firmware architecture, not a
rename of the original files.

### Hardware
- Arduino Uno R3
- 3× Adafruit MAX31856 + K-type thermocouples
- SSD1309 OLED (SPI)
- microSD over SPI (optional logging)

### What's different from a typical class-per-sensor layout
- **One `SensorArray` class owns all three channels** and hands back a
  single `SensorFrame` per sample, instead of the caller looping over three
  separate sensor objects.
- **Cooling-rate math lives in its own `RateTracker` class**, decoupled from
  the SPI/thermocouple driver, so the derivative logic can change without
  touching sensor code.
- **Struct-of-arrays `SensorFrame`** (`temperatureC[3]`, `coolingRateCs[3]`,
  `valid[3]`) instead of an array of per-channel structs.
- **Non-blocking state machine** in `loop()` — `IDLE → ACQUIRE → RENDER →
  PERSIST` — instead of a single `if (elapsed) { do everything }` block.
- **`constexpr` namespaces** (`Pins::`, `Timing::`, `Screen::`) in place of
  flat `#define` macros.
- **Display and SD lines are built with `snprintf` into a buffer**, then
  written once, instead of many chained `.print()` calls.

### Build
```
pio run
pio run -t upload
```

### Layout
```
src/
  hardware_config.h   pin + timing constants
  types.h              SensorFrame, Phase enum
  rate_tracker.{h,cpp} per-channel dT/dt
  sensor_array.{h,cpp} owns all 3 MAX31856 channels
  display_view.{h,cpp} OLED rendering
  sd_logger.{h,cpp}    CSV logging (opt-in)
  main.cpp             state machine + setup/loop
```
