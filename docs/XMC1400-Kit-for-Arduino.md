# Overview
This pages summarizes information about the XMC1400 Kit for Arduino evaluation board and its implementation for the Arduino IDE. The XMC1400 Kit for Arduino board consists of a XMC1400 microcontroller with a debugger implemented by a XMC4200 microcontroller. The Infineon homepage of the board can be found [here](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc1400_arduino/).

# Arduino Pin Out
The pin layout of the XMC1400 Kit for Arduino for the Arduino IDE is as follows (the original file can be found [here](https://github.com/Infineon/Assets/blob/version-2.x/Pictures/XMC%201400_KitforArduino_PO_v2.png)).

## Important Note

Please note that pins **P1.4** and **P0.5** are **swapped** on the board and are not consistent with the silkscreen. As a result, interrupt 0 (INT0) occurs at **Arduino pin 3** and inerrupt 1 (INT1) is located at **Arduino pin 25**. 

This is different from the original Arduino UNO Rev3 implementation. Please look at the pinout diagram above for more information. 



## Pin Out

![XMC1400 Kit for Arduino Pin Out for Arduino](https://github.com/Infineon/Assets/blob/version-2.x/Pictures/XMC%201400_KitforArduino_PO_v2.png)

# Key Features
* XMC1400 Microcontroller (ARM® Cortex™-M0 based) in TSSOP-38 with 64 KB Flash and full peripheral set of XMC1400 series
* Detachable Segger J-Link (implemented with XMC4200)
* Board shape & power supply for Arduino shields: [Shield List](http://shieldlist.org).
* [Infineon shields](https://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-registered-cortex-tm-m/xmc-development-tools-kits-and-boards/boards-and-shields-for-arduino/channel.html?channel=5546d4614b0b239c014ba1e6c4a73098) - Hardware compatible with Arduino


# Board Information, Datasheet and Additional Information
A PDF summarizing the features and layout of the XMC1400 Kit for Arduino board is stored on the Infineon homepage [here](https://www.infineon.com/dgdl/Infineon-XMC1400_ArduinoKit-UserManual-v02_00-EN.pdf?fileId=5546d4626cb27db2016d48e4c7051906).
The datasheet for the XMC1400 can be found here [XMC1400 Datasheet](https://www.infineon.com/dgdl/Infineon-XMC1400-DataSheet-v01_04-EN.pdf?fileId=5546d46250cc1fdf015110a2596343b2) while the respective reference manual is located here [XMC1400 Reference Manual](https://www.infineon.com/dgdl/Infineon-XMC1400-AA_ReferenceManual-UM-v01_01-EN.pdf?fileId=5546d46250cc1fdf0150f6ebc29a7109).

