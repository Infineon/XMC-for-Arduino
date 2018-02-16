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

void pinMode( uint8_t pin, uint8_t mode )
{
    XMC_GPIO_CONFIG_t gpio_conf;
    gpio_conf.mode = mode;

    XMC_GPIO_Init(mapping_port_pin[pin].port, mapping_port_pin[pin].pin, &gpio_conf);
}

uint8_t digitalRead(uint8_t pin)
{
    uint32_t val = (pin == GND) ? LOW : XMC_GPIO_GetInput(mapping_port_pin[pin].port, mapping_port_pin[pin].pin);
    return ((val ? HIGH : LOW));
}

void digitalWrite(uint8_t pin, uint8_t value)
{
    XMC_GPIO_SetOutputLevel(mapping_port_pin[pin].port, mapping_port_pin[pin].pin, (value == LOW) ? XMC_GPIO_OUTPUT_LEVEL_LOW : XMC_GPIO_OUTPUT_LEVEL_HIGH);

}

void digitalToggle(uint8_t pin)
{
    XMC_GPIO_ToggleOutput(mapping_port_pin[pin].port, mapping_port_pin[pin].pin);

}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
