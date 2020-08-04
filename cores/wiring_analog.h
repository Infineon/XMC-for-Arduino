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

#ifndef _WIRING_ANALOG_
#define _WIRING_ANALOG_

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// @External Prototypes
//****************************************************************************

    /*
     * \brief Configures the reference voltage used for analog input (i.e. the value used as the top of the input range).
     * This function is kept only for compatibility with existing AVR based API.
     *
     * \param ulMmode Should be set to DEFAULT.
     *
     */
    extern void analogReference( uint8_t ulMode ) ;

    /*
     * \brief Writes an analogue value to a DAC or PWM wave to a pin.
     *        DAC is straight write to DAC (if present on that pin)
     *
     *        PWM depends on analogWriteResolution()
     *        Effect of value is the duty cycle for PWM output to be HIGH
     *        Valid values are
     *                   Write resolution (bits)
     *        Value      8      10      12      16
     *        OFF        0      0       0       0
     *        ON always  255    1023    4095    65535
     *
     *        Values in between these values vary the duty cycle
     *
     * \param pin
     * \param value must be 0 to max value for ADC WRITE resolution
     *
     * \return 0 = success, -1 = invalid value, -2 = wrong pin
     */
    extern int16_t analogWrite( uint8_t pin, uint16_t value ) ;

    /*
     * \brief Sets the frequency for analogWrite PWM.
     *
     *    Returns -2 invalid pin
     *            -1 invalid frequency
     *             0 success
     *
     * \note Default value is 490 Hz
     *
     * \param pin
     * \param frequency in Hz
     *
     * \return 0 = success, -1 = invalid frequency, -2 = wrong pin
     */
    extern int16_t setAnalogWriteFrequency( uint8_t pin, uint32_t frequency ) ;

    /*
     * \brief Reads the value from the specified analogue channel.
     *
     * \param channel
     *
     * \return Read value from selected channel, or 0xFFFFFFFF for error.
     */
    extern uint32_t analogRead( uint8_t channel ) ;

    /*
     * \brief Set the resolution of analogRead return values in number of bits.
     * \note Default is 10 bits (range from 0 to 1023).
     *
     * \param res  - range 8 to 12
     *
     * \return valid bits set (8 to 12) or 255 for error
     */
    extern uint8_t analogReadResolution( uint8_t res );

    /*
     * \brief Set the resolution of analogWrite parameters in number of bits.
     * \note Default (minimum) is 8 bits (range from 0 to 16).
     *  Maximum is 16 bits (range 0 to 65535)
     *
     * \param res  - range 8 to 16
     *
     * \return valid bits set (8 to 16) or 255 for error
     */
    extern uint8_t analogWriteResolution( uint8_t res );

    extern void wiring_analog_init( );

    /*********************************************************
     \brief Additional helper functions for other libraries
    **********************************************************/
    /*
     * \brief Get the current resolution of analogRead in number of bits.
     *
     * \return Current resolution in bits (8 to 12)
     */
    extern uint8_t getAnalogReadBits( );

    /*
     * \brief Get the current resolution of analogWrite in number of bits.
     *
     * \return Current resolution in bits (8 to 16)
     */
    extern uint8_t getAnalogWriteBits( );

    /*
     * \brief Get the maximum value for current resolution for analogRead.
     * \note Default is 1023
     * \note Maximum is 4095
     *
     * \return Current maximum value
     */
    extern uint16_t getAnalogReadMaximum( );

    /*
     * \brief Get the maximum value for current resolution for analogWrite.
     * \note Default is 255
     * \note Maximum is 65535
     *
     * \return Current maximum value
     */
    extern uint16_t getAnalogWriteMaximum(  );

#ifdef __cplusplus
}
#endif

#endif /* _WIRING_ANALOG_ */
