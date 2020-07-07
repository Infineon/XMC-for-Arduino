/*
* Copyright (c) 2015 Arduino LLC. All right reserved.
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*
* Copyright (c) 2020 Infineon Technologies AG
* This library has been modified for the XMC microcontroller series.
*/

#include "Servo.h"

Servo::Servo() {}

bool Servo::attach(uint8_t pin, uint16_t minWidth, uint16_t maxWidth,
                    int16_t minAngle, int16_t maxAngle)
{ 
    if (isAttached || maxWidth < minWidth || maxAngle < minAngle ||
        maxWidth > 20000)
            return false;
    
    pinMode(pin, OUTPUT);
    setAnalogWriteFrequency(pin, 50);
    curUsec = (maxWidth + minWidth) / 2;
    this->minWidth = minWidth;
    this->maxWidth = maxWidth;
    this->minAngle = minAngle;
    this->maxAngle = maxAngle;
    this->pin = pin;
    isAttached = true;
    
    SET_PWM;
    return true;
}

void Servo::write(uint16_t angle)
{
    if (!isAttached)
        return;

    angle = constrain(angle, minAngle, maxAngle);

    curUsec = ANGLE2US(angle);
    SET_PWM;
}

void Servo::writeMicroseconds(uint16_t usec)
{
    if (!isAttached)
        return;

    usec = constrain(usec, minWidth, maxWidth);
    curUsec = usec;
    SET_PWM;
}

uint16_t Servo::read()
{
    return US2ANGLE(curUsec);
}

uint16_t Servo::readMicroseconds()
{
    return curUsec;
}

bool Servo::attached()
{
    return isAttached;
}

bool Servo::detach()
{
    if (!isAttached)
        return false;

    curUsec = 0;
    isAttached = false;
    
    SET_PWM;
    return true;
}
