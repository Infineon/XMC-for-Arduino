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

#ifndef SERVO_H
#define SERVO_H

#include "Arduino.h"

#define MIN_WIDTH 1000
#define MAX_WIDTH 2000

#define MIN_ANGLE 0
#define MAX_ANGLE 180

#define US2DUTY(USEC) map(USEC, 0, 20000, 0, getAnalogWriteMaximum())
#define US2ANGLE(USEC) map(USEC, minWidth, maxWidth, minAngle, maxAngle)
#define ANGLE2US(ANGLE) map(ANGLE, minAngle, maxAngle, minWidth, maxWidth)
#define SET_PWM analogWrite(pin, US2DUTY(curUsec))

class Servo {
public:
    Servo();
    bool attach(uint8_t, uint16_t = MIN_WIDTH, uint16_t = MAX_WIDTH, \
                int16_t = MIN_ANGLE, int16_t = MAX_ANGLE);
    void write(uint16_t);
    void writeMicroseconds(uint16_t);
    uint16_t read();
    uint16_t readMicroseconds();
    bool attached();
    bool detach();

private:
    uint8_t pin;
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t curUsec;
    int16_t minAngle;
    int16_t maxAngle;
    bool isAttached;
};

#endif
