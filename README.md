# Infineon's XMC Microcontroller Boards for Arduino

```
Initial Note: There will be soon changes due to hardware/license/issue/other/your changes,
please regard this kindly as an inital release to integrate our XMC boards into your favorite IDE.
We want you to have the best experience for fair contribution and collaboration here as this is
intended to be part of a community.
In case of problems, please open an 'Issue' ticket and we will get in contact with you.

Thank you very much!

Kind regards,

The Infineon Team
```

This repository contains the integration of [Infineon's](https://www.infineon.com/) XMC microcontrollers into the [Arduino IDE](https://www.arduino.cc/en/main/software).
Supported boards by this repository are listed under 'Microcontroller Boards' in the following section.

## Microcontroller Boards

* [XMC 2Go](https://www.infineon.com/cms/en/product/evaluation-boards/KIT_XMC_2GO_XMC1100_V1/productType.html?productType=db3a304443537c4e01436ccecb5d154f)
* [XMC1100 Boot Kit](https://www.infineon.com/cms/en/product/evaluation-boards/KIT_XMC11_BOOT_001/productType.html?productType=db3a30443b360d0e013b8f5163c46f62#ispnTab1)
* [XMC4700 Relax Kit](https://www.infineon.com/cms/en/product/evaluation-boards/KIT_XMC47_RELAX_LITE_V1/productType.html?productType=5546d46250cc1fdf0150f6a2788e6e89)

## Additional Information
Please visit also the Wiki for additional information, datasheets, pin out diagrams for the evaluation boards as well as links to datasheets, applications notes, and so on. 
You can find the wiki under the following link:

[XMC-for-Arduino Wiki](https://github.com/Infineon/XMC-for-Arduino/wiki)

## Installation Instructions

### Prework for SEGGER J-Link

In order to use the Infineon XMC microcontrollers by this repository and program them, you need [SEGGER J-Link](https://www.segger.com/downloads/jlink) installed on your PC. Please follow this link [SEGGER J-Link](https://www.segger.com/downloads/jlink) and install the J-Link Software and Documentation Pack for your respective operating system (OS).
If you have already installed '[DAVE™ - Development Platform for XMC™ Microcontrollers](https://www.infineon.com/cms/de/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-registered-cortex-registered-m/dave-version-4-free-development-platform-for-code-generation/channel.html?channel=db3a30433580b37101359f8ee6963814)', you might skip this step as you should have the respective drivers on your system.

![J-Link](https://raw.githubusercontent.com/infineon/assets/master/Pictures/J-Link_Packages.png)

### Integration in Arduino IDE

![Preferences](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Preferences.png)

Paste the following URL into the 'Additional Boards Manager URLs' input field under **File** > **Preferences** to add Infineon's microcontroller boards to the Arduino IDE.

https://github.com/Infineon/Assets/releases/download/current/package_infineon_index.json

Nicer to copy (no clickable link):

```
https://github.com/Infineon/Assets/releases/download/current/package_infineon_index.json
```

![Adding a Board JSON](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Preferences_JSON.png)

To install the boards, please go now to **Tools** > **Board** > **Boards Manager...** and search for XMC. You will see options to install the board files for the microcontrollers. Click "Install" to add the boards to your Arduino IDE.

![Infineon Board Entry](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Boards_Manager_Entry.png)

In the boards list **Tools** > **Board**, you will now find the XMC microcontroller boards XMC2Go, XMC1100 Boot Kit, and XMC4700 Relax Kit.

![Board List](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Board_List.png)

### Different Notes

* **Note: This will only work for Arduino IDE >=1.5**
* **Note: XMC1100 Boot Kit has some limitations if compared to the official Arduino boards, additional information will follow**
* **Note: There will be changes due to hardware/license/issue/other problems, please regard this as an inital release**
* **Note: Refer also to the LICENSE.md/txt file for further information**
