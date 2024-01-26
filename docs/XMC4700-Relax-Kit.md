# Overview
This pages summarizes information about the XMC4700 Relax Kit evaluation board and its implementation for the Arduino IDE. The XMC4700 Relax Kit board consists of a XMC4700 microcontroller with a debugger implemented by a XMC4200 microcontroller. The Infineon homepage of the board can be found [here](https://www.infineon.com/cms/en/product/evaluation-boards/KIT_XMC47_RELAX_5V_AD_V1/productType.html?productType=5546d46250cc1fdf0150f6a27dbf6e8a).
Please note that there exist versions with 5 V and 3.3V. Please be careful which version you have and use with your respective shields. The one described here means the 5 V version as this one is compatible with Arduino shields designed for the 5 V systems.

# Arduino Pin Out
The pin layout of the XMC4700 Relax Kit (for 5V Shields) for the Arduino IDE is as follows (the original file can be found [here](https://github.com/Infineon/Assets/blob/version-2.x/Pictures/XMC%204700_RelaxKit_5VShields_PO_v2.png)):

## Pin Out

![XMC4700 Relax Kit (for 5V Shields) Pin Out for Arduino](https://github.com/Infineon/Assets/blob/version-2.x/Pictures/XMC%204700_RelaxKit_5VShields_PO_v2.png)

## Important Note

Please note that **Arduino pin number 15 & 21 (SCL & A5)** and **Arduino pin number 14 & 20 (SDA & A4)** are **connected** with each other on the board itself. 
Although they are different physical pins of the microcontroller, they are connected with each other on the board to comply with the original Arduino UNO Rev3 pin connections. This influences analog measurements on A4 and A5 if you are using I2C simultaneously.
Details of the connection can also be found in the schematics in the user manual of the board [here](https://www.infineon.com/dgdl/Infineon-Board_User_Manual_XMC4700_XMC4800_Relax_Kit_Series-UM-v01_02-EN.pdf?fileId=5546d46250cc1fdf01513f8e052d07fc).

The [User Manual](https://www.infineon.com/dgdl/Infineon-Board_User_Manual_XMC4700_XMC4800_Relax_Kit_Series-UM-v01_02-EN.pdf?fileId=5546d46250cc1fdf01513f8e052d07fc) on 
- Page 11 details the 3V3 signals on connectors X1 and X2 (figure 7) including ADC channels
- Page 12 below Figure 8 details analog input specifications

See also another Wiki for notes on [XMC4xxx Series Analog pins](https://github.com/techpaul/XMC-for-Arduino/wiki/XMC4xxx-Series-Analog-pins "XMC4xxx series analogue pin WARNINGS")

A workaround is to set the I2C pins to output open drain via `pinMode(<pinNumber>, OUTPUT_OPENDRAIN);` and writing a HIGH afterwards via `digitalWrite(<pinNumber>, HIGH);` to turn it off if you want to use the analog pins (but then I2C cannot be used anymore). Tri-state via `pinMode(<pinNumber>, XMC_GPIO_MODE_INPUT_TRISTATE);` is also possible, but the open drain method is preferable as explained [here](https://github.com/Infineon/XMC-for-Arduino/issues/164#issuecomment-714804397) for some use cases. These functions are using the pin mode definitions from the XMC Peripheral Library defined [here](https://github.com/Infineon/XMC-for-Arduino/blob/0dcbd5822cb59d12a7bdae776d307fae9c607ed7/cores/xmc_lib/XMCLib/inc/xmc4_gpio.h#L206).

You can also cut the physical connection on the board itself (blue routes on the back side of the PCB) as indicated here:

![XMC4700 Cut Copper Analog](https://user-images.githubusercontent.com/20902096/96850978-c2edb280-1457-11eb-9636-b4e8c7b0f725.JPG)

# Key Features
* XMC4700-F144 Microcontroller based on ARM® Cortex®-M4 @ 144MHz, 2MB Flash and 352KB RAM
* On-Board Debugger
* Power over USB
* ESD and reverse current protection
* 2 x user button and 2 x user LED
* Arduino hardware compatible 3.3V and 5.0 V pinout (depending on the version)

# PCB Design Data
In case you want to change the design or reuse it for your own projects, please find the XMC4700 Relax Kit board design for EAGLE under the following link:

[XMC4700 Relax Kit PCB Design Data](https://www.infineon.com/dgdl/Infineon-PCB+Footprints+and+Symbols+-+XMC4700-XMC4800+-+Source+Eagle+-+Relax+Kit+Series-PCB-v01_00-EN.zip?fileId=5546d46250cc1fdf015139c2d2f32016)

# Board Information, Datasheet and Additional Information
A PDF summarizing the features and layout of the XMC4700 Relax Kit board is stored on the Infineon homepage [here](https://www.infineon.com/dgdl/Infineon-Board_User_Manual_XMC4700_XMC4800_Relax_Kit_Series-UM-v01_02-EN.pdf?fileId=5546d46250cc1fdf01513f8e052d07fc).
The datasheet for the XMC4700 can be found here [XMC4700 Datasheet](https://www.infineon.com/dgdl/Infineon-XMC4700-XMC4800-DS-v01_00-EN.pdf?fileId=5546d462518ffd850151908ea8db00b3) while the respective reference manual is located here [XMC4700 Reference Manual](https://www.infineon.com/dgdl/Infineon-ReferenceManual_XMC4700_XMC4800-UM-v01_03-EN.pdf?fileId=5546d462518ffd850151904eb90c0044).

