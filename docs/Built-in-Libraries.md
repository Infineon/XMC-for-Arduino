## Documentation
Documentation of the Built-in libraries is to be found on [this page](https://github.com/Infineon/InfineonDoxyGenerator).

## DeviceControlXMC

### Examples Supported

| Example          | Boards  | Description |
| -----------                | -----------        |------------
|  DieTemperatureMeasurement       &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; |  <ul><li>XMC1100 XMC 2GO</li> <li>XMC1100 Boot Kit</li> <li>XMC1100 H-Bridge 2GO</li> <li>XMC1300 Boot Kit</li> <li>XMC4400 Platform 2Go</li>  <li>XMC4700 Relax Kit</li></ul> |Simple die temperature measurement for XMC devices which demonstrates the measure temperature of die using sensor. |
| HeapMemoryMeasurement | <ul><li>XMC1100 XMC 2GO</li> <li>XMC1100 Boot Kit</li> <li>XMC1100 H-Bridge 2GO</li> <li>XMC1300 Boot Kit</li>  <li>XMC4700 Relax Kit</li></ul> | Simple example to check heap memory during run time for XMC devices which demonstrates the ability to check on free heap memory. |
|SleepModeXMC1100 | <ul><li>XMC1100 XMC 2GO</li> <li>XMC1100 Boot Kit</li> <li>XMC1100 H-Bridge 2GO</li> <li>XMC1300 Boot Kit</li>  | Demonstrates the use of an alarm to wake up an xmc1100 from sleep mode. |
|SleepModeXMC4700 |  <ul><li>XMC4700 Relax Kit</li>  | Simple Sleep Mode for XMC4700 Relax Kit V1 demonstrates the use of an alarm to wake up an XMC4700 from sleep mode.LED2 will blink fast on active mode. If CCU4 is ON in sleep mode, LED2 will blink slower (because of slower clock) while in sleep mode.If CCU is OFF in sleep mode, LED2 will stop blinking, until device wakes up.
|StackMemoryMeasurement | <ul><li>XMC1100 XMC 2GO</li> <li>XMC1100 Boot Kit</li> <li>XMC1100 H-Bridge 2GO</li> <li>XMC1300 Boot Kit</li> <li>XMC4400 Platform 2Go</li>  <li>XMC4700 Relax Kit</li></ul>| Simple example to check stack memory during run time for XMC devices which demonstrates the ability to check on free stack memory

## DMA

### Examples Supported
| Example          | Boards  | Description |
| ---------            | -----------     | --------------
| DMA_Memory &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;| <ul><li>XMC4700 Relax Kit</li> &nbsp;  &nbsp;     | Demonstrates how to setup an DMA, to transfer data between two places in memory.|
|DMA_UART                         | <ul><li>XMC4700 Relax Kit</li> | Demonstrates how to setup an DMA, to transfer data between two places in memory.|


## RTC Library
| Example          | Boards  | Description |
| -----------    | -----------        |------------
|AlarmRTC     &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  |  <ul><li>XMC4700 Relax Kit</li>   &nbsp;  &nbsp;|  Demonstrates how to set an RTC alarm for the XMC4700 Relax Kit V1|
|SimpleRTC | <ul><li>XMC4700 Relax Kit</li> |  Demonstrates the use of the RTC library for the XMC4700|

## SPI Library
| Example          | Boards  | Description |
| -----------    | -----------        |------------
|SPI_MOSI_to_MISO_SameDevice &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp; &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;   |  <ul><li>XMC1100 XMC 2GO</li> <li>XMC1100 Boot Kit</li> <li>XMC1100 H-Bridge 2GO</li> <li>XMC1300 Boot Kit</li> <li>XMC4400 Platform 2Go</li>  <li>XMC4700 Relax Kit</li></ul> | SPI example which communicates between the MOSI and MISO pin of the same board. Connect the MOSI pin to the MOSI pin as hardware setup.|

## Wire Library

| Example          | Boards | Description |
| -----------    | -----------        |------------
| master_reader &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp; &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp; &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  | <ul><li>XMC1100 XMC 2GO</li> <li>XMC1100 Boot Kit</li> <li>XMC1100 H-Bridge 2GO</li> <li>XMC1300 Boot Kit</li> <li>XMC4400 Platform 2Go</li>  <li>XMC4700 Relax Kit</li></ul> | Demonstrates use of the Wire library. Reads data from an I2C/TWI slave device. Refer to the "Wire Slave Sender" example for use with this.Then it communicates using I2C protocol between two supported XMC boards. Connect the SDA and SCL pins of one board to the SDA and SCL pin of the other board.
| master_writer | <ul><li>XMC1100 XMC 2GO</li> <li>XMC1100 Boot Kit</li> <li>XMC1100 H-Bridge 2GO</li> <li>XMC1300 Boot Kit</li> <li>XMC4400 Platform 2Go</li>  <li>XMC4700 Relax Kit</li></ul> | Demonstrates use of the Wire library.Writes data to an I2C/TWI slave device. Refer to the "Wire Slave Receiver" example for use with this.Then it communicates using I2C protocol between two supported XMC boards. Connect the SDA and SCL pins of one board to the SDA and SCL pin of the other board.
| slave_receiver | <ul><li>XMC1100 XMC 2GO</li> <li>XMC1100 Boot Kit</li> <li>XMC1100 H-Bridge 2GO</li> <li>XMC1300 Boot Kit</li> <li>XMC4400 Platform 2Go</li>  <li>XMC4700 Relax Kit</li></ul> | Demonstrates use of the Wire library. Receives data as an I2C/TWI slave device. Refer to the "Wire Master Writer" example for use with this.Then it communicates using I2C protocol between two supported XMC boards. Connect the SDA and SCL pins of one board to the SDA and SCL pin of the other board.
| slave_sender | <ul><li>XMC1100 XMC 2GO</li> <li>XMC1100 Boot Kit</li> <li>XMC1100 H-Bridge 2GO</li> <li>XMC1300 Boot Kit</li> <li>XMC4400 Platform 2Go</li>  <li>XMC4700 Relax Kit</li></ul> | Demonstrates use of the Wire library. Sends data as an I2C/TWI slave device. Refer to the "Wire Master Reader" example for use with this.Then it communicates using I2C protocol between two supported XMC boards. Connect the SDA and SCL pins of one board to the SDA and SCL pin of the other board.

## I2S Library

This library has been tested with the IM69D130 Microphone Shield2Go with both XMC4700 Relax Kit and XMC1100 XMC2Go. Please refer to the [README.md](https://github.com/Infineon/XMC-for-Arduino/blob/master/arm/libraries/I2S/README.md) of the I2S library for pin connections.

### Limitations
With XMC 2Go (possibly also with other XMC1000 family devices), you might easily overflow the I2S buffer and you should try to reduce the I2S sampling rate if so.

## OneWire Library
Library for One wire protocol. It could be used to access 1-wire temperature sensors, memory and other chips.

