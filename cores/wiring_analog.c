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
/* Paul Carpenter  March-2019
   Several fixes to remove redundant code
   Fix prescaler bug for CCU8 in analogWriteFrequency
   analogWrite - Improvements, extra safety and more documentation
   analogRead - Change return to 0xFFFFFFFF (an invalid value) for invalid channel
   wiring_analog_init - Add dummy reading so background scanning starts on ALL
                possible channels meaning first user reading will be valid
*/
/* Paul Carpenter  September-2019
   Add definition ADC_MIN_RESOLUTION for error checking parameters
   Add maximum resolution values for helper functions
   On errors where possible nothing changed or read
   Add helper functions for Read and Write resolution settings for other modules
   especially using PWM on analogWrite to scale parameters correctly
    getAnaolgReadBits, getAnaolgWriteBits,  getAnaolgReadMaximum, getAnaolgWriteMaximum
   Add more return values for error trapping -
   analogWrite - Change error values for invalid and separate invalid frequency
*/
//****************************************************************************
// @Project Includes
//****************************************************************************
#include "Arduino.h"
#include <string.h>

//****************************************************************************
// @Defines
//****************************************************************************
#define ADC_CONVERSION_GROUP            0
#define ADC_MIN_RESOLUTION              8
#define ADC_MAX_READ_RESOLUTION         12
#define ANALOG_MAX_WRITE_RESOLUTION     16

//****************************************************************************
// @Global Variables
//****************************************************************************
static uint8_t _readResolution = 10;
static uint8_t _writeResolution = 8;
uint16_t _readMaximum = 1023;
uint16_t _writeMaximum = 255;


void wiring_analog_init( void )
{
/* Initialization data of VADC Global resources */
XMC_VADC_GLOBAL_CONFIG_t vadc_global_config;
memset( &vadc_global_config, 0, sizeof( XMC_VADC_GLOBAL_CONFIG_t ) );
vadc_global_config.class0.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT;
vadc_global_config.class1.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT;

XMC_VADC_BACKGROUND_CONFIG_t vadc_background_config = { 0 };

/* Provide clock to VADC and initialize the VADC global registers. */
XMC_VADC_GLOBAL_Init( VADC, &vadc_global_config );

#if(XMC_VADC_GROUP_AVAILABLE == 1U)
// ADC grouping
XMC_VADC_GROUP_CONFIG_t vadc_group_config;
memset( &vadc_group_config, 0, sizeof( XMC_VADC_GROUP_CONFIG_t ) );
vadc_group_config.class0.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT;
vadc_group_config.class1.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT;

/* Initialize Group */
XMC_VADC_GROUP_Init( VADC_G0, &vadc_group_config );
XMC_VADC_GROUP_Init( VADC_G1, &vadc_group_config );

/* Switch on the converter of the Group*/
XMC_VADC_GROUP_SetPowerMode( VADC_G0, XMC_VADC_GROUP_POWERMODE_NORMAL );
XMC_VADC_GROUP_SetPowerMode( VADC_G1, XMC_VADC_GROUP_POWERMODE_NORMAL );

#if(XMC_VADC_MAXIMUM_NUM_GROUPS > 2)
/* Initialize Group */
XMC_VADC_GROUP_Init( VADC_G2, &vadc_group_config );
XMC_VADC_GROUP_Init( VADC_G3, &vadc_group_config );

/* Switch on the converter of the Group*/
XMC_VADC_GROUP_SetPowerMode( VADC_G2, XMC_VADC_GROUP_POWERMODE_NORMAL );
XMC_VADC_GROUP_SetPowerMode( VADC_G3, XMC_VADC_GROUP_POWERMODE_NORMAL );
#endif

#endif
/* Calibrate the VADC. Make sure you do this after all used VADC groups
   are set to normal operation mode. */
XMC_VADC_GLOBAL_StartupCalibration( VADC );

/* Initialize the background source hardware. The gating mode is set to
   ignore to pass external triggers unconditionally.*/
XMC_VADC_GLOBAL_BackgroundInit( VADC, &vadc_background_config );

/* PC Mar-2019
   Dummy read of ALL analogue inputs to ensure ALL analogue channels are
   started in background scanning mode, otherwise first readings at least
   will always be zero on reading an analogue input. */
for( uint8_t chan = 0; chan < NUM_ANALOG_INPUTS; chan++ )
   analogRead( chan );

//Additional Initialization of DAC starting here
}


