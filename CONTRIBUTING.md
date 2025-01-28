# Contributing to XMC for Arduino
First important point: **All Contributions** are welcomed :open_hands:.

Please contribute and raise issues via the [github repository](https://github.com/Infineon/XMC-for-Arduino/tree/master)

## Overview for Contributors

- Start your contribution by creating a [fork](https://github.com/Infineon/XMC-for-Arduino/fork) of this repository
- It's recommended to create a separate branch for your contribution in your fork
- Once your contribution is ready & tested, please create a [Pull Request](https://github.com/Infineon/XMC-for-Arduino/compare) to the master branch
- Once we merged your changes to the master branch, they are automatically included in the next release

## Development (Linux/ WSL)
1. Create an `<SKETCHBOOK>/hardware/arduino-git` folder. Where `<SKETCHBOOK>` is the location of your Arduino sketchbook. You can run:`mkdir -p $sketchbook/hardware/arduino-git`
1. Change directories: `cd <SKETCHBOOK>/hardware/arduino-git`
1. Clone this repo: `git clone https://github.com/Infineon/XMC-for-Arduino.git xmc`
This allows quick testing of local changes during development.
1. From the root directory of the core, run the setup script : `bash tools/dev-setup.sh`

[!TIP] 
If you encounter strange behavior with Arduino IDE during development, try cleaning up the cache:
* Windows: `C:\User\"username"\AppData\Roaming\arduino-ide`
* Linux: `~/.config/arduino-ide`
* macOS: `~/Library/Application Support/arduino-ide/`

## Automated Build Checks

Currently a Github workflow is used for automatic compilation checking and releasing. Workflows are defined [here](https://github.com/Infineon/XMC-for-Arduino/tree/master/.github/workflows).
Before opening a Pull Request for your contribution, please add a git tag in the format `Vx.y.z` (e.g. V3.3.0) to trigger the release process in your fork and pass the compilation tests.

## Creating and Maintaining Third Party Libraries
### Basics
The Arduino IDE allows for external libraries to be added to support specific devices and functions which are not part of the core setup. For details on creating libraries see the 
[Arduino library specifications](https://arduino.github.io/arduino-cli/library-specification/). If you add additional libraries to this project, make sure to [document them](https://xmc-arduino.readthedocs.io/en/latest/builtin-libraries.html) accordingly.

### XMC-for-Arduino Configuration
To ensure that a library specific to one architecture or board type is only compiled when a supporting board is set up, this specification includes a setting for *architecture* in the *library.properties* file.

When creating or maintaining third party or external libraries for XMC-for-Arduino please use this setting:
~~~
architecture=xmc
~~~

If your library also supports other boards and architectures, add those in as well.

## Validation test
To test the XMC4arduino, we used unity to test some of the features of the arduino core & builtin library. 

Tests are located in tests/arduino-core-tests and included as submodule in this project. Run  `git submodule update --init --recursive` to update them.  If you are nor familiar with submodules, check out: https://git-scm.com/book/en/v2/Git-Tools-Submodules 

## Code checks (WIP)
Refer to libraries\CAN\Makefile.codecheck
* Regarding formatting, we currently use [pre-commit](https://pre-commit.com/) to automatically run clang-formatting to format all c/c++ code. Please install this python package, and follow the quick start (the pre-commit configuration file is already there). You should be able to format your code automatically on git commit!