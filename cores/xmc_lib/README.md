# Develop notes
## XMCLib version
The current one is V4.3.0. The macro of XMCLib version is also defined in ```cores\xmc_lib\XMCLib\inc\xmc_common.h```

## CAN macro

Because XMClibs use CAN macro, conflicts with Arduino default CAN class name, so we manually changed XMClib (CAN -> CAN_xmc).
changed files:

.h header files:
- XMCLib\inc\xmc_can.h
- XMCLib\inc\xmc_pau.h
- XMCLib\inc\xmc1_scu.h
- XMCLib\inc\xmc4_scu.h

.c source files:
- XMCLib\src\xmc_can.c
- XMCLib\src\xmc1_scu.c
