/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the GenericHID demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */
#include <wchar.h>
#include "Descriptor.h"
/* Clock configuration */
XMC_SCU_CLOCK_CONFIG_t clock_config =
{
  .syspll_config.p_div = 2,
  .syspll_config.n_div = 80,
  .syspll_config.k_div = 4,
  .syspll_config.mode = XMC_SCU_CLOCK_SYSPLL_MODE_NORMAL,
  .syspll_config.clksrc = XMC_SCU_CLOCK_SYSPLLCLKSRC_OSCHP,
  .enable_oschp = true,
  .calibration_mode = XMC_SCU_CLOCK_FOFI_CALIBRATION_MODE_FACTORY,
  .fsys_clksrc = XMC_SCU_CLOCK_SYSCLKSRC_PLL,
  .fsys_clkdiv = 1,
  .fcpu_clkdiv = 1,
  .fccu_clkdiv = 1,
  .fperipheral_clkdiv = 1
};
/** HID class report descriptor. This is a special descriptor constructed with values from the
 *  USBIF HID class specification to describe the reports and capabilities of the HID device. This
 *  descriptor is parsed by the host and its contents used to determine what data (and in what encoding)
 *  the device will send, and what it may be sent back from the host. Refer to the HID specification for
 *  more details on HID report descriptors.
 */
const USB_Descriptor_HIDReport_Datatype_t HIDMouseReport[] =
{
		HID_DESCRIPTOR_MOUSE(-127,127,-255,255,3,0)

};
/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

	.USBSpecification       = VERSION_BCD(1,1,0),
	.Class                  = USB_CSCP_NoDeviceClass,
	.SubClass               = USB_CSCP_NoDeviceSubclass,
	.Protocol               = USB_CSCP_NoDeviceProtocol,

	.Endpoint0Size          = GENERIC_EPSIZE,

	.VendorID               = 0x04D8,
	.ProductID              = 0x0000,
	.ReleaseNumber          = VERSION_BCD(0,0,1),

	.ManufacturerStrIndex   = STRING_ID_Manufacturer,
	.ProductStrIndex        = STRING_ID_Product,
	.SerialNumStrIndex      = NO_DESCRIPTOR,

	.NumberOfConfigurations = 1
};


/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const USB_Descriptor_Configuration_t ConfigurationDescriptor =
{
	.Config =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

			.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
			.TotalInterfaces        = 1,

			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = NO_DESCRIPTOR,

			.ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED),

			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
		},

	.HID_Interface =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 0,/*INTERFACE_ID_GenericHID*/
			.AlternateSetting       = 0x00,

			.TotalEndpoints         = 1,

			.Class                  = HID_CSCP_HIDClass,
			.SubClass               = HID_CSCP_BootSubclass,
			.Protocol               = HID_CSCP_MouseBootProtocol,

			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.HID_GenericHID =
		{
			.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

			.HIDSpec                = VERSION_BCD(1,1,1),
			.CountryCode            = 0x00,
			.TotalReportDescriptors = 1,
			.HIDReportType          = HID_DTYPE_Report,
			.HIDReportLength        = sizeof(HIDMouseReport)
		},

	.HID_ReportINEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = GENERIC_IN_EPADDR,
			.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = GENERIC_REPORT_SIZE,
			.PollingIntervalMS      = 0x05
		},
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t LanguageString = USB_STRING_DESCRIPTOR_ARRAY(LANGUAGE_ID_ENG);

/** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t ManufacturerString = USB_STRING_DESCRIPTOR(L"Infineon Technologies");

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t ProductString = USB_STRING_DESCRIPTOR(L"LUFA Generic HID Demo");

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;

	switch (DescriptorType)
	{
		case DTYPE_Device:
			Address = &DeviceDescriptor;
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration:
			Address = &ConfigurationDescriptor;
			Size    = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch (DescriptorNumber)
			{
				case STRING_ID_Language:
					Address = &LanguageString;
					Size    = LanguageString.Header.Size;
					break;
				case STRING_ID_Manufacturer:
					Address = &ManufacturerString;
					Size    = ManufacturerString.Header.Size;
					break;
				case STRING_ID_Product:
					Address = &ProductString;
					Size    = ProductString.Header.Size;
					break;
			}

			break;
		case HID_DTYPE_HID:
			Address = &ConfigurationDescriptor.HID_GenericHID;
			Size    = sizeof(USB_HID_Descriptor_HID_t);
			break;
		case HID_DTYPE_Report:
			Address = &HIDMouseReport;
			Size    = sizeof(HIDMouseReport);
			break;
	}

	*DescriptorAddress = Address;
	return Size;
}

/** Buffer to hold the previously generated HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevHIDReportBuffer[GENERIC_REPORT_SIZE];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Generic_HID_Interface =
	{
		.Config =
			{
				.InterfaceNumber              = 0, /*INTERFACE_ID_GenericHID*/
				.ReportINEndpoint             =
					{
						.Address              = GENERIC_IN_EPADDR,
						.Size                 = GENERIC_REPORT_SIZE,
						.Banks                = 1,
					},
				.PrevReportINBuffer           = PrevHIDReportBuffer,
				.PrevReportINBufferSize       = sizeof(PrevHIDReportBuffer),
			},
	};


uint8_t buffer[GENERIC_REPORT_SIZE];

/* USB runtime structure*/
XMC_USBD_t USB_runtime =
{
  .usbd = USB0,
  .usbd_max_num_eps = XMC_USBD_MAX_NUM_EPS_6,
  .usbd_transfer_mode = XMC_USBD_USE_FIFO,
  .cb_xmc_device_event = USBD_SignalDeviceEventHandler,
  .cb_endpoint_event = USBD_SignalEndpointEvent_Handler

};

/*******************************************************************************
**                     Public Function Definitions                            **
*******************************************************************************/

void USB0_0_IRQHandler(void)
{
  XMC_USBD_IRQHandler(&USB_runtime);

}

/*The function initializes the USB core layer and register call backs. */
void USB_Init(void)
{
  USBD_Initialize(&USB_runtime);

  /* Interrupts configuration*/
  NVIC_SetPriority(USB0_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
  NVIC_ClearPendingIRQ(USB0_0_IRQn);
  NVIC_EnableIRQ(USB0_0_IRQn);

  /* USB Connection*/
  USB_Attach();

}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_(void)
{
//	HID_Device_USBTask(&Generic_HID_Interface);
}
/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	//HID_Device_USBTask(&Generic_HID_Interface);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Reset(void)
{
  if(device.IsConfigured)
  {
    USB_Init();
    device.IsConfigured=0;
  }
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
  bool ConfigSuccess = true;

  USBD_SetEndpointBuffer(GENERIC_IN_EPADDR, buffer, GENERIC_REPORT_SIZE);

  ConfigSuccess &= HID_Device_ConfigureEndpoints(&Generic_HID_Interface);

  device.IsConfigured = ConfigSuccess;
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{

	HID_Device_ProcessControlRequest(&Generic_HID_Interface);
}


/*
bool CALLBACK_HIDParser_Filter3HIDReportItem(HID_ReportItem_t* const CurrentItem)
{
  return true;
}*/
/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
}


void EVENT_USB_Device_StartOfFrame(void)
{
}

void EVENT_USB_Device_WakeUp(void)
{
}

void EVENT_USB_Device_Suspend(void)
{
}
/*
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
			                                         uint8_t* const ReportID,
			                                         const uint8_t ReportType,
			                                         void* ReportData,
			                                         uint16_t* const ReportSize)
{
	*ReportID =1;


	USB_MouseReport_Data_t* Data  = (uint8_t*)ReportData;
	Data->Button = mouse_data[0];
	Data->X = mouse_data[1];
	Data->Y = mouse_data[2];

	*ReportSize = GENERIC_REPORT_SIZE;

	return false;
}
*/
/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{

}
