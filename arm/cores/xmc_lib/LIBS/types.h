/******************************************************************************
 *
 * Copyright (C) 2011 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
********************************************************************************
**                                                                            **
**                                                                            **
** PLATFORM : Infineon XMC4000/XMC1000 Series                                 **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** AUTHOR   : App Developer                                                   **
**                                                                            **
** MAY BE CHANGED BY USER [yes/no]: Yes                                       **
**                                                                            **
** MODIFICATION DATE : May 30, 2012                                         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Author(s) Identity                                   **
********************************************************************************
**                                                                            **
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** MV           App Developer                                                 **
*******************************************************************************/
/**
 * @file types.h
 *
 * @brief  This file contains types defs.
 *
 */
/* Revision History
 *  1  Dec 2012   v1.0.4   taken as base version
 *  25 Apr 2013   v1.0.10  __STDBOOL_H__ is changed to _STDBOOL_H
  */
#ifndef TYPES_CONFIG_H_
#define TYPES_CONFIG_H_

 
#include "stdint.h"
#include "stddef.h"

#define DAVEApp_SUCCESS  0
#define NULL_PTR NULL

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t u8;


typedef signed long  s32;
typedef signed short s16;
typedef int8_t  s8;
typedef uint32_t dma_addr_t;

typedef uint32_t status_t;
typedef uint32_t handle_t;

#if defined(__TASKING__) || defined (__GNUC__)
#else
typedef uint32_t time_t;
#endif

typedef enum SetResetType{
  RESET,
  SET
}SetResetType;

typedef enum BOOLType{
  FALSE,
  TRUE
}BOOLType;


#ifndef __cplusplus
#ifndef _STDBOOL_H
typedef unsigned char bool;
#endif
#endif

#ifndef EOF
#define EOF     (-1)
#endif      /* EOF */

#ifndef MIN
#define MIN(a,b)    (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b)    (((a) > (b)) ? (a) : (b))
#endif

#endif /* TYPES_CONFIG_H_ */

