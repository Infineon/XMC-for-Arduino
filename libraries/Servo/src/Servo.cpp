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
    if (this->isAttached || maxWidth < minWidth || maxAngle < minAngle ||
        maxWidth > 20000)
            return false;
    
    pinMode(pin, OUTPUT);
    setAnalogWriteFrequency(pin, 50);
    this->curUsec = (maxWidth + minWidth) / 2;
    this->minWidth = minWidth;
    this->maxWidth = maxWidth;
    this->minAngle = minAngle;
    this->maxAngle = maxAngle;
    this->pin = pin;
    this->isAttached = true;
    
    SET_PWM;
    return true;
}

void Servo::write(uint16_t angle)
{
    if (!this->isAttached)
        return;

    angle = constrain(angle, this->minAngle, this->maxAngle);

    this->curUsec = ANGLE2US(angle);
    SET_PWM;
}

void Servo::writeMicroseconds(uint16_t usec)
{
    if (!this->isAttached)
        return;

    usec = constrain(usec, this->minWidth, this->maxWidth);
    this->curUsec = usec;
    SET_PWM;
}

uint16_t Servo::read()
{
    return US2ANGLE(this->curUsec);
}

uint16_t Servo::readMicroseconds()
{
    return this->curUsec;
}

bool Servo::attached()
{
    return this->isAttached;
}

bool Servo::detach()
{
    if (!this->isAttached)
        return false;

    this->curUsec = 0;
    this->isAttached = false;
    
    SET_PWM;
    return true;
}
