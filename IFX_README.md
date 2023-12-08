[![Build Status](https://travis-ci.org/Infineon/XMC-for-Arduino.svg?branch=master)](https://travis-ci.org/Infineon/XMC-for-Arduino)
# Infineon's XMC Microcontroller Boards for Arduino

## Local test (**ON WINDOWS**):

### Clone the repository in arduino folder
- Open Arduino and install any Infineon XMC library (e.g. 2.2.0)
- Open the library location in Arduino program folder

`C:\Users\USERNAME\AppData\Local\Arduino15\packages\Infineon\hardware\xmc`

- Open git bash, type command:

`git clone "HTTP_SSH_REPOSITORY" "LIBRARY_VERSION (e.g. 2.2.0)"`

### Add JLink path to flasher (quick fix)
- Open `tools/xmc-flasher.py`
- Change line 14
`jlinkexe = 'JLINK_EXE_PATH (e.g. C:/Program Files/SEGGER/JLink/JLink.exe)'`

Refer to the main README for the rest of the usage.