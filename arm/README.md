[![Build Status](https://travis-ci.org/Infineon/XMC-for-Arduino.svg?branch=master)](https://travis-ci.org/Infineon/XMC-for-Arduino)
# Infineon's XMC Microcontroller Boards for Arduino

This repository integrates [Infineon's](https://www.infineon.com/) XMC microcontrollers into the [Arduino IDE](https://www.arduino.cc/en/main/software) and [PlatformIO IDE](https://platformio.org/platformio-ide?utm_source=github&utm_medium=xmc-for-arduino).

## Contents
- [Supported Microcontroller Boards](#supported-microcontroller-boards)
- [Additional Information](#additional-information)
- [Installation Instructions](#installation-instructions)
  * [Prework for SEGGER J-Link](#prework-for-segger-j-link)
  * [Using Arduino IDE](#using-arduino-ide)
  * [Using PlatformIO IDE](#using-platformio-ide)
- [Additional Contributors](#additional-contributors)

## Supported Microcontroller Boards

* [XMC1100 XMC 2Go](https://www.infineon.com/cms/en/product/evaluation-boards/KIT_XMC_2GO_XMC1100_V1/productType.html?productType=db3a304443537c4e01436ccecb5d154f)
* [XMC1100 H-Bridge 2Go](https://www.infineon.com/cms/de/product/evaluation-boards/h-bridge-kit-2go/)
* [XMC1100 Boot Kit](https://www.infineon.com/cms/en/product/evaluation-boards/KIT_XMC11_BOOT_001/productType.html?productType=db3a30443b360d0e013b8f5163c46f62#ispnTab1)
* [XMC1300 Boot Kit](https://www.infineon.com/cms/de/product/evaluation-boards/kit_xmc13_boot_001/)
* [XMC1300 Sense2GoL](https://www.infineon.com/cms/de/product/evaluation-boards/demo-sense2gol/)
* [XMC4700 Relax Kit](https://www.infineon.com/cms/en/product/evaluation-boards/KIT_XMC47_RELAX_LITE_V1/productType.html?productType=5546d46250cc1fdf0150f6a2788e6e89)

## Additional Information

Please visit also the Wiki for additional information, e.g. datasheets, pin out diagrams, etc.:

[XMC-for-Arduino Wiki](https://github.com/Infineon/XMC-for-Arduino/wiki)

* Page for [XMC1100 XMC 2Go](https://github.com/Infineon/XMC-for-Arduino/wiki/XMC-2Go)
* Page for [XMC1100 H-Bridge 2Go](https://github.com/Infineon/XMC-for-Arduino/wiki/XMC1100-H%E2%80%90Bridge-2Go)
* Page for [XMC1100 Boot Kit](https://github.com/Infineon/XMC-for-Arduino/wiki/XMC1100-Boot-Kit)
* Page for [XMC1300 Boot Kit](https://github.com/Infineon/XMC-for-Arduino/wiki/XMC1300-Boot-Kit)
* Page for [XMC1300 Sense2GoL](https://github.com/Infineon/XMC-for-Arduino/wiki/XMC1300-Sense2GoL)
* Page for [XMC4700 Relax Kit](https://github.com/Infineon/XMC-for-Arduino/wiki/XMC4700-Relax-Kit)

Additionally, please consult the [releases](https://github.com/Infineon/XMC-for-Arduino/releases) for information about the changes and new versions.

## Installation Instructions

### Prework for SEGGER J-Link

In order to use and program the Infineon XMC microcontrollers in the Arduino IDE, [SEGGER J-Link](https://www.segger.com/downloads/jlink) must be installed on your PC. Please follow this link to [SEGGER J-Link](https://www.segger.com/downloads/jlink) and install the J-Link Software and Documentation Pack for your operating system.
If you have already installed '[DAVE™ - Development Platform for XMC™ Microcontrollers](https://www.infineon.com/cms/de/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-registered-cortex-registered-m/dave-version-4-free-development-platform-for-code-generation/channel.html?channel=db3a30433580b37101359f8ee6963814)', you can skip this step as the respective drivers/programs are already installed on your system.

![J-Link](https://raw.githubusercontent.com/infineon/assets/master/Pictures/J-Link_Packages.png)

### Using Arduino IDE

![Preferences](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Preferences.png)

Paste the following URL into the 'Additional Boards Manager URLs' input field under **File** > **Preferences** to add Infineon's microcontroller boards to the Arduino IDE.

https://github.com/Infineon/Assets/releases/download/current/package_infineon_index.json

Easier to copy (no clickable link):

```
https://github.com/Infineon/Assets/releases/download/current/package_infineon_index.json
```

![Adding a Board JSON](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Preferences_JSON.png)

To install the boards, please navigate to **Tools** > **Board** > **Boards Manager...** and search for XMC. You will find options to install the board files for the microcontrollers. Click "Install" to add the boards to your Arduino IDE.

![Infineon Board Entry](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Boards_Manager_Entry.png)

In the boards list **Tools** > **Board**, the XMC microcontroller boards are added and can be used from now on.

![Board List](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Board_List.png)

**Important Notes**

* This integration will only work for Arduino IDE >=1.5
* The XMC1100 Boot Kit has limitations if compared to the official Arduino boards (consult the [XMC-for-Arduino Wiki](https://github.com/Infineon/XMC-for-Arduino/wiki) for more information)
* Refer also to the LICENSE.md/txt file for further information
* Arduino 1.8.0 IDE might have problems with the XMC-for-Arduino releases

### Using PlatformIO IDE

- [What is PlatformIO?](http://docs.platformio.org/en/latest/what-is-platformio.html?utm_source=github&utm_medium=xmc-for-arduino)
- [PlatformIO IDE](http://platformio.org/platformio-ide?utm_source=github&utm_medium=xmc-for-arduino)
- [PlatformIO Core (CLI)](http://docs.platformio.org/en/latest/core.html?utm_source=github&utm_medium=xmc-for-arduino) (command line tool)
- [Integration with Cloud and Desktop IDEs](http://docs.platformio.org/en/latest/ide.html?utm_source=github&utm_medium=xmc-for-arduino) -
  Cloud9, Codeanywhere, Eclipse Che (Codenvy), Atom, CLion, Eclipse, Emacs, NetBeans, Qt Creator, Sublime Text, VIM, Visual Studio, and VSCode
- [Project Examples](https://github.com/Infineon/platformio-infineonxmc/tree/master/examples)

## Additional Contributors

* [Paul Carpenter](https://github.com/techpaul)
