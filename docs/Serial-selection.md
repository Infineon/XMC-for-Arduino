## Serial Output Selection

On the XMC boards, two kinds of serial outputs are possible, namely:

* `SERIAL DEBUG (via PC)`
* `SERIAL ONBOARD`


If these two outputs share the same instance of the internal USIC channel, only one of the two could be used at a given time. The selection can be made via the `Tools` menu as shown in the picture below. 

![Serial selection](https://github.com/Infineon/Assets/blob/version-2.x/Pictures/serial_selection.png)

This is generally the case for most of the XMC boards. However, for boards such as the [XMC4200 Platform2Go](https://github.com/Infineon/XMC-for-Arduino/wiki/XMC4200-Platform2Go) and the [XMC4700 Relax Kit](https://github.com/Infineon/XMC-for-Arduino/wiki/XMC4700-Relax-Kit), both the serial output modes are simultaneously active and neednot be selected or enabled from the menu.  

*Note: Please note that the sketch must be recompiled when a different serial output is selected.*

#### For advanced users

The build flag `-DSERIAL_HOSTPC` must be used for the serial output interface via PC and the build flag `-DSERIAL_ONBOARD` must be used for serial output through the onboard TX and RX pins.