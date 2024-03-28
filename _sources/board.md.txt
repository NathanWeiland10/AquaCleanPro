# Development

For ESP-32 development, it is recommended to use the Arduino IDE ([download here](https://www.arduino.cc/en/software)). All required libraries and board interfaces can be installed through the IDE, however, the GitHub URLs are provided just in case.

## Required Libraries

The required libraries can be found by searching in the Arduino IDE's library manager (Tools > Manage Libraries).

- DS18B20 by Mathias Munk Hansen
    - https://github.com/matmunk/DS18B20
- WiFiManager by tzapu
    - https://github.com/tzapu/WiFiManager
- OneWire
    - https://www.pjrc.com/teensy/td_libs_OneWire.html
- HTTPClient by Adrian McEwan
    - https://github.com/amcewen/HttpClient

## Board Configuration

The board interface can be installed through the Arduino IDE's board manager (Tools > Board > Board Manager). The interface that works with our specific board was _DOIT ESP32 DEVKIT V1_ in the "[esp32 by Espressif Systems](https://github.com/espressif/arduino-esp32)" package.