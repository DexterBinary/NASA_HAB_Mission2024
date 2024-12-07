<img src="assets/IGA.svg" width=200 align="right">


[![PlatformIO](https://github.com/domino4com/IGA/actions/workflows/platformio.yml/badge.svg)](https://github.com/domino4com/IGA/actions/workflows/platformio.yml)
[![Arduino](https://github.com/domino4com/IGA/actions/workflows/arduino.yml/badge.svg)](https://github.com/domino4com/IGA/actions/workflows/arduino.yml)

# IGA - Input Gas Air Quality
This is a Gas Sensor measuring Total Volatile Organic Compounds and estimating Carbon dioxide (CO₂eq) 
| Specifications | |
| --: | :--: |
| Communication | I²C |
| I²C Address | 0x58 |
| ChipSet | Sensirion SGP30|
| Datasheet | [.pdf](https://sensirion.com/media/documents/984E0DD5/61644B8B/Sensirion_Gas_Sensors_Datasheet_SGP30.pdf) |
| Suggested Arduino Library | [GitHub](https://github.com/sparkfun/SparkFun_SGP30_Arduino_Library) |
| Suggested MicroPython Library | [GitHub](https://github.com/adafruit/Adafruit_CircuitPython_SGP30)|
| TVOC Accuracy | 1 ppb |
| TVOC Range | 0 to 60000 ppb|
| CO₂eq Accuracy | 1 ppm |
| CO₂eq Range | 400 to 60000 ppm |

## Supported I²C Modes
- [x] 100 kbit/s Standard Mode SM
- [x] 400 kbit/s Fast Mode	FM
- [ ] 1 Mbit/s Fast Mode Plus	FM+
- [ ] 3.4Mbit/s High Speed Mode	HS
- [ ] 5 Mbit/s Ultra Fast Mode	UFM

# License: 
<img src="assets/CC-BY-NC-SA.svg" width=200 align="right">
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International Public License

[View License Deed](https://creativecommons.org/licenses/by-nc-sa/4.0/) | [View Legal Code](https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode)
