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
 *  Header file for GenericHID.c.
 */

#ifndef _GENERICHID_H_
#define _GENERICHID_H_

#ifdef __cplusplus
extern "C" {
#endif
	/* Includes: */
		#include <string.h>
		#include <xmc_gpio.h>
		#include <usblib.h>

	/* Global variables: */
		extern USB_ClassInfo_HID_Device_t Generic_HID_Interface;

		extern XMC_SCU_CLOCK_CONFIG_t clock_config ;
			typedef struct
			{
				USB_Descriptor_Configuration_Header_t Config;

				// Generic HID Interface
				USB_Descriptor_Interface_t            HID_Interface;
				USB_HID_Descriptor_HID_t              HID_GenericHID;
				USB_Descriptor_Endpoint_t             HID_ReportINEndpoint;
			} USB_Descriptor_Configuration_t;
		//  Low level key report: up to 6 keys and shift, ctrl etc at once

	/* Function Prototypes: */
		void  USB_Init(void);

			/** Enum for the device string descriptor IDs within the device. Each string descriptor should
			 *  have a unique ID index associated with it, which can be used to refer to the string from
			 *  other descriptors.
			 */
			enum StringDescriptors_t
			{
				STRING_ID_Language     = 0, /**< Supported Languages string descriptor ID (must be zero) */
				STRING_ID_Manufacturer = 1, /**< Manufacturer string ID */
				STRING_ID_Product      = 2, /**< Product string ID */
			};

		/* Macros: */
	        /** Defines the size of the device reports, both sent and received (including report ID byte). The value must be an integer ranging from 1 to 255 */
			#define GENERIC_REPORT_SIZE      3

			/** Endpoint address of the Generic HID reporting IN endpoint. */
			#define GENERIC_IN_EPADDR         (ENDPOINT_DIR_IN | 1)

			/** Size in bytes of the Generic HID reporting endpoint. */
			#define GENERIC_EPSIZE            64

		/* Function Prototypes: */
		/*	bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
						                                         uint8_t* const ReportID,
						                                         const uint8_t ReportType,
						                                         void* ReportData,
						                                         uint16_t* const ReportSize);*/
			uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
			                                    const uint8_t wIndex,
			                                    const void** const DescriptorAddress)
			                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#ifdef __cplusplus
}
#endif
#endif

