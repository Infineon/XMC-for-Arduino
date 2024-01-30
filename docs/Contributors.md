# XMC-for-Arduino
## Contributing to XMC-for-Arduino Project
First important point **All Contributions** are welcomed.

Please contribute and raise issues via the [github repository](https://github.com/Infineon/XMC-for-Arduino/tree/develop) 

Check the **develop** branch for any Beta releases fixes for any issues you may find. 

## Developer notes

General points on repository branches and flow

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