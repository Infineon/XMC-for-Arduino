# Infineon's XMC Microcontroller Boards for Arduino

```
Important Information:
Arduino 1.8.0 IDE might have problems with the XMC-for-Arduino releases.
Please update to the newest version.
In case of problems, please open an 'Issue' ticket and we will get in contact with you.

Thank you very much!

Kind regards,

The Infineon Team
```

This repository enables the integration of [Infineon's](https://www.infineon.com/) XMC microcontrollers into the [Arduino IDE](https://www.arduino.cc/en/main/software).

## Supported Microcontroller Boards

* [XMC 2Go](https://www.infineon.com/cms/en/product/evaluation-boards/KIT_XMC_2GO_XMC1100_V1/productType.html?productType=db3a304443537c4e01436ccecb5d154f)
* [XMC1100 Boot Kit](https://www.infineon.com/cms/en/product/evaluation-boards/KIT_XMC11_BOOT_001/productType.html?productType=db3a30443b360d0e013b8f5163c46f62#ispnTab1)
* [XMC4700 Relax Kit](https://www.infineon.com/cms/en/product/evaluation-boards/KIT_XMC47_RELAX_LITE_V1/productType.html?productType=5546d46250cc1fdf0150f6a2788e6e89)

## Additional Information
Please visit also the Wiki for additional information, e.g. datasheets, pin out diagrams, etc.:

[XMC-for-Arduino Wiki](https://github.com/Infineon/XMC-for-Arduino/wiki)

* Page for [XMC 2Go](https://github.com/Infineon/XMC-for-Arduino/wiki/XMC-2Go)
* Page for [XMC1100 Boot Kit](https://github.com/Infineon/XMC-for-Arduino/wiki/XMC1100-Boot-Kit)
* Page for [XMC4700 Relax Kit](https://github.com/Infineon/XMC-for-Arduino/wiki/XMC4700-Relax-Kit)

## Installation Instructions

### Prework for SEGGER J-Link

In order to use and program the Infineon XMC microcontrollers in the Arduino IDE, you need [SEGGER J-Link](https://www.segger.com/downloads/jlink) installed on your PC. Please follow this link to [SEGGER J-Link](https://www.segger.com/downloads/jlink) and install the J-Link Software and Documentation Pack for your operating system.
If you have already installed '[DAVE™ - Development Platform for XMC™ Microcontrollers](https://www.infineon.com/cms/de/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-registered-cortex-registered-m/dave-version-4-free-development-platform-for-code-generation/channel.html?channel=db3a30433580b37101359f8ee6963814)', you can skip this step as the respective drivers/programs are already installed on your system.

![J-Link](https://raw.githubusercontent.com/infineon/assets/master/Pictures/J-Link_Packages.png)

### Integration into the Arduino IDE

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

In the boards list **Tools** > **Board**, the XMC microcontroller boards XMC2Go, XMC1100 Boot Kit, and XMC4700 Relax Kit are added and can be used from now on.

![Board List](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Board_List.png)

### Important Notes

* **This integration will only work for Arduino IDE >=1.5**
* **The XMC1100 Boot Kit has limitations if compared to the official Arduino boards (consult the [XMC-for-Arduino Wiki](https://github.com/Infineon/XMC-for-Arduino/wiki) for more information)**
* **Refer also to the LICENSE.md/txt file for further information**
