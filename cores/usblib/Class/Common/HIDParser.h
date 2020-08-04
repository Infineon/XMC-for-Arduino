#ifdef XMC4_SERIES

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
 *  \brief USB Human Interface Device (HID) Class report descriptor parser.
 *
 *  This file allows for the easy parsing of complex HID report descriptors, which describes the data that
 *  a HID device transmits to the host. It also provides an easy API for extracting and processing the data
 *  elements inside a HID report sent from an attached HID device.
 */

/** \ingroup Group_USB
 *  \defgroup Group_HIDParser HID Report Parser
 *  \brief USB Human Interface Device (HID) Class report descriptor parser.
 *
 *  \section Sec_HIDParser_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/HIDParser.c <i>(Makefile source module name: LUFA_SRC_USB)</i>
 *
 *  \section Sec_HIDParser_ModDescription Module Description
 *  Human Interface Device (HID) class report descriptor parser. This module implements a parser than is
 *  capable of processing a complete HID report descriptor, and outputting a flat structure containing the
 *  contents of the report in an a more friendly format. The parsed data may then be further processed and used
 *  within an application to process sent and received HID reports to and from an attached HID device.
 *
 *  A HID report descriptor consists of a set of HID report items, which describe the function and layout
 *  of data exchanged between a HID device and a host, including both the physical encoding of each item
 *  (such as a button, key press or joystick axis) in the sent and received data packets - known as "reports" -
 *  as well as other information about each item such as the usages, data range, physical location and other
 *  characteristics. In this way a HID device can retain a high degree of flexibility in its capabilities, as it
 *  is not forced to comply with a given report layout or feature-set.
 *
 *  This module also contains routines for the processing of data in an actual HID report, using the parsed report
 *  descriptor data as a guide for the encoding.
 *
 *  @{
 */

#ifndef __HIDPARSER_H__
#define __HIDPARSER_H__

	/* Includes: */
		#include <../../Common/Common.h>

		#include "HIDReportData.h"
		#include "HIDClassCommon.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif



		#if !defined(HID_MAX_REPORT_IDS) || defined(__DOXYGEN__)
			/** Constant indicating the maximum number of unique report IDs that can be processed in the report item
			 *  descriptor for the report size information array in the user HID Report Info structure. A large value
			 *  allows for more report ID report sizes to be stored, but consumes more memory. By default this is set
			 *  to 10 items, but this can be overridden by defining \c HID_MAX_REPORT_IDS to another value in the user project
			 *  makefile, and passing the define to the compiler using the -D compiler switch. Note that IN, OUT and FEATURE
			 *  items sharing the same report ID consume only one size item in the array.
			 */
			#define HID_MAX_REPORT_IDS            10
		#endif

		/** Returns the value a given HID report item (once its value has been fetched via \ref USB_GetHIDReportItemInfo())
		 *  left-aligned to the given data type. This allows for signed data to be interpreted correctly, by shifting the data
		 *  leftwards until the data's sign bit is in the correct position.
		 *
		 *  \param[in] ReportItem  HID Report Item whose retrieved value is to be aligned.
		 *  \param[in] Type        Data type to align the HID report item's value to.
		 *
		 *  \return Left-aligned data of the given report item's pre-retrieved value for the given datatype.
		 */
		#define HID_ALIGN_DATA(ReportItem, Type) ((Type)(ReportItem->Value << ((8 * sizeof(Type)) - ReportItem->Attributes.BitSize)))



	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */


#endif /* UC_FAMILY == XMC4 */
