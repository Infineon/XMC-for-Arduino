Built-in Libraries
==================

The XMC for Arduino platform provides a comprehensive set of built-in libraries that enable developers to easily access 
and utilize the XMC microcontrollers' features and peripherals. This section lists these libraries, including their 
functionality and supported boards.

DeviceControl XMC
^^^^^^^^^^^^^^^^^

Examples Supported
------------------

.. list-table:: 
    :header-rows: 1

    * - Examples
      - Boards
      - Description
    * - DieTemperatureMeasurement
      - | KIT_XMC_2GO_XMC1100_V1 
        | KIT_XMC11_BOOT_001
        | XMC1100 H-Bridge 2GO
        | KIT_XMC13_BOOT_001
        | KIT_XMC14_2GO
        | KIT_XMC1400_ARDUINO
        | KIT_XMC_PLT2GO_XMC4400
        | KIT_XMC47_RELAX_5V_AD_V1
      - | Simple die temperature measurement  
        | for XMC devices which demonstrates 
        | themeasure temperature of die using 
        | sensor.  
    * - HeapMemoryMeasurement
      - | KIT_XMC_2GO_XMC1100_V1 
        | KIT_XMC11_BOOT_001
        | XMC1100 H-Bridge 2GO
        | KIT_XMC13_BOOT_001
        | KIT_XMC14_2GO
        | KIT_XMC1400_ARDUINO
        | KIT_XMC47_RELAX_5V_AD_V1
      - | Simple example to check heap memory 
        | during run time for XMC devices which
        | demonstrates the ability to check on 
        | free heap memory.
    * - SleepModeXMC1100
      - | KIT_XMC_2GO_XMC1100_V1 
        | KIT_XMC11_BOOT_001
        | XMC1100 H-Bridge 2GO
        | KIT_XMC13_BOOT_001
        | KIT_XMC14_2GO
        | KIT_XMC1400_ARDUINO
      - | Demonstrates the use of an alarm to 
        | wake up an xmc1100 from sleep mode.
    * - SleepModeXMC4700
      - | KIT_XMC47_RELAX_5V_AD_V1
      - | Simple Sleep Mode for XMC4700  
        | Relax Kit V1 demonstrates the use of 
        | an alarm to wake up an XMC4700 from  
        | sleep mode. LED2 will blink fast on  
        | active  mode. If CCU4 is ON in sleep 
        | mode,  LED2  will blink slower 
        | (because of slower clock) while 
        | in sleep mode. If CCU is OFF in sleep 
        | mode, LED2 will stop blinking, until 
        | device wakes up.
    * - StackMemoryMeasurement
      - | KIT_XMC_2GO_XMC1100_V1 
        | KIT_XMC11_BOOT_001
        | XMC1100 H-Bridge 2GO
        | KIT_XMC13_BOOT_001
        | KIT_XMC_PLT2GO_XMC4400
        | KIT_XMC47_RELAX_5V_AD_V1
      - | Simple example to check stack memory 
        | during run time for XMC devices which
        | demonstrates the ability to check on 
        | free stack memory

DMA
^^^^^

Examples Supported
-------------------

.. list-table:: 
    :header-rows: 1

    * - Examples
      - Boards
      - Description
    * - DMA_Memory   
      - | KIT_XMC47_RELAX_5V_AD_V1
      - | Demonstrates how to setup an DMA, to transfer
        | data between two places in memory. 
    * - DMA_UART   
      - | KIT_XMC47_RELAX_5V_AD_V1
      - | Demonstrates how to setup an DMA, to transfer
        | data between two places in memory. 



RTC Library
^^^^^^^^^^^

.. list-table:: 
    :header-rows: 1

    * - Examples
      - Boards
      - Description
    * - AlarmRTC
      -  KIT_XMC47_RELAX_5V_AD_V1
      - | Demonstrates how to set an RTC alarm for the 
        | KIT_XMC47_RELAX_5V_AD_V1 V1.
    * - SimpleRTC
      -  KIT_XMC47_RELAX_5V_AD_V1
      -  Demonstrates the use of the RTC library for the XMC4700.


SPI Library
^^^^^^^^^^^

.. list-table:: 
    :header-rows: 1

    * - Examples
      - Boards
      - Description
    * - | SPI_MOSI_to_MISO
        | _SameDevice
      - | KIT_XMC_2GO_XMC1100_V1 
        | KIT_XMC11_BOOT_001
        | XMC1100 H-Bridge 2GO
        | KIT_XMC13_BOOT_001
        | KIT_XMC14_2GO
        | KIT_XMC1400_ARDUINO
        | KIT_XMC_PLT2GO_XMC4400
        | KIT_XMC47_RELAX_5V_AD_V1
      - | SPI example which communicates between the
        | MOSI and MISO pin of the same board. Connect 
        | the MOSI pin to the MOSI pin as hardware 
        | setup.


Wire Library
^^^^^^^^^^^^

