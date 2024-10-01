# Develop Environment

## Develop on Windows
Clone the repository in arduino folder:
- Open Arduino and install any Infineon XMC library (e.g. 2.2.0)
- Open the library location in Arduino program folder
`C:\Users\"USERNAME"\AppData\Local\Arduino15\packages\Infineon\hardware\xmc`
- Open git bash, type command:
`git clone "HTTP_SSH_REPOSITORY" "LIBRARY_VERSION (e.g. 2.2.0)"`

This is a workaround for current local compilation/testing.

## Develop on WSL
To be able to use some tools (make, clang, gcc...) easier on Linux, WSL is needed.
Since now we still compile the code with arduino-cli.exe on windows, in order to useLinux commands/ build tools, a symbolic link is created to eunsure the changes are immediately reflected in the other. 
In WSL, you can create a symbolic link pointing to your windows project folder:

`ln -s /mnt/c/Users/<YourUserName>/AppData/Local/Arduino15/packages/Infineon/hardware/xmc /home/<you-wsl-user>/project`

# Code checks
Refer to libraries\CAN\Makefile.codecheck

# Example and Unity tests
Refer to libraries\CAN\Makefile.test

XMC4700 Receiver has some issue. 