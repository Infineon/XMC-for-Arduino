On 64 bit Linux (ubuntu etc..) it has been reported that the XMCFlasher does not work out of the box.

See Issue [=21 on Infineon/XMC-for-Arduino](https://github.com/Infineon/XMC-for-Arduino/issues/21#issuecomment-397651078)

The suggested fix is to put a symbolic link in so the 32bit application can be found properly as suggested by PabloPL there as follows after installing the Segger software.

`ln -s /opt/SEGGER/JLink/libjlinkarm.so /usr/lib/libjlinkarm.so`

This enables the XMCFlasher to run.

The problem appears to be in the Segger software installation.
