
[![Arduino CI](https://github.com/RobTillaart/AMC1302/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AMC1302/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AMC1302/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AMC1302/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AMC1302/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AMC1302.svg)](https://github.com/RobTillaart/AMC1302/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AMC1302/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AMC1302.svg?maxAge=3600)](https://github.com/RobTillaart/AMC1302/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AMC1302.svg)](https://registry.platformio.org/libraries/robtillaart/AMC1302)


# AMC1302

Arduino library for AMC1302 current sensor.


## Description

**Experimental**

This library is to use AMC1302 current sensor


### Special characters

Ω == Ohm = ALT-234 (Windows)
µ == micro = ALT-0181 (Windows)



### Related

- https://github.com/RobTillaart/AMC1302
- https://github.com/RobTillaart/INA226
- https://github.com/RobTillaart/printHelpers


### Tested

TODO: 
- Test on Arduino UNO and ESP32
- get hardware


## Interface

```cpp
#include "AMC1302.h"
```

### Constructor

- **AMC1302(uint8_t outNpin, uint8_t outPpin)** defines the
analog pins connected to outN and outP of the AMC1302.
- **bool begin(float voltsPerStep, float shunt = 50e-3)**
  - volts per step of the ADC e.g. 5.0/1023
  - shunt = e.g. 50 mΩ = 50e-3 (or 0.050)

### Measurements

- **float readCurrent()** reads outN and outP and calculates
the current.
- **float readVoltage()** ???

### Misc

- **int32_t readDiff()** raw differential for debugging.
- **int16_t getLastError()** placeholder for error handling.

//  GET/SET GAIN to calibrate => float gain?

## Future

#### Must

- improve documentation
- get hardware to test
- almost everything.

#### Should

- add error handling
  - out of range
- double read analog ADC ignore first flag in readCurrent?


#### Could

- float getPower(volts) { return volts x getCurrent)
- create unit tests if possible


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