/* Set the resolution of analogRead return values in number of bits.
    Default is 10 bits (range from 0 to 1023)
    Maximum is 12 bits (range from 0 to 4095)

PC Sept-2019 Change flow to trap invalid input first and leave at old setting if
    Invalid and return valid value or 255 for error, else return setting used

    Add set maximum value for resolution
*/
uint8_t analogReadResolution( uint8_t res )
{
if( res > ADC_MAX_READ_RESOLUTION || res < ADC_MIN_RESOLUTION )
  return 255;

_readResolution = res;
_readMaximum = (uint16_t)( ( (uint32_t)1U << res ) - 1 );
return res;
}


/* Set the resolution of analogWrite parameters in number of bits.

    Default (minimum) is 8 bits (range from 0 to 255).
    Maximum is 16 bits (range 0 to 65535)

PC Sept-2019 Change flow to trap invalid input first and leave at old setting if
    Invalid and return valid value or 255 for error, else return setting used

    Add set maximum value for resolution
  */
uint8_t analogWriteResolution( uint8_t res )
{
if( res > ANALOG_MAX_WRITE_RESOLUTION || res < ADC_MIN_RESOLUTION )
  return 255;

_writeResolution = res;
_writeMaximum = (uint16_t)( ( (uint32_t)1U << res ) - 1 );
return res;
}


// This appears to be a dummy function and variable not used elsewhere
uint8_t analog_reference = DEFAULT;

void analogReference( uint8_t ulMode )
{
analog_reference = ulMode;
}


/* analogRead takes parameter of ADC channel number
        return 0xFFFFFFFF for invalid channel */
uint32_t analogRead( uint8_t channel )
{
uint32_t value;

value = 0xFFFFFFFF;
if( channel < NUM_ANALOG_INPUTS )
  {
  XMC_ADC_t *adc = &mapping_adc[ channel ];

#if(XMC_VADC_GROUP_AVAILABLE == 1U)
  // ADC grouping
  if( !(adc->enabled) )
    {
    XMC_VADC_CHANNEL_CONFIG_t  vadc_gobal_channel_config;
    memset( &vadc_gobal_channel_config, 0, sizeof( XMC_VADC_CHANNEL_CONFIG_t ) );
    vadc_gobal_channel_config.input_class       = XMC_VADC_CHANNEL_CONV_GROUP_CLASS1;
    vadc_gobal_channel_config.result_reg_number = adc->result_reg_num;
    vadc_gobal_channel_config.alias_channel     = XMC_VADC_CHANNEL_ALIAS_DISABLED;

    XMC_VADC_RESULT_CONFIG_t vadc_gobal_result_config = { .g_rcr = 0 };
    /* Configure a channel belonging to the aforesaid conversion kernel */
    XMC_VADC_GROUP_ChannelInit( adc->group, adc->channel_num, &vadc_gobal_channel_config );
    /* Configure a result resource belonging to the aforesaid conversion kernel */
    XMC_VADC_GROUP_ResultInit( adc->group, adc->result_reg_num, &vadc_gobal_result_config );
    /* Add channel into the Background Request Source Channel Select Register */
    XMC_VADC_GLOBAL_BackgroundAddChannelToSequence( VADC, (uint32_t)adc->group_num,
                                                          (uint32_t)adc->channel_num );
    }
  /* Start conversion manually using load event trigger*/
  XMC_VADC_GLOBAL_BackgroundTriggerConversion( VADC );
  value = XMC_VADC_GROUP_GetResult( adc->group, adc->result_reg_num );
#else
  // XMC1100 no ADC grouping
  if( !(adc->enabled) )
    /* Add a channel to the background source. */
    VADC->BRSSEL[ ADC_CONVERSION_GROUP ] = (uint32_t)( 1U << adc->channel_num );
  // Generates conversion request
  XMC_VADC_GLOBAL_BackgroundTriggerConversion( VADC );

  // Wait until conversion is ready
  while( ( ( value = XMC_VADC_GLOBAL_GetDetailedResult( VADC ) ) & VADC_GLOBRES_VF_Msk) == 0u );
#endif
  value = ( ( value & VADC_GLOBRES_RESULT_Msk) >> ( ADC_MAX_READ_RESOLUTION - _readResolution ) );
  }
return value;
}


