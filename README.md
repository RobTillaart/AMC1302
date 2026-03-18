
[![Arduino CI](https://github.com/RobTillaart/AMC1302/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AMC1302/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AMC1302/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AMC1302/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AMC1302/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AMC1302.svg)](https://github.com/RobTillaart/AMC1302/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AMC1302/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AMC1302.svg?maxAge=3600)](https://github.com/RobTillaart/AMC1302/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AMC1302.svg)](https://registry.platformio.org/libraries/robtillaart/AMC1302)


# AMC1302

Arduino library for AMC1302 current sensor and compatibles.


## Description

**Experimental, work in progress**

This library is to read a current with the AMC1302 sensor.

The library is not tested with hardware yet - feedback welcome.

The working is based upon a differential voltage over a defined shunt.
For the differential voltage 2 ADC measurements are made called N and P.
The calculation for DC is done with Ohm's law, current = (Vp - Vn) / shunt.
For AC the calculation is more work.

The AMC1302 has a build in GAIN of 41, so it is used to measure small
voltage differences. E.g. an input voltage of 0.1 Volt becomes 4.1 volt.

The AMC1302 is internally opto-isolated so the processor is protected 
against sudden fluctuations. (read datasheet for details).

The library has the following six classes, code wise the only difference
is the gain. Be sure to use the correct class. 
For gain error and gain drift check the datasheet.

|  device    |  gain  |  error  |  drift       |
|:----------:|:------:|:-------:|:------------:|
|  AMC1200   |   8.0  |  ±0.5%  |  ±50 ppm/°C  |
|  AMC1300   |   8.2  |  ±1.0%  |  ±50 ppm/°C  |
|  AMC1300B  |   8.2  |  ±0.3%  |  ±30 ppm/°C  |
|  AMC1301   |   8.2  |  ±0.3%  |  ±50 ppm/°C  |
|  AMC1302   |  41.0  |  ±0.2%  |  ±35 ppm/°C  |
|  AMC1311   |   1.0  |  ±1.0%  |  ±30 ppm/°C  |
|  AMC1311B  |   1.0  |  ±0.2%  |  ±40 ppm/°C  |
|  AMC1351   |   0.4  |  ±0.2%  |  ±35 ppm/°C  |

As the gain error is on the order 1 in 1000, it makes little sense to use
an ADC with e.g. more than 12 bit. 

The library does not support external ADCs yet.

The library is not tested with hardware yet.

Feedback as always is welcome,


### Special characters

Ω == Ohm = ALT-234 (Windows)  
µ == micro = ALT-0181 (Windows)


### Compatibles

Derived classes exist for the following devices 
- AMC1200
- AMC1300
- AMC1301
- AMC1311
- AMC1351

There exists AMC1304, AMC1305, AMC1306 AMC1336, but these are not compatible.

If you know more compatible devices, please let me know.


### Related

- https://github.com/RobTillaart/ACS712 - current library for ACS7xx series.
- https://github.com/RobTillaart/AMC1302 - this library
- https://github.com/RobTillaart/INA226 - current and voltage sensor
- https://github.com/RobTillaart/TRAFO - voltage sensor for 110/230V
- https://github.com/RobTillaart/printHelpers - for scientific format et al.


### Tested

TODO: 
- Test on Arduino UNO and ESP32
- get hardware


## Interface

```cpp
#include "AMC1302.h"
```

### Constructor

- **AMC1302(uint8_t outNpin, uint8_t outPpin)** defines the internal
analog pins connected to outN and outP of the AMC1302.
- **bool begin(float voltsPerStep, float shunt = 50e-3)**
  - volts per step of the ADC e.g. 5.0/1023  (10 bits 5 volt ADC)
  - shunt = e.g. 50 mΩ = 50e-3 (or 0.050)
- **float calibrateVoltsPerStep(float current)** optional function to 
calibrate the begin() function one can measure an exact current with a 
calibrated device (DMM).
This function adjusts and returns the voltsPerStep parameter based upon 
given shunt and the **current** parameter which should not be 0 (zero).
The value is returned so it can be used for the begin() function.
Note begin() has to be called to initialize shunt and first order volts
per step.


### Frequency Measurements

Must be done before AC measurements can be done. Otherwise the AC
measurements assume a frequency of 50 Hz.
The detectFrequency() blocks depending on the parameter used.
If you want to monitor the frequency around 50 Hz, set the minimal
Frequency to e.g. 45.

- **float detectFrequency(float minimalFrequency = 40)** blocking.
- **void setMicrosAdjust(float factor = 1.000)** adjust timing 
for frequency detection. (optional).
- **float getMicrosAdjust()** idem.


### AC Measurements

AC measurements block for at least one cycle, so for 60 Hz this is 17 ms,
for 50 Hz it is 20 ms.

- **float mA_peak2peak(uint16_t cycles = 1)** measure the peak 
to peak voltage for AC. More cycles makes it more accurate but takes more time.
- **float mA_AC(uint16_t cycles = 1)** measures the current-RMS
by applying a known the crust / FormFactor of the wave.
See section below.
- **float mA_AC_sampling(uint16_t cycles = 1)** measures the current-RMS
by summing the squares of the amplitudes of one period.
This is to be used for voltages with unknown FormFactor.


### Form Factor

- **void setFormFactor(float formFactor = AMC_FF_SINUS)** sets the FormFactor 
for mA_AC() function.
- **float getFormFactor()** returns set value.


### DC Measurements

- **float mA_DC(uint16_t cycles = 1)** reads outN and outP 
and calculates the current.
More cycles makes it more accurate but takes more time.
- **float readVoltageN()** reads the voltage at N (before shunt).
- **float readVoltageP()** reads the voltage at P (after shunt).


### Debugging

- **uint32_t getMinimum()** raw minimum
- **uint32_t getMaximum()** raw maximum.
- **int32_t rawDifference()** raw differential.
Can also be used for own conversion service.
- **float readVoltageN()** read voltage at outN.
- **float readVoltageP()** read voltage at outP.
- **float getGain()** returns hard coded gain. Differs per device type.
Gain cannot be set.
- **int16_t getLastError()** placeholder for error handling.


## Future

#### Must

- improve documentation
- get hardware
- test with hardware

#### Should

- investigate calibration
  - need hardware
- remove unneeded functions

#### Could

- can other data be derived from this AMC1302?
- add examples (from ACS712?)
- investigate support external ADC (see TRAFO / ACS712)
  - need two of them.
- create unit tests if possible
- add error handling
  - out of range

#### Wont

- float getPower(volts) { return volts x getCurrent)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


