# Overview
This pages summarizes information about the [XMC H-Bridge Kit 2GO](https://www.infineon.com/cms/de/product/evaluation-boards/h-bridge-kit-2go/) evaluation board and its implementation for the Arduino IDE. XMC H-Bridge Kit 2GO is fully populated with all electronic components equipped with the H-Bridge [IFX9201](https://www.infineon.com/cms/de/product/power/motor-control-ics/intelligent-motor-control-ics/integrated-full-bridge-driver/ifx9201sg/) combined with XMC 1100 Microcontroller  to realize your own DC motor control. It is designed for the control of DC motors or other inductive loads up to 6 A or up to 36 V of supply. The Infineon homepage of the board can be found [here](https://www.infineon.com/cms/de/product/evaluation-boards/h-bridge-kit-2go/).
# Changes
The release V1.4.0 changed the Arduino pin out, for XMC1100 XMC2Go, so later releases will have the Analog pins to match the XMC2Go. Pin out change is: Analog Inputs A0 and A1 have been swapped - 
* A0 is now pin 13
* A1 is now pin 12

# Arduino Pin Out
The pin layout of the XMC H-Bridge 2Go for the Arduino IDE is as follows (the original file can be found [here](https://github.com/Infineon/Assets/blob/master/Pictures/XMC%202Go_H-Bridge_PO.jpg)):

![XMC H-Bridge 2Go Pin Out for Arduino](https://github.com/Infineon/Assets/blob/master/Pictures/XMC%202Go_H-Bridge_PO.jpg)

# Key Features
* XMC1100 (ARM® Cortex™-M0 based)
* On-board J-Link Lite Debugger (implemented with XMC4200)
* Power over USB (Micro USB) or: 
  * 3.3 V pin with direct connection to XMC1100 and IFX9201SG (compare schematics in [Board User Manual](https://www.infineon.com/dgdl/Infineon-H-Bridge_Kit_2Go_UM-UM-v01_01-EN.pdf?fileId=5546d46250cc1fdf015133ee879d3696))
  * 5 V pin with direct connection to 3.3 V Regulator (converting 5V to 3.3 V, Figure 17 in [Board User Manual](https://www.infineon.com/dgdl/Infineon-H-Bridge_Kit_2Go_UM-UM-v01_01-EN.pdf?fileId=5546d46250cc1fdf015133ee879d3696))
* ESD and reverse current protection
* 2 user LEDs
* Pin Header 2x8 Pins suitable for Breadbord
* H-Bridge IFX9201SG
* Reverse polarity protection

# Board Information, Datasheet and Additional Information
A PDF summarizing the features and layout of the H-Bridge Kit 2GO board is stored on the Infineon homepage [here](https://www.infineon.com/dgdl/Infineon-H-Bridge_Kit_2Go_UM-UM-v01_03-EN.pdf?fileId=5546d46250cc1fdf015133ee879d3696).
The datasheet of the H-Bridge IFX9201 can be found [here](https://www.infineon.com/dgdl/Infineon-IFX9201SG-DS-v01_01-EN.pdf?fileId=5546d4624cb7f111014d2e8916795dea) and the homepage of the H-Bridge IC [here](https://www.infineon.com/cms/de/product/power/motor-control-ics/intelligent-motor-control-ics/integrated-full-bridge-driver/ifx9201sg/).

The datasheet for the XMC1100 can be found here [XMC1100 Datasheet](https://www.infineon.com/dgdl/Infineon-xmc1100_AB-DS-v01_08-EN.pdf?fileId=5546d4624a0bf290014a4bdaff9325bd) while the respective reference manual is located here [XMC1100 Reference Manual](https://www.infineon.com/dgdl/Infineon-xmc1100-AA_rm-UM-v01_01-EN.pdf?fileId=5546d46255dd933d0155e31753b077af).

