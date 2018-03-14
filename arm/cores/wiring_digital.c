/*
Copyright (c) 2011 Arduino.  All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

//****************************************************************************
// @Project Includes
//****************************************************************************
#include "Arduino.h"

void pinMode(uint8_t pin, uint8_t mode)
{
    XMC_GPIO_CONFIG_t gpio_conf = {};
    gpio_conf.mode = mode;
    XMC_GPIO_Init(mapping_port_pin[pin].port, mapping_port_pin[pin].pin, &gpio_conf);
}

inline uint8_t digitalRead(uint8_t pin)
{
    /* 
    *  Replacing the XMC_GPIO_GetInput function with direct implementation to enable inlining and avoid compilation error
    *  TODO: Check new XMC library versions for code change of XMC_GPIO_GetInput (unlikely as direct ports are accessed)
    *  uint32_t val = (pin == GND) ? LOW : XMC_GPIO_GetInput(mapping_port_pin[pin].port, mapping_port_pin[pin].pin);
    */
    
    XMC_ASSERT("XMC_GPIO_GetInput: Invalid port", XMC_GPIO_CHECK_PORT(port));

    uint32_t val = (pin == GND) ? LOW : (((mapping_port_pin[pin].port->IN) >> mapping_port_pin[pin].pin) & 0x1U);
    return ((val ? HIGH : LOW));
}

inline void digitalWrite(uint8_t pin, uint8_t value)
{
    /* 
    *  Replacing the XMC_GPIO_SetOutputLevel function with direct implementation to enable inlining and avoid compilation error
    *  TODO: Check new XMC library versions for code change of XMC_GPIO_SetOutputLevel (unlikely as direct ports are accessed)
    *  XMC_GPIO_SetOutputLevel(mapping_port_pin[pin].port, mapping_port_pin[pin].pin, (value == LOW) ? XMC_GPIO_OUTPUT_LEVEL_LOW : XMC_GPIO_OUTPUT_LEVEL_HIGH);
    */
    XMC_ASSERT("XMC_GPIO_SetOutputLevel: Invalid port", XMC_GPIO_CHECK_OUTPUT_PORT(port));
    XMC_ASSERT("XMC_GPIO_SetOutputLevel: Invalid output level", XMC_GPIO_CHECK_OUTPUT_LEVEL(level));
    
    mapping_port_pin[pin].port->OMR = (XMC_GPIO_OUTPUT_LEVEL_t)((uint32_t)(value == LOW) ? XMC_GPIO_OUTPUT_LEVEL_LOW : XMC_GPIO_OUTPUT_LEVEL_HIGH) << mapping_port_pin[pin].pin;
}

inline void digitalToggle(uint8_t pin)
{
    /* 
    *  Replacing the XMC_GPIO_ToggleOutput function with direct implementation to enable inlining and avoid compilation error
    *  TODO: Check new XMC library versions for code change of XMC_GPIO_ToggleOutput (unlikely as direct ports are accessed)
    *  XMC_GPIO_ToggleOutput(mapping_port_pin[pin].port, mapping_port_pin[pin].pin);
    */
    XMC_ASSERT("XMC_GPIO_ToggleOutput: Invalid port", XMC_GPIO_CHECK_OUTPUT_PORT(port));
    mapping_port_pin[pin].port->OMR = 0x10001U << mapping_port_pin[pin].pin;
}
//****************************************************************************
//                                 END OF FILE
//****************************************************************************