/* Helper function for analogWrite and setAnalogWriteFrequency to scan
   mapping tables to determine for a given pin which PWM4, PWM8 or DAC
   channel to use
   Returns valid channel index or -1 for not listed
   reading first column as 255 denotes end of table
   See pins_arduino.h for table layout
*/
int16_t scan_map_table( const uint8_t table[][ 2 ], uint8_t pin )
{
int16_t i;

i = 0;
while( table[ i ][ 0 ] != 255 )
    {
    if( table[ i ][ 0 ] == pin )
      break;
    i++;
    }
if( table[ i ][ 0 ] != 255 )
  return table[ i ][ 1 ];
return -1;
}


/* Writes an analogue value to a DAC or PWM wave to a pin.
    DAC is straight write to DAC (if present on that pin)

    PWM depends on analogWriteResolution()
    Effect of value is the duty cycle for PWM output to be HIGH
    Valid values are
               Write resolution (bits)
    Value      8      10      12      16
    OFF        0      0       0       0
    ON always  255    1023    4095    65535

    Values in between these values vary the duty cycle

    Returns     0 = success
               -1 = invalid value
               -2 = wrong pin
*/
int16_t analogWrite( uint8_t pin, uint16_t value )
{
uint32_t compare_reg = 0;
int16_t resource;

if( value > _writeMaximum )
  return -1;

if( ( resource = scan_map_table( mapping_pin_PWM4, pin ) ) >= 0 )
  {
  XMC_PWM4_t *pwm4 = &mapping_pwm4[ resource ];

  if( !(pwm4->enabled) )
    {
    // Slice not yet initialized
    XMC_CCU4_SLICE_COMPARE_CONFIG_t pwm_config;
    memset( &pwm_config, 0, sizeof( XMC_CCU4_SLICE_COMPARE_CONFIG_t ) );
    pwm_config.passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
    pwm_config.prescaler_initval = pwm4->prescaler;

    XMC_CCU4_Init( pwm4->ccu, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR );
    XMC_CCU4_SLICE_CompareInit( pwm4->slice, &pwm_config );
    XMC_CCU4_EnableClock( pwm4->ccu, pwm4->slice_num );
    XMC_CCU4_SLICE_SetTimerPeriodMatch( pwm4->slice, pwm4->period_timer_val );

    pwm4->enabled = ENABLED;
    }

  if( value != 0 )
    compare_reg  = ( ( value + 1 ) * ( pwm4->period_timer_val + 1 ) ) >> _writeResolution;

  XMC_CCU4_SLICE_SetTimerCompareMatch( pwm4->slice, compare_reg );
  XMC_CCU4_EnableShadowTransfer( pwm4->ccu, ( CCU4_GCSS_S0SE_Msk << ( 4 * pwm4->slice_num ) ) );
  XMC_GPIO_SetMode( pwm4->port_pin.port, pwm4->port_pin.pin,
                                  ( XMC_GPIO_MODE_OUTPUT_PUSH_PULL | pwm4->port_mode ) );
  XMC_CCU4_SLICE_StartTimer( pwm4->slice );
  }
#ifdef CCU8V2
else
  if( ( resource = scan_map_table( mapping_pin_PWM8, pin ) ) >= 0 )
    {
    XMC_PWM8_t *pwm8 = &mapping_pwm8[ resource ];

    if( !(pwm8->enabled) )
      {
      // Slice not yet initialized
      XMC_CCU8_SLICE_COMPARE_CONFIG_t pwm_config;
      memset( &pwm_config, 0, sizeof( XMC_CCU8_SLICE_COMPARE_CONFIG_t ) );
      pwm_config.passive_level_out0 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
      pwm_config.passive_level_out1 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
      pwm_config.passive_level_out2 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
      pwm_config.passive_level_out3 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
      pwm_config.prescaler_initval = pwm8->prescaler;

      XMC_CCU8_Init( pwm8->ccu, XMC_CCU8_SLICE_MCMS_ACTION_TRANSFER_PR_CR );
      XMC_CCU8_SLICE_CompareInit( pwm8->slice, &pwm_config );
      XMC_CCU8_EnableClock( pwm8->ccu, pwm8->slice_num );
      XMC_CCU8_SLICE_SetTimerPeriodMatch( pwm8->slice, pwm8->period_timer_val );
      pwm8->enabled = ENABLED;
      }

    if( value != 0 )
      compare_reg  = ( ( value + 1 ) * ( pwm8->period_timer_val + 1 ) ) >> _writeResolution;

    XMC_CCU8_SLICE_SetTimerCompareMatch( pwm8->slice, pwm8->slice_channel, compare_reg );
    XMC_CCU8_EnableShadowTransfer( pwm8->ccu, CCU8_GCSS_S0SE_Msk << ( 4 * pwm8->slice_num ) );
    XMC_GPIO_SetMode( pwm8->port_pin.port, pwm8->port_pin.pin,
                                XMC_GPIO_MODE_OUTPUT_PUSH_PULL | pwm8->port_mode );
    XMC_CCU8_SLICE_StartTimer( pwm8->slice );
    }
#endif
#ifdef DAC
else
  if( ( resource = scan_map_table( mapping_pin_DAC, pin ) ) >= 0 )
    {
    XMC_ARD_DAC_t *dac = &( mapping_dac[ resource ] );
    XMC_DAC_Enable( dac->group );
    XMC_DAC_CH_EnableOutput( dac->group, dac->channel );
    XMC_DAC_CH_StartSingleValueMode(dac->group, dac->channel );
    uint16_t dacValue = map(value, 0, ( 0b10 << _writeResolution ) - 1, 0,
                                ( 0b10 << dac->resolution ) - 1 );
    XMC_DAC_CH_Write( dac->group, dac->channel, dacValue );
    }
#endif
  else
    return -2;
return 0;
}