.. list-table:: 
    :header-rows: 1

    * - Examples
      - Boards
      - Description
    * - master_reader    
      - | KIT_XMC_2GO_XMC1100_V1 
        | KIT_XMC11_BOOT_001
        | XMC1100 H-Bridge 2GO
        | KIT_XMC13_BOOT_001
        | KIT_XMC14_2GO
        | KIT_XMC1400_ARDUINO
        | KIT_XMC_PLT2GO_XMC4400
        | KIT_XMC47_RELAX_5V_AD_V1
      - | Demonstrates use of the Wire library. Reads data
        | from an I2C/TWI slave device. Refer to the "Wire Slave
        | Sender" example for use with this. Then it
        | communicates using I2C protocol between two
        | supported XMC boards. Connect the SDA and SCL
        | pins of one board to the SDA and SCL pin of the
        | other board.
    * - master_writer 
      - | KIT_XMC_2GO_XMC1100_V1 
        | KIT_XMC11_BOOT_001
        | XMC1100 H-Bridge 2GO
        | KIT_XMC13_BOOT_001
        | KIT_XMC14_2GO
        | KIT_XMC1400_ARDUINO
        | KIT_XMC_PLT2GO_XMC4400
        | KIT_XMC47_RELAX_5V_AD_V1
      - | Demonstrates use of the Wire library. Writes data to
        | an I2C/TWI slave device. Refer to the "Wire Slave
        | Receiver" example for use with this. Then it
        | communicates using I2C protocol between two
        | supported XMC boards. Connect the SDA and SCL
        | pins of one board to the SDA and SCL pin of the
        | other board.
    * - slave_receiver
      - | KIT_XMC_2GO_XMC1100_V1 
        | KIT_XMC11_BOOT_001
        | XMC1100 H-Bridge 2GO
        | KIT_XMC13_BOOT_001
        | KIT_XMC14_2GO
        | KIT_XMC1400_ARDUINO
        | KIT_XMC_PLT2GO_XMC4400
        | KIT_XMC47_RELAX_5V_AD_V1
      - | Demonstrates use of the Wire library. Receives data as
        | an I2C/TWI slave device. Refer to the "Wire Slave
        | Writer" example for use with this. Then it
        | communicates using I2C protocol between two
        | supported XMC boards. Connect the SDA and SCL
        | pins of one board to the SDA and SCL pin of the
        | other board.
    * - slave_sender
      - | KIT_XMC_2GO_XMC1100_V1 
        | KIT_XMC11_BOOT_001
        | XMC1100 H-Bridge 2GO
        | KIT_XMC13_BOOT_001
        | KIT_XMC14_2GO
        | KIT_XMC1400_ARDUINO
        | KIT_XMC_PLT2GO_XMC4400
        | KIT_XMC47_RELAX_5V_AD_V1
      - | Demonstrates use of the Wire library. Receives data as
        | an I2C/TWI slave device. Refer to the "Wire Master
        | Reader" example for use with this. Then it
        | communicates using I2C protocol between two
        | supported XMC boards. Connect the SDA and SCL
        | pins of one board to the SDA and SCL pin of the
        | other board.


I2S Library
^^^^^^^^^^^

This library has been tested with the IM69D130 Microphone Shield2Go with both KIT_XMC47_RELAX_5V_AD_V1 and XMC1100 XMC2Go. 
Please refer to the `README.md <https://github.com/Infineon/XMC-for-Arduino/blob/master/libraries/I2S/README.md>`_ of 
the I2S library for pin connections.

Limitations
-----------
With XMC 2Go (possibly also with other XMC1000 family devices), you might easily overflow the I2S buffer and you should 
try to reduce the I2S sampling rate if so.

OneWire Library
^^^^^^^^^^^^^^^

Library for One wire protocol. It could be used to access 1-wire temperature sensors, memory and other chips.

CAN Library
^^^^^^^^^^^

This library provides support for the CAN protocol. For further details, please refer to the `README.md <https://github.com/Infineon/XMC-for-Arduino/blob/master/libraries/CAN/README.md>`_ file in the CAN library.

.. list-table:: 
    :header-rows: 1

    * - Examples
      - Boards
      - Description
    * - CANSender   
      - XMC1400 2GO 
      - | This example demonstrates how to send a CAN message.
        | It supports two different message/frame formats: 
        | standard and extended. The CAN standard frame uses 
        | an 11-bit identifier, while the CAN extended frame 
        | uses a 29-bit identifier.
    * - | CANReceiver/
        | CANReceiverCallback  
      - XMC1400 2GO 
      - | This example demonstrates how to receive a CAN 
        | message. There are two methods for receiving messages:
        | the default method runs a loop that continuously
        | polls for new messages, while the  callback method
        | registers a callback function that triggers an interrupt
        | when data is received on the CAN bus. In both examples,
        | messages with any ID transmitted on the CAN bus can 
        | be received. Additionally, messages can be filtered for
        | specific IDs  using the ``filter()`` function.
    * - CANLoopBack 
      - XMC1400 2GO 
      - | This example demonstrates the loopback mode of CAN. 
        | In this mode, the CAN transmitter is internally connected 
        | to its receiver, allowing the message to be sent and 
        | received internally without transmission onto the actual 
        | CAN bus.
