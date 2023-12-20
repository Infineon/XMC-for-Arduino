### Examples Supported

| Example          | XMC1400 2GO test | Description |
| -----------                | -----------        |------------
|  DieTemperatureMeasurement       &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; | PASS (serial delay)  |Simple die temperature measurement for XMC devices which demonstrates the measure temperature of die using sensor. |
| HeapMemoryMeasurement | PASS (serial delay)  | Simple example to check heap memory during run time for XMC devices which demonstrates the ability to check on free heap memory. |
|SleepModeXMC1100 | PASS  | Demonstrates the use of an alarm to wake up an xmc1100 from sleep mode. |
|SleepModeXMC4700 | N/A | Simple Sleep Mode for XMC4700 Relax Kit V1 demonstrates the use of an alarm to wake up an XMC4700 from sleep mode.LED2 will blink fast on active mode. If CCU4 is ON in sleep mode, LED2 will blink slower (because of slower clock) while in sleep mode.If CCU is OFF in sleep mode, LED2 will stop blinking, until device wakes up.
|StackMemoryMeasurement | FAIL: linker file variable name changed| Simple example to check stack memory during run time for XMC devices which demonstrates the ability to check on free stack memory

## DMA

### Examples Supported
| Example          | XMC1400 2GO test  | Description |
| ---------            | -----------     | --------------
| DMA_Memory &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;| N/A &nbsp;  &nbsp;     | Demonstrates how to setup an DMA, to transfer data between two places in memory.|
|DMA_UART                         | N/A | Demonstrates how to setup an DMA, to transfer data between two places in memory.|


## RTC Library
| Example          | XMC1400 2GO test  | Description |
| -----------    | -----------        |------------
|AlarmRTC     &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  |  N/A   &nbsp;  &nbsp;|  Demonstrates how to set an RTC alarm for the XMC4700 Relax Kit V1|
|SimpleRTC | N/A |  Demonstrates the use of the RTC library for the XMC4700|

## SPI Library
| Example          | XMC1400 2GO test  | Description |
| -----------    | -----------        |------------
|SPI_MOSI_to_MISO_SameDevice &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp; &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;   | PASS (serial problem same as XMC1100 2Go) | SPI example which communicates between the MOSI and MISO pin of the same board. Connect the MOSI pin to the MOSI pin as hardware setup.|

## Wire Library
Test with TLV493 1A6: PASS

| Example          | XMC1400 2GO test | Description |
| -----------    | -----------        |------------
| master_reader &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp; &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp; &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  &nbsp;  |  | Demonstrates use of the Wire library. Reads data from an I2C/TWI slave device. Refer to the "Wire Slave Sender" example for use with this.Then it communicates using I2C protocol between two supported XMC boards. Connect the SDA and SCL pins of one board to the SDA and SCL pin of the other board.
| master_writer | | Demonstrates use of the Wire library.Writes data to an I2C/TWI slave device. Refer to the "Wire Slave Receiver" example for use with this.Then it communicates using I2C protocol between two supported XMC boards. Connect the SDA and SCL pins of one board to the SDA and SCL pin of the other board.
| slave_receiver |  | Demonstrates use of the Wire library. Receives data as an I2C/TWI slave device. Refer to the "Wire Master Writer" example for use with this.Then it communicates using I2C protocol between two supported XMC boards. Connect the SDA and SCL pins of one board to the SDA and SCL pin of the other board.
| slave_sender |  | Demonstrates use of the Wire library. Sends data as an I2C/TWI slave device. Refer to the "Wire Master Reader" example for use with this.Then it communicates using I2C protocol between two supported XMC boards. Connect the SDA and SCL pins of one board to the SDA and SCL pin of the other board.

## I2S Library
FAIL!! NEED to go deep in I2S library

## OneWire Library


