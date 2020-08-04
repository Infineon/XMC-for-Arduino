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
 *  Header file for VirtualSerial.c.
 */

#ifndef _VIRTUALSERIAL_H_
#define _VIRTUALSERIAL_H_
#ifdef __cplusplus
extern "C"
{
#endif
  /* Includes: */
#include "Descriptors.h"
#include <usblib.h>

  /* Global variables: */
  extern const XMC_SCU_CLOCK_CONFIG_t clk_config;
  extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;
  extern XMC_USBD_t USB_runtime;
  /* Function Prototypes: */
  void USB_Init(uint8_t baudrate);

  void EVENT_USB_Device_Connect(void);
  void EVENT_USB_Device_Disconnect(void);
  void EVENT_USB_Device_ConfigurationChanged(void);
  void EVENT_USB_Device_ControlRequest(void);

#ifdef __cplusplus
}
#endif

#endif
