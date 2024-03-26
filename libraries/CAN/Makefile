FQBN  ?=
PORT  ?=
TESTS ?=

$(info FQBN : $(FQBN))
$(info PORT : $(PORT))


TESTS_CONNECTED=-DTEST_CAN_CONNECTED 

TESTS_NOT_CONNECTED=-DTEST_CAN
		

CAN_connected: TESTS=-DTEST_CAN -DTEST_CAN_CONNECTED
CAN: TESTS=-DTEST_CAN

CAN_connected CAN: unity flash


# master_baudrate: TESTS=-DMASTER_BAUDRATE
# master_baudrate: PORT=COM18

# slave_baudrate: TESTS=-DSLAVE_BAUDRATE
# master_baudrate: PORT=COM17

# master_baudrate slave_baudrate: unity flash


test_all: TESTS=$(TESTS_CONNECTED) $(TESTS_NOT_CONNECTED)
test_connected: TESTS=$(TESTS_CONNECTED)
test: TESTS=$(TESTS_NOT_CONNECTED)

test_all \
test_connected \
test: unity flash
#test: unity compile


EXAMPLES = CANReceiver CANReceiverCallback 


clean:
	-rm -rf build/*


arduino: clean
	mkdir -p build
# copy library file
# cp -r libraries/CAN/* build 
# find src -name '*.[hc]*' -a \( \! -name 'main*' \) -print -exec cp {} build \;


CANReceiver: arduino
	cp examples/CANReceiver/CANReceiver.ino build/build.ino

CANReceiverCallback: arduino
	cp examples/CANReceiverCallback/CANReceiverCallback.ino build/build.ino	


# master1:
# 	...

# slave1:
# 	...


unity: arduino
	cp -r test/unit/Unity/*.[hc] build
	cp test/unit/src/framework/arduino/Test_*.[hc]* build
	cp test/unit/src/framework/arduino/unity_ifx.cpp build
	cp test/unit/src/framework/arduino/Test_main.ino build/build.ino


# For WSL and Windows :
# download arduino-cli.exe from : https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Windows_64bit.zip
compile:
ifeq ($(FQBN),)
	$(error "Must set variable FQBN in order to be able to compile Arduino sketches !")
else
# CAUTION : only use '=' when assigning values to vars, not '+='
	arduino-cli.exe compile --clean --log --warnings all --fqbn $(FQBN) --build-property "compiler.c.extra_flags=\"-DUNITY_INCLUDE_CONFIG_H=1\"" \
                                    		             --build-property compiler.cpp.extra_flags="$(TESTS)" \
														 --build-property compiler.ar.cmd=arm-none-eabi-gcc-ar \
                            							 --build-property compiler.libraries.ldflags=-lstdc++ \
														 --build-property compiler.arm.cmsis.path="-isystem{compiler.xmclib_include.path}/XMCLib_CAN_v4_3_0/inc -isystem{compiler.xmclib_include.path}/XMCLib/inc -isystem{compiler.dsp_include.path} -isystem{compiler.nn_include.path} -isystem{compiler.cmsis_include.path} -isystem{compiler.xmclib_include.path}/LIBS -isystem{build.variant.path} -isystem{build.variant.config_path}" \
														 --build-property compiler.usb.path="-isystem{runtime.platform.path}/cores/usblib -isystem{runtime.platform.path}/cores/usblib/Common -isystem{runtime.platform.path}/cores/usblib/Class -isystem{runtime.platform.path}/cores/usblib/Class/Common -isystem{runtime.platform.path}/cores/usblib/Class/Device -isystem{runtime.platform.path}/cores/usblib/Core -isystem{runtime.platform.path}/cores/usblib/Core/XMC4000" \
														 build
endif


upload:	
ifeq ($(PORT),)
	$(error "Must set variable PORT (Windows port naming convention, ie COM16) in order to be able to flash Arduino sketches !")
endif
ifeq ($(FQBN),)
	$(error "Must set variable FQBN in order to be able to flash Arduino sketches !")
else
	arduino-cli.exe upload -p $(PORT) --fqbn $(FQBN) build
endif


flash: compile upload


monitor:
ifeq ($(PORT),)
	$(error "Must set variable PORT (Windows port naming convention, ie COM16) in order to be able to flash Arduino sketches !")
endif
ifeq ($(FQBN),)
	$(error "Must set variable FQBN in order to be able to flash Arduino sketches !")
else
	arduino-cli.exe monitor -c baudrate=9600 -p $(PORT) --fqbn $(FQBN)
endif
