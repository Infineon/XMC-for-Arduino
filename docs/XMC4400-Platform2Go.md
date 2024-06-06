# Overview
This page summarizes information about the XMC4400 Platform 2Go evaluation board and its implementation for the Arduino IDE. The XMC4400 Platform 2Go evaluation board consists of a XMC4400 microcontroller with a debugger implemented by a XMC4200 microcontroller. The Infineon homepage of the board can be found [here](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc_plt2go_xmc4400/).
Please note that there exist versions with 5 V and 3.3V. Please be careful which version you have and use with your respective shields. The one described here means the 5 V version as this one is compatible with Arduino shields designed for the 5 V systems.
This kit has the XMC4400 device with debugger plus ETHERNET, CAN, ARDUINO, MikroBUS and Shields2Go form factor. 
Equipped with an ARM® Cortex®-M4 based XMC™ Microcontroller from Infineon Technologies AG, the XMC4400 Platform2Go is designed to evaluate the capabilities of Infineon’s XMC4400  Microcontroller. It can be used with a wide range of development tools including Infineon’s free of charge Eclipse based IDE DAVE. 

# Arduino Pin Out
The pin layout of the XMC4400 Platform 2Go evaluation board (for 5V Shields) for the Arduino IDE is as follows (the original file can be found [here](https://github.com/Infineon/Assets/blob/version-2.x/Pictures/xmc4400_platform2go_PO_v2.png)):

![XMC4400 Platform 2Go evaluation board (for 5V Shields) Pin Out for Arduino](https://github.com/Infineon/Assets/blob/version-2.x/Pictures/xmc4400_platform2go_PO_v2.png)

## Connected I2S and Analog pin 
Please note that **Arduino pin number 15 & 21 (SCL & A5)** and **Arduino pin number 14 & 20 (SDA & A4)** are **connected** with each other on the board itself. 
Although they are different physical pins of the microcontroller, they are connected with each other on the board to comply with the original Arduino UNO Rev3 pin connections. This influences analog measurements on A4 and A5 if you are using I2C simultaneously.
Details of the connection can also be found in the schematics in the user manual of the board [here](https://www.infineon.com/dgdl/Infineon-XMC4400_Platform2Go-UserManual-v01_00-EN.pdf?fileId=5546d4626f229553016f8fc159482c94).

The [XMC4400 Platform2Go User Manual](https://www.infineon.com/dgdl/Infineon-XMC4400_Platform2Go-UserManual-v01_00-EN.pdf?fileId=5546d4626f229553016f8fc159482c94) on 
- Page 12 details the 3V3 signals on connectors X1 and X2 (Figure 7) including ADC channels
- Page 15 below Figure 9 details analog input specifications

See also another Wiki for notes on [XMC4xxx Series Analog pins](https://github.com/techpaul/XMC-for-Arduino/wiki/XMC4xxx-Series-Analog-pins "XMC4xxx series analogue pin WARNINGS")

A workaround is to set the I2C pins to output open drain via `pinMode(<pinNumber>, OUTPUT_OPENDRAIN);` and writing a HIGH afterwards via `digitalWrite(<pinNumber>, HIGH);` to turn it off if you want to use the analog pins (but then I2C cannot be used anymore). Tri-state via `pinMode(<pinNumber>, XMC_GPIO_MODE_INPUT_TRISTATE);` is also possible, but the open drain method is preferable as explained [here](https://github.com/Infineon/XMC-for-Arduino/issues/164#issuecomment-714804397) for some use cases. These functions are using the pin mode definitions from the XMC Peripheral Library defined [here](https://github.com/Infineon/XMC-for-Arduino/blob/0dcbd5822cb59d12a7bdae776d307fae9c607ed7/cores/xmc_lib/XMCLib/inc/xmc4_gpio.h#L206).

You can also cut the connection to the pins physically by cutting the marked blue routes on the back side of the PCB:

![XMC4400 Cut Lines Board](https://user-images.githubusercontent.com/26908977/96910232-7332d980-149f-11eb-81ec-2b5c23b01372.png)

## CAN Terminal Resistor
R2 needs to be removed if the board is neither start nor end node.

# Key Features
* XMC™4400 (ARM® Cortex™-M4)
* ARDUINO Uno compatibility
* Shields2Go connectivity
* Ethernet-enabled communication option
* Additional voltage level shifters
* Available in four different assembly versions: 3.3V Shields (Lite), 5V (Lite)
* CAN connectivity

# Benefits 
* Highest integration on Microcontrollers
* Easy to design products
* Highest efficiency
* Reduced system cost

# PCB Design Data
In case you want to change the design or reuse it for your own projects, please find the XMC4400 Platform2Go board design for Altium under the following link:

[XMC4400 Platform2Go PCB Design Data](https://www.infineon.com/dgdl/Infineon-XMC4400_Platform2Go-PCBDesignData-v01_00-EN.zip?fileId=5546d46277921c32017795dcd31b4689)

# Board Information, Datasheet and Additional Information
A PDF summarizing the features and layout of the XMC4400 Platform 2Go evaluation board is stored on the Infineon homepage [here](https://www.infineon.com/dgdl/Infineon-XMC4400_Platform2Go-UserManual-v01_00-EN.pdf?fileId=5546d4626f229553016f8fc159482c94).
The datasheet for the XMC4400 can be found here [XMC4400 Datasheet](https://www.infineon.com/dgdl/Infineon-XMC4400-DS-v01_03-EN.pdf?fileId=5546d462696dbf12016981795855391d) while the respective reference manual is located here [XMC4400 Reference Manual](https://www.infineon.com/dgdl/Infineon-xmc4400_rm_v1.6_2016-UM-v01_06-EN.pdf?fileId=db3a30433afc7e3e013b3c46756b5c41).

