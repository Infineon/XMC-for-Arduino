On 64 bit Windows 10 it has been reported that the XMCFlasher does not always work out of the box. Also can fail on 32 bit systems that some other software creates a Program Files (x86) folder, use the same fix.

See Issue [=104 on Infineon/XMC-for-Arduino](https://github.com/Infineon/XMC-for-Arduino/issues/104#issuecomment-530547204)

# Configuration
* Windows 10, 64bit
* Arduino 1.8.9
* Segger Jlink V650
* XMC1100 Boot Kit

## The most common error 
> [Error] Infineon.DebuggerExceptions: It seems that JLink software is not installed please download from www.segger.com and install it. You can specify it by setting java property xmcFlasher.JLink.dllPath

Similar encounters by others https://www.infineonforums.com/threads/5697-XMC-Flasher-is-not-working

If you are using the standalone XMCFlasher then you will be getting an error like this
> XMCFlasher cant find ''JLinkARM.dll''

### Solution
##### XMCFlasher
For standalone XMCFlasher modify the xmcFlasher.bat as follows

 > java -DxmcFlasher.JLink.dllPath="C:\Program Files (x86)\SEGGER\JLink_V650\JLinkARM.dll" -jar %~dp0\xmcflasher.jar %* --gui



The flasher will starts in GUI mode

Select SEGGER in XMCFlasher instead of default DAP link and connect

#### Arduino IDE

For Arduino IDE set an environment value for your Windows account:

> JAVA_TOOL_OPTIONS: "-DxmcFlasher.JLink.dllPath=C:\Program Files (x86)\SEGGER\JLink_V650\JLinkARM.dll"

Arduino Debug will give an report:

> Picked up environment var ... JAVA_TOOL_OPTIONS = "-DxmcFlasher.JLink.dllPath=C:\Program Files etc

The problem appears to be in the Segger software installation.

