# Test Environment

## Develop on Windows
Clone the repository in arduino folder:
- Open Arduino and install any Infineon XMC library (e.g. 2.2.0)
- Open the library location in Arduino program folder
`C:\Users\"USERNAME"\AppData\Local\Arduino15\packages\Infineon\hardware\xmc`
- Open git bash, type command:
`git clone "HTTP_SSH_REPOSITORY" "LIBRARY_VERSION (e.g. 2.2.0)"`

This is a workaround for current local compilation/testing.

## Test on WSL
To be able to use some tools (make, clang, gcc...) easier on Linux, WSL is needed.
Since now we still compile the code with arduino-cli.exe on windows, in order to useLinux commands/ build tools, a symbolic link is created to eunsure the changes are immediately reflected in the other. 
In WSL, you can create a symbolic link pointing to your windows project folder:
`ln -s /mnt/c/Users/<YourUserName>/AppData/Local/Arduino15/packages/Infineon/hardware/xmc /home/<you-wsl-user>/project`

## (legacy) Manual tests
located in `tests/manual`. The application level `.ino` files for testing purposes. 

## Unity tests

Currently, we are using Unity as the testing framework. You can find more information about Unity at [Unity](https://www.throwtheswitch.org/unity).
Please refer to `unity\README.md` for more details.

To run the tests, use the commands example in `Makefile.test`. 

