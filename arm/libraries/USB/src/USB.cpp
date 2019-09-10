#include "USB.h"

USBClass::USBClass() : clock_configuration(clk_config), baudrate(9600)
{
}
// for different clk configuration
USBClass::USBClass(const XMC_SCU_CLOCK_CONFIG_t _clk_config) : clock_configuration(_clk_config), baudrate(9600)
{
}

void USBClass::begin(void)
{
	this->init(this->baudrate);
	while (USB_DeviceState != DEVICE_STATE_Configured)
	{
	}
	// after this function device state will be configured and ready to use
}
void USBClass::init(uint32_t baudrate)
{
	_rx_buffer = new RingBuffer(USB_RX_BUFFER_SIZE);
	_tx_buffer = new RingBuffer(USB_TX_BUFFER_SIZE);

	// fist setup clock for USB
	this->setupClock();
	// then init usb
	USB_Init(baudrate);
}

void USBClass::begin(uint32_t baudrate)
{

	this->init(baudrate);
	while (USB_DeviceState != DEVICE_STATE_Configured)
	{
	}
	// after this function device state will be configured and ready to use
}

void USBClass::setupClock()
{
	XMC_SCU_CLOCK_Init(&clock_configuration);
	XMC_SCU_CLOCK_EnableUsbPll();
	XMC_SCU_CLOCK_StartUsbPll(2, 64);
	XMC_SCU_CLOCK_SetUsbClockDivider(4);
	XMC_SCU_CLOCK_SetUsbClockSource(XMC_SCU_CLOCK_USBCLKSRC_USBPLL);
	XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_USB);
	SystemCoreClockUpdate();
}

void USBClass::end(void)
{
	USB_Detach();
}

void USBClass::writeToBuffer(const uint8_t uc_data)
{
	_tx_buffer->store_char(uc_data);
}

void USBClass::writeToBuffer(const char uc_data)
{
	_tx_buffer->store_char(uc_data);
}

void USBClass::writeToBuffer(const float val,  uint8_t delimiter)
{
	float_to_bytes.float_val = val;

	for (uint8_t i = 0; i < FLOAT_BYTES; i++)
		_tx_buffer->store_char(float_to_bytes.byte_array[i] + 48);
	_tx_buffer->store_char(delimiter);
}

void USBClass::clearTxBuffer()
{
	// send
	while (_tx_buffer->_iTail != _tx_buffer->_iHead)
	{
		int next = _tx_buffer->_iTail + 1;
		if (next >= USB_TX_BUFFER_SIZE)
			next = 0;
		CDC_Device_SendByte(&VirtualSerial_CDC_Interface, (const uint8_t)_tx_buffer->_aucBuffer[_tx_buffer->_iTail]);
		_tx_buffer->_iTail = next;
	}
}

void USBClass::write(const char *const String)
{
	CDC_Device_SendString(&VirtualSerial_CDC_Interface, String);
}

void USBClass::write(const uint8_t uc_data)
{
	CDC_Device_SendByte(&VirtualSerial_CDC_Interface, uc_data);
}

void USBClass::write(const uint8_t *Buffer, const uint16_t Length)
{
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, (uint8_t *)Buffer, Length);
}

bool USBClass::available()
{
	int head = _rx_buffer->_iHead; // Snapshot index affected by irq
	if (head >= _rx_buffer->_iTail)
		return head - _rx_buffer->_iTail;
	return USB_RX_BUFFER_SIZE - _rx_buffer->_iTail + head;
}

int USBClass::read()
{
	if (_rx_buffer->_iHead == _rx_buffer->_iTail)
		return -1;

	uint8_t uc = _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
	_rx_buffer->_iTail++;
	if (_rx_buffer->_iTail >= USB_RX_BUFFER_SIZE)
		_rx_buffer->_iTail = 0;
	return uc;
}

void USBClass::flush()
{
	CDC_Device_Flush(&VirtualSerial_CDC_Interface);
}

void USBClass::IrqHandler()
{
	XMC_USBD_IRQHandler(&USB_runtime);
	// this function does not need to be run so frequently
	CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
	// receive
	while (CDC_Device_BytesReceived(&VirtualSerial_CDC_Interface))
	{
		_rx_buffer->store_char(CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface));
	}
}

extern "C"
{
	void USB0_0_IRQHandler(void)
	{
		USB.IrqHandler();
	}
}

USBClass USB;