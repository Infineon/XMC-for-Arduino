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

  Copyright (c) 2018 Infineon Technologies AG
  This file has been modified for the XMC microcontroller series.
 */

//****************************************************************************
// @Project Includes
//****************************************************************************
#include "Arduino.h"
#ifdef __cplusplus
extern "C" {
#endif
void pinMode(pin_size_t pin, PinMode mode) {
    XMC_GPIO_CONFIG_t gpio_conf;

    switch (mode) {
    case INPUT:
        gpio_conf.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
        gpio_conf.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
        break;

    case INPUT_PULLUP:
        gpio_conf.mode = XMC_GPIO_MODE_INPUT_PULL_UP;
        gpio_conf.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
        break;

    case INPUT_PULLDOWN:
        gpio_conf.mode = XMC_GPIO_MODE_INPUT_PULL_DOWN;
        gpio_conf.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
        break;

    case OUTPUT:
        gpio_conf.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
        gpio_conf.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
        break;
    case OUTPUT_OPENDRAIN:
        gpio_conf.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN;
        gpio_conf.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
        break;

    default:
        return;
    }

#if UC_FAMILY == XMC1
    gpio_conf.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_LARGE;
#endif
    XMC_GPIO_Init(mapping_port_pin[pin].port, mapping_port_pin[pin].pin, &gpio_conf);
}

uint8_t digitalRead(uint8_t pin){  
    return (pin == GND)
               ? LOW
               : (XMC_GPIO_GetInput(mapping_port_pin[pin].port, mapping_port_pin[pin].pin));
}

void digitalWrite(uint8_t pin, uint8_t status) {
    XMC_GPIO_SetOutputLevel(mapping_port_pin[pin].port, mapping_port_pin[pin].pin,
                            (status == LOW) ? XMC_GPIO_OUTPUT_LEVEL_LOW
                                            : XMC_GPIO_OUTPUT_LEVEL_HIGH);
}

#ifdef __cplusplus
}
#endif
//****************************************************************************
//                                 END OF FILE
//****************************************************************************