/* Sets the frequency for analogWrite PWM.

   Parameters   pin
                frequency in Hz

   Returns -2 invalid pin
           -1 invalid frequency
            0 Success
*/
int16_t setAnalogWriteFrequency( uint8_t pin, uint32_t frequency )
{
int16_t ret = -1;
uint16_t prescaler = 0U;
int16_t resource;
uint16_t period;

if( frequency < PCLK )
  {
  do
    {
    if( frequency > ( PCLK / ( ( 1U << prescaler ) * 65536U ) ) )
      break;
    prescaler++;
    }
  while( prescaler < 15 );      // Prescaler must never be > 15

  // Calculate 16 bit timer end value
  period = ( PCLK / ( ( 1U << prescaler )  * frequency ) ) - 1;

  if( ( resource = scan_map_table( mapping_pin_PWM4, pin ) ) >= 0 )
    {
    XMC_PWM4_t *pwm4 = &mapping_pwm4[ resource ];

    pwm4->prescaler = prescaler;
    pwm4->period_timer_val = period;
    if( pwm4->enabled == ENABLED )
      {
      // Disable pwm output
      pwm4->enabled = DISABLED;
      XMC_CCU4_SLICE_StartTimer( pwm4->slice );
      }
    ret = 0;
    }
#ifdef CCU8V2
  else
    if ( ( resource = scan_map_table( mapping_pin_PWM8, pin ) ) >= 0 )
      {
      XMC_PWM8_t *pwm8 = &mapping_pwm8[ resource ];

      pwm8->prescaler = prescaler;
      pwm8->period_timer_val = period;
      if( pwm8->enabled == ENABLED )
        {
        // Disable pwm output
        pwm8->enabled = DISABLED;
        XMC_CCU8_SLICE_StartTimer( pwm8->slice );
        }
      ret = 0;
      }
#endif
  if( ret == -1 )           // Catch pin not found
    ret = -2;
  }
return ret;
}


/* PC Sept-2019
    Add helper functions to get Read and Write resolution as bits or maximum value
*/
/* Get the current resolution of analogRead in number of bits.
    Return Current resolution in bits (8 to 12)
 */
uint8_t getAnalogReadBits( )
{
return _readResolution;
}


/* Get the current resolution of analogWrite in number of bits.
    Return Current resolution in bits (8 to 16)
 */
uint8_t getAnalogWriteBits( )
{
return _writeResolution;
}


/* Get the maximum value for current resolution for analogRead.
    Default is 1023
    Maximum is 4095
 */
uint16_t getAnalogReadMaximum( )
{
return _readMaximum;
}


/* Get the maximum value for current resolution for analogWrite.
    Default is 255
    Maximum is 65535
 */
uint16_t getAnalogWriteMaximum(  )
{
return _writeMaximum;
}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
