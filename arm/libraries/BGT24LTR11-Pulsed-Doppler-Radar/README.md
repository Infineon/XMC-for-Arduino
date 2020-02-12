# The Pulsed Doppler Radar library for XMC4700

The Pulsed Doppler Radar library initializes the [XMC4700 Radar Baseboard](https://github.com/Infineon/XMC-for-Arduino/wiki/Radar-Baseboard-XMC4700) firmware to run a pulsed doppler algorithm with the BGT24LTR11 Shield.
This then enables the user to develop compelling applications such as motion detection, presence sensing, speed and direction detection.
To help you get started quickly, example sketches are provided as part of this library:
1) Radar_Pulsed_Doppler_LED: This sketch changes the color of the on-board LEDs to indicate the detection and direction of motion.
2) RadarPulsedDoppler_Andee_RGB: This sketch projects the results of radar processing (i.e. speed, direction) onto a smart device (e.g.handphone/tablet) via Bluetooth, and at the same time uses an external RGB LED to indicate motion and direction of motion.

Scroll down to the Example Sketches section to find out more!

For a deeper understanding of the firmware and algorithm, please refer to:
[S2GLP Software User Manual](https://www.infineon.com/dgdl/Infineon-S2GL_Application_Note_AN597-ApplicationNotes-v01_00-EN.pdf?fileId=5546d4626b2d8e69016b89403b9342aa)

## Using the Pulsed Doppler Radar Library
-----------------------------------------
To use the Pulsed Doppler Radar library in Arduino sketch, it has to be added first via **Sketch** --> **Include Library** --> **IFXRadarPulsedDoppler**.

![Select Library](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_select_library.png)

Next, declare a Radar Pulsed Doppler object.

![Declare Object](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_declare_object.png)

Next, some steps are required to initialize the hardware for the Pulsed Doppler Radar and also to configure the parameters. All these are to be done within the setup() routine.

![Radar Init](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_radar_init.png)

The lines of code will initialize the software to use the default parameters. In case custom parameters are preferred, the user can call the respective APIs (as listed in the following table) before calling the begin() function.

| Configuration APIs                              | Description                                                                                 |
| ----------------------------------------------- | ------------------------------------------------------------------------------------------- |
| uint8_t setMinSpeed(float speedMs);             | Set minimum speed that will be detected                                                     |
| float getMinSpeed(void);                        | Retrieve the minimum speed configured                                                       |
| uint8_t setMaxSpeed(float speedMs);             | Set maximum speed that will be detected                                                     |
| float getMaxSpeed(void);                        | Retrieve the maximum speed configured                                                       |
| uint8_t setMotionSensitivity(float threshold);  | Set threshold that will determine motion or not                                             |
| float getMotionSensitivity(void);               | Retrieve threshold that will determine motion or not                                        |
| uint8_t setDopplerSensitivity(float threshold); | Set threshold that will determine motion with direction (departing/approaching) or not      |
| float getDopplerSensitivity(void);              | Retrieve threshold that will determine motion with direction (departing/approaching) or not |
| uint8_t setFramePeriod(uint8_t periodUs);       | Set frame period in usec                                                                    |
| uint8_t getFramePeriod(void);                   | Retrieve configured frame period in usec                                                    |
| uint8_t setSampleFreq(uint32_t frequencyHz);    | Set ADC sampling frequency in Hz                                                            |
| uint32_t getSampleFreq(void);                   | Retrieve ADC sampling frequency in Hz                                                       |
| uint8_t setSkipSamples(uint32_t numSamples);    | Set the number of samples to skip at beginning of frame                                     |
| uint32_t getSkipSamples(void);                  | Retrieve the number of samples to skip at beginning of frame                                |
| uint8_t setNumSamples(uint32_t numSamples);     | Set size of raw IQ ADC buffer                                                               |
| uint32_t getNumSamples(void);                   | Retrieve configured size of raw IQ ADC buffer                                               |
| uint8_t setPulseWidth(uint32_t widthUs);        | Set the pulse width in usec                                                                 |
| uint32_t getPulseWidth(void);                   | Retrieve the configured pulse width in usec                                                 |
| uint32_t getMinFramePeriod(void);               | Get the minimum frame period in usec                                                        |

Next, define the callback function to perform application tasks upon completion of a round of radar processing, for example to turn on or off an LED. 
In the example shown in the following figure, different LED colors are used to indicate different radar processing results. 

![Callback Function](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_callback_function.png)

The following table lists the APIs that can be called to retrieve the result of the radar processing.

| Result APIs                   | Description                                                 |
| ----------------------------- | ----------------------------------------------------------- |
| bool targetAvailable(void);   | Returns true: motion (with no direction), false: no motion  |
| float getDopplerLevel(void);  | Retrieve the Doppler level of the detected target           |
| float getDopplerFreqHz(void); | Retrieve the Doppler frequency of the detected target       |
| float getVelocity(void);      | Retrieve the signed velocity value                          |
| uint8_t getDirection(void);   | Returns 0:no direction, 1:departing, 2:approaching          |
| float getSpeed(void);         | Retrieve the unsigned speed value                           |
| uint32_t getFrameCount(void); | Retrieve the frame count of result                          |

Finally, add the run() API in the loop() routine to run the radar processing.

![Radar Run](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_radar_run.png)

The following table lists the available control APIs for the Pulsed Doppler Radar library.

| Control APIs                                      | Description                                                                                    |
| ------------------------------------------------- | ---------------------------------------------------------------------------------------------- |
| void initHW(void);                                | To initialize hardware for Pulsed Doppler radar                                                |
| void registerResultCallback(void(*callBackPtr));  | To register function to be called when radar process is done                                   |
| void registerErrorCallback(void(*callBackPtr));   | To register function to be called in case of error                                             |
| void begin(void);                                 | To initialize software parameters for Pulsed Doppler radar                                     |
| void end(void);                                   | To stop radar processing. Usually called during runtime before reconfiguring radar parameters. |
| float getSpeed(void);                             | To run radar processing.                                                                       |

## Example Sketches
-------------------
Two Arduino sketch examples are provided in the current library release. These examples can be accessed from **File** --> **Examples** --> **IFXRadarPulsedDoppler**.

![See Examples](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_see_examples.png)

### Example 1: Radar_Pulsed_Doppler_LED
This example sketch runs the Pulsed Doppler firmware and uses the on-board LED to indicate detection of motion and direction of motion.

**Hardware required:**
Radar Baseboard XMC4700 and BGT24LTR11 Shield

**Steps:**
1.	In Arduino IDE, navigate to **File** --> **Examples** --> **IFXRadarPulsedDoppler** --> **Radar_Pulsed_Doppler_LED**

![Example1 Sketch](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_example1_sketch.png)

2.	Navigate to **Tools** --> **Board** --> **XMC4700 Radar Baseboard** to select the Radar Baseboard as the target kit.

![Select Radar Baseboard](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_select_radar_baseboard.png)

3.	Compile the sketch by clicking the **Verify** button. A success message will be displayed on compilation completion.

![Arduino Verify](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_arduino_verify.png)

![Done Compiling](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_done_compiling.png)

4.	Attach the BGT24LTR11 Shield to the Radar Baseboard XMC4700 via the SAMTEC connectors.

![Connecting Boards](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_connecting_boards.png)

5.	Connect the Radar Baseboard XMC4700 to the PC via a USB cable onto the **Debug** USB port.

![Debug Port](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_debug_port.png)

6.	Upload the code onto the board by clicking the **Upload** button.

![Arduino Upload](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_arduino_upload.png)

The application can now be tested. Make some movement in front of the radar board and observe the LED colors depending on the motion and its direction.

![Radar LED](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_radar_led.png)

The following table lists the programmed behavior of the on-board LED.

| LED Color  | Type of Motion                      |
| ---------- | ----------------------------------- |
| Off        | No motion                           |
| Red        | Departing                           |
| Green      | Approaching                         |
| Blue       | Motion with no meaningful direction |


### Example 2: RadarPulsedDoppler_Andee_RGB
This example sketch runs the Pulsed Doppler firmware and projects the results of radar processing onto a smart device (e.g. handphone/tablet) via Bluetooth, 
and at the same time uses an external RGB LED to indicate motion and direction of motion.

**Hardware required:**
1) Radar Baseboard XMC4700 and BGT24LTR11 Shield
2) Annikken Andee U Shield (https://www.annikken.com/andee-u)
3) RGB LED Lighting Shield with XMC1202 (https://www.infineon.com/cms/en/product/evaluation-boards/kit_led_xmc1202_as_01/)

**Steps:**
1.	In Arduino IDE, navigate to **File** --> **Examples** --> **IFXRadarPulsedDoppler** --> **RadarPulsedDoppler_Andee_RGB**

![Example2 Sketch](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_example2_sketch.png)

2.	Navigate to **Tools** --> **Board** --> **XMC4700 Radar Baseboard** to select the Radar Baseboard as the target kit.

![Select Radar Baseboard](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_select_radar_baseboard.png)

3.	Compile the sketch by clicking the **Verify** button. A success message will be displayed on compilation completion.

![Arduino Verify](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_arduino_verify.png)

![Done Compiling](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_done_compiling.png)

4.	Attach the BGT24LTR11 Shield to the Radar Baseboard XMC4700 via the SAMTEC connectors.

![Connecting Boards](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_connecting_boards.png)

5.	Stack the RGB LED Lighting Shield with XMC1202 onto the Radar Baseboard XMC4700 via the Arduino stack headers. 
Also connect an RGB LED and a 24 VDC power adapter to the RGB LED Lighting Shield. **Do not turn the power on yet!** 
For more information on setting up of the RGB LED Lighting Shield, please refer to [Infineon RGB LED Lighting Shield with XMC1202 for Arduino - User Manual](https://www.infineon.com/dgdl/Infineon-Board_Manual_-_XMC1202_-_RGB_LED_Lighting_Shield_with_XMC1202_for_Arduino_-_v1_0-UM-v01_00-EN.pdf?fileId=5546d46249be182c0149ccca3860734d).

![RGB LED Shield Setup](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_RGB_LED_Shield_Setup.png)

6.	Stack the Annikken Andee U shield onto the setup. Notice that there are several jumper wires on the Annikken Andee U board. 
This is due to the hardware modifications required on the Radar Baseboard regarding the ISCP header as mentioned in [the XMC4700 Radar Baseboard Wiki](https://github.com/Infineon/XMC-for-Arduino/wiki/Radar-Baseboard-XMC4700). 
The second diagram below illustrates the required connections.

![Annikken Andee U](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_Annikken_Andee_U.png)

![Andee Jumpers](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_Andee_Jumpers.png)

7.	Turn on the 24 VDC power supply to the RGB LED Lighting Shield and connect the Radar Baseboard XMC4700 to the PC via a USB cable onto the **Debug** USB port.

![Debug Port](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_debug_port.png)

8.	Upload the code onto the board by clicking the **Upload** button.

![Arduino Upload](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_arduino_upload.png)

The RGB LED should turn on with white light, while the on-board LED will cycle between red, green and blue light to show radar processing is taking place. The application can now be tested.

![Pulsed Doppler Andee RGB](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_PulsedDoppler_Andee_RGB.png)

9.	Launch the Andee app (can be installed for free from the Apple App Store or Google Play Store) on your smart device. In the app, click **Scan for Devices**.

![Andee Scan Devices](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_Andee-Scan_Device.png)

10.	Click **Tjuefire**. When prompted, click **Connect**.

![Andee Connect Device](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_Andee-Connect_Device.png)

11.	Upon successful connection, the GUI should appear on the app. 

![Andee GUI](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_Andee-GUI.png)

In case this does not happen, disconnect from the app, press the reset button on the Radar Baseboard XMC4700 and retry the connection.

Make some movement in front of the radar board and observe the measured speed and detected direction on the GUI. You may also observe the light from the RGB LED changing with regards to the motion and its direction.

The following table lists the programmed behavior of the RGB LED connected to the RGB LED Lighting Shield.

| LED Color      | Type of Motion                                |
| -------------- | --------------------------------------------- |
| Dims down      | Departing                                     |
| Brightens      | Approaching                                   |
| Changes color  | Motion with speed above pre-defined threshold |

The pre-defined fast speed threshold can be changed within the Arduino sketch.

![Predefined Threshold](https://raw.githubusercontent.com/infineon/assets/master/Pictures/rbb_Predefined_Threshold.png)

## Additional Information
See also our [Wiki](https://github.com/Infineon/XMC-for-Arduino/wiki/Core-Libraries) and doxygen-generated [documentation page](https://github.com/Infineon/InfineonDoxyGenerator).

## Authors
Muhammad Nur Syafii Bin Mohamed Saat