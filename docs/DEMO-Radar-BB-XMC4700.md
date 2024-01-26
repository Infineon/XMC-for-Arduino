# Overview
This pages summarizes information about the DEMO Radar BB XMC4700 board and its implementation for the Arduino IDE. The DEMO Radar BB XMC4700 board consists of a XMC4700 microcontroller with a debugger implemented by a XMC4200 microcontroller. The Infineon homepage of the board can be found [here](https://www.infineon.com/cms/en/product/evaluation-boards/demo-sense2gol-pulse/).
Please note that there exist versions with 5 V and 3.3V. Please be careful which version you have and use with your respective shields. The one described here means the 5 V version as this one is compatible with Arduino shields designed for the 5 V systems.

# Arduino Pin Out
The pin layout of the XMC4700 for the Arduino IDE is as follows (the original file can be found [here](https://github.com/Infineon/Assets/blob/master/Pictures/Radar%20Baseboard%20XMC4700_PO.png)):

![DEMO Radar BB XMC4700 Pin Out for Arduino](https://github.com/Infineon/Assets/blob/master/Pictures/Radar%20Baseboard%20XMC4700_PO.png)

# Key Features
* XMC4700-E196 Microcontroller based on ARM® Cortex®-M4 @ 144MHz, 2MB Flash and 352KB RAM
* On-Board Debugger
* Power over USB
* ESD and reverse current protection
* 1 x user button and 1 x user LED with 3 channels (RGB)
* Arduino hardware compatible 3.3V and 5.0 V pinout (depending on the version)

# Using the DEMO Radar BB XMC4700 in Arduino
There are some things to note and modifications to make when using the Demo Radar BB XMC4700 **V1.0** in Arduino.

## I2C
If I2C communication is intended to be used as the interface to the target Arduino shield, remove the following resistors: R70, R71, R73, R74, R77 and R80.

![I2C Resistors](https://github.com/Infineon/Assets/blob/master/Pictures/rbb_i2c_resistors.png)

## Selection of IOREF
XMC4700 operates on the 3.3V domain. Depending on the target Arduino shield, the IOREF can be configured as 5V or 3.3V via a jumper on P2 (see diagram below).
To select 3.3V as IOREF, short pins 1 and 2 of P2.
To select 5V as IOREF, short pins 2 and 3 of P2.

![IOREF Jumper](https://github.com/Infineon/Assets/blob/master/Pictures/rbb_ioref_jumper.png)

## ISCP Header
In case connection via the ISCP header is required to the target Arduino shield, do not use the pins from header P7. Instead, connect the pins via jumper wires from the SPI pins on header P3.

![ISCP Header](https://github.com/Infineon/Assets/blob/master/Pictures/rbb_iscp_header.png)

# PCB Design Data
In case you want to change the design or reuse it for your own projects, please find the Radar Baseboard XMC4700 board design for Altium Designer under the following link:

[DEMO Radar BB XMC4700 PCB Design Data](https://www.infineon.com/cms/en/product/evaluation-boards/demo-sense2gol-pulse/#!tools)

# Board Information, Datasheet and Additional Information
A PDF summarizing the features and layout of the DEMO Radar BB XMC4700 board is stored on the Infineon homepage [here](https://www.infineon.com/dgdl/Infineon-AN602%20Radar%20Baseboard%20XMC4700-ApplicationNotes-v01_00-EN.pdf?fileId=5546d4626e651a41016e82b63d8a1574).
The datasheet for the XMC4700 can be found here [XMC4700 Datasheet](https://www.infineon.com/dgdl/Infineon-XMC4700-XMC4800-DS-v01_00-EN.pdf?fileId=5546d462518ffd850151908ea8db00b3) while the respective reference manual is located here [XMC4700 Reference Manual](https://www.infineon.com/dgdl/Infineon-ReferenceManual_XMC4700_XMC4800-UM-v01_03-EN.pdf?fileId=5546d462518ffd850151904eb90c0044).

