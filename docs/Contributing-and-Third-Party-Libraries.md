# XMC-for-Arduino
## Contributing to XMC-for-Arduino Project
First important point **All Contributions** are welcomed.

Please contribute and raise issues via the [github repository](https://github.com/Infineon/XMC-for-Arduino/tree/develop) 

Check the **develop** branch for any Beta releases fixes for any issues you may find. 

## Developer notes

### General points on repository branches and flow

1. _master_ branch is intended to be copy of release version
2. Please make Pull Requests to _develop_ branch for review, inclusion and availability for others
3. At next release _develop_ is merged into _master_ for release
4. Other branches are for other tests and not to be treated as anything but work in progress for now
5. Check [XMC-for-Arduino Wiki](https://github.com/Infineon/XMC-for-Arduino/wiki) for any additional information

### Local Running using Arduino IDE (**ON WINDOWS**):
Clone the repository in arduino folder:
- Open Arduino and install any Infineon XMC library (e.g. 2.2.0)
- Open the library location in Arduino program folder
`C:\Users\"USERNAME"\AppData\Local\Arduino15\packages\Infineon\hardware\xmc`
- Open git bash, type command:
`git clone "HTTP_SSH_REPOSITORY" "LIBRARY_VERSION (e.g. 2.2.0)"`

This is a workaround for current local compilation/testing.

### CICD

Currently github workflow is used for automaticaly build test and release. Workflows are defined by YAML file in the `.github/workflows` directory. 
To merge your PR, please try to add a git tag in the format `VX.Y.Z` (e.g. V3.3.0) to trigger the release process in your fork and pass the compilation tests.

### WIKI
Because of the limitations of the github wiki, it is difficult to create PR for changes of wiki. Please refer to the answer under: https://stackoverflow.com/questions/10642928/how-can-i-make-a-pull-request-for-a-wiki-page-on-github and create a ticket for your modifications.

### Debug
New Arduino IDE(v2.3.2) support debug. Refer to https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-debugger for more details.

No hardware setup is required since the XMC eval board has Jlink on-board debugger, You can jump directly to the:
https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-debugger/#getting-to-know-the-debugger


If you encounter strange behavior with Arduino IDE, try cleaning up the cache

windows: `C:\User\"username"\AppData\Roaming\arduino-ide`
linux: `~/.config/arduino-ide`
macos: `~/Library/Application Support/arduino-ide/`

## Creating and Maintaining Third Party Libraries
### Background
The Arduino IDE allows for external libraries to be added to support devices and functions
not in the core setup. For details on creating libraries see the 
[Arduino Library Specifications](https://arduino.github.io/arduino-cli/library-specification/)
### XMC-for-Arduino Configuration
In order that a library, that is specific to one architecture or board type is only 
compiled when a supporting board is setup, this specification has a setting for the 
*architecture* the library will work on. The *library.properties* file *architecture* 
setting is shortly going to be changed from a confusing *arm* name to a less confusing 
name of *xmc*, to avoid any confusions for those using multiple boards and architectures 
for third party libraries compatibility.
### XMC-for-Arduino Architecture Settings to use
Currently third party and other external libraries use the *library.properties* 
*architecture* setting to define which board architecture the library is compiled for
The XMC-for-Arduino **current** setting for **up to V1.50** is -
~~~
architecture=arm
~~~

When creating or maintaining third party or external libraries please use *library.properties* 
*architecture* setting for versions **V1.5.0 and above** -
~~~
architecture=xmc,arm
~~~
The Arduino IDE on compilation will work out which one to use automatically, avoiding any strange updating issues.
At a later stage to be announced, it will be recommended to change to
~~~
architecture=xmc
~~~
As all newer versions will be using architecture *xmc*.

If your library ALSO supports other boards and architectures, obviously leave those in as well.

Check [XMC-for-Arduino Wiki](https://github.com/Infineon/XMC-for-Arduino/wiki) for any additional information.