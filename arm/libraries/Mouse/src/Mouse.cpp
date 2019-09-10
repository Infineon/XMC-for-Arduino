/*
  Mouse.cpp

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Mouse.h"

//================================================================================
//================================================================================
//	Mouse
int8_t mouse_data[3];
MouseClass::MouseClass(void) : _buttons(0)
{
}

void MouseClass::begin(void)
{
	this->init();
	while (USB_DeviceState != DEVICE_STATE_Configured)
	{
	}
	// after this function device state will be configured and ready to use
}
void MouseClass::init(void)
{
	// fist setup clock for USB
	this->setupClock();
	// then init usb
	USB_Init();

	HID_Device_USBTask(&Generic_HID_Interface, MS_OS_20_DESCRIPTOR_PREFIX,false, sizeof(MS_OS_20_DESCRIPTOR_PREFIX), true);
	HID_Device_USBTask(&Generic_HID_Interface, MS_OS_20_DESCRIPTOR_SUFFIX,false, sizeof(MS_OS_20_DESCRIPTOR_SUFFIX), true);
	HID_Device_USBTask(&Generic_HID_Interface, MS_OS_20_CUSTOM_PROPERTY,false, sizeof(MS_OS_20_CUSTOM_PROPERTY), true);
}
void MouseClass::setupClock()
{
	XMC_SCU_CLOCK_Init(&clock_config);
	XMC_SCU_CLOCK_EnableUsbPll();
	XMC_SCU_CLOCK_StartUsbPll(2, 64);
	XMC_SCU_CLOCK_SetUsbClockDivider(4);
	XMC_SCU_CLOCK_SetUsbClockSource(XMC_SCU_CLOCK_USBCLKSRC_USBPLL);
	XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_USB);
	SystemCoreClockUpdate();
}
void MouseClass::end(void)
{
}

void MouseClass::click(uint8_t b)
{
	_buttons = b;
	move(0, 0, 0);
	_buttons = 0;
	move(0, 0, 0);
}

void MouseClass::move(signed char x, signed char y, signed char wheel)
{

	mouse_data[0] = _buttons;
	mouse_data[1] = x;
	mouse_data[2] = y;
	//m[3] = wheel;
	this->SendReport();
}

void MouseClass::buttons(uint8_t b)
{
	if (b != _buttons)
	{
		_buttons = b;
		move(0, 0, 0);
	}
}

void MouseClass::press(uint8_t b)
{
	buttons(_buttons | b);
}

void MouseClass::release(uint8_t b)
{
	buttons(_buttons & ~b);
}

bool MouseClass::isPressed(uint8_t b)
{
	if ((b & _buttons) > 0)
		return true;
	return false;
}
void MouseClass::SendReport(void)
{

	HID_Device_USBTask(&Generic_HID_Interface, mouse_data, false, GENERIC_REPORT_SIZE, true);
	delay(1);
}

MouseClass Mouse;
