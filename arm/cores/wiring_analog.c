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

//****************************************************************************
// @Defines
//****************************************************************************
#define ADC_CONVERSION_GROUP            0
#define ADC_MAX_READ_RESOLUTION         12
#define ANALOG_MAX_WRITE_RESOLUTION     16

//****************************************************************************
// @Global Variables
//****************************************************************************
static uint8_t _readResolution = 10;
static uint8_t _writeResolution = 8;

void wiring_analog_init(void)
{
    /* Initialization data of VADC Global resources */
    XMC_VADC_GLOBAL_CONFIG_t vadc_global_config = {0};
    vadc_global_config.class0.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT;
    vadc_global_config.class1.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT;

    XMC_VADC_BACKGROUND_CONFIG_t vadc_background_config = {0};

    /* Provide clock to VADC and initialize the VADC global registers. */
    XMC_VADC_GLOBAL_Init(VADC, &vadc_global_config);

#if(XMC_VADC_GROUP_AVAILABLE == 1U)
// ADC grouping
    XMC_VADC_GROUP_CONFIG_t vadc_group_config = {0};
    vadc_group_config.class0.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT;
    vadc_group_config.class1.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT;

    /*Initialize Group*/
    XMC_VADC_GROUP_Init(VADC_G0, &vadc_group_config);
    XMC_VADC_GROUP_Init(VADC_G1, &vadc_group_config);
	
    /* Switch on the converter of the Group*/
    XMC_VADC_GROUP_SetPowerMode(VADC_G0, XMC_VADC_GROUP_POWERMODE_NORMAL);
    XMC_VADC_GROUP_SetPowerMode(VADC_G1, XMC_VADC_GROUP_POWERMODE_NORMAL);
	
#if(XMC_VADC_MAXIMUM_NUM_GROUPS > 2)
    /*Initialize Group*/
    XMC_VADC_GROUP_Init(VADC_G2, &vadc_group_config);

    /* Switch on the converter of the Group*/
    XMC_VADC_GROUP_SetPowerMode(VADC_G2, XMC_VADC_GROUP_POWERMODE_NORMAL);
#endif	

#endif

    /* Calibrate the VADC. Make sure you do this after all used VADC groups
    * are set to normal operation mode. */
    XMC_VADC_GLOBAL_StartupCalibration(VADC);

    /* Initialize the background source hardware. The gating mode is set to
    * ignore to pass external triggers unconditionally.*/
    XMC_VADC_GLOBAL_BackgroundInit(VADC, &vadc_background_config);
	
	
	//Additional Initialization of DAC starting here
	
}

void analogReadResolution(uint8_t res)
{
    if (res > ADC_MAX_READ_RESOLUTION)
    {
        res = ADC_MAX_READ_RESOLUTION;
    }

    _readResolution = res;
}

void analogWriteResolution(uint8_t res)
{
    if (res > ANALOG_MAX_WRITE_RESOLUTION)
    {
        res = ANALOG_MAX_WRITE_RESOLUTION;
    }

    _writeResolution = res;
}

uint8_t analog_reference = DEFAULT;

void analogReference(uint8_t ulMode)
{
    analog_reference = ulMode;
}

uint32_t analogRead(uint8_t pin)
{
    uint32_t value = 0;
    if (isanalogPin(pin))
    {
        uint8_t adc_num = analogPinToADCNum(pin);
        XMC_ADC_t *adc = &mapping_adc[adc_num];

#if(XMC_VADC_GROUP_AVAILABLE == 1U)
// ADC grouping
        if (!(adc->enabled))
        {
            XMC_VADC_CHANNEL_CONFIG_t  vadc_gobal_channel_config = {0};
            vadc_gobal_channel_config.input_class       = XMC_VADC_CHANNEL_CONV_GROUP_CLASS1;
            vadc_gobal_channel_config.result_reg_number = adc->result_reg_num;
            vadc_gobal_channel_config.alias_channel     = XMC_VADC_CHANNEL_ALIAS_DISABLED;

            XMC_VADC_RESULT_CONFIG_t vadc_gobal_result_config = {0};

            /* Configure a channel belonging to the aforesaid conversion kernel */
            XMC_VADC_GROUP_ChannelInit(adc->group, adc->channel_num, &vadc_gobal_channel_config);

            /* Configure a result resource belonging to the aforesaid conversion kernel */
            XMC_VADC_GROUP_ResultInit(adc->group, adc->result_reg_num, &vadc_gobal_result_config);

            /* Add channel into the Background Request Source Channel Select Register */
            XMC_VADC_GLOBAL_BackgroundAddChannelToSequence(VADC, (uint32_t)adc->group_num, (uint32_t)adc->channel_num);
        }
        /* Start conversion manually using load event trigger*/
        XMC_VADC_GLOBAL_BackgroundTriggerConversion(VADC);

        value = XMC_VADC_GROUP_GetResult(adc->group, adc->result_reg_num);
#else
// XMC1100 no ADC grouping
        if (!(adc->enabled))
        {
            /* Add a channel to the background source. */
            VADC->BRSSEL[ADC_CONVERSION_GROUP] = (uint32_t)(1U << adc->channel_num);
        }
        // Generates conversion request
        XMC_VADC_GLOBAL_BackgroundTriggerConversion(VADC);

        // Wait until conversion is ready
        while (((value = XMC_VADC_GLOBAL_GetDetailedResult(VADC)) & VADC_GLOBRES_VF_Msk) == 0u);
#endif
    }

    return ((value & VADC_GLOBRES_RESULT_Msk) >> (ADC_MAX_READ_RESOLUTION - _readResolution));
}

void analogWrite(uint8_t pin, uint16_t value)
{
    uint32_t compare_reg = 0;

    if (digitalPinHasPWM4(pin))
    {
        uint8_t pwm4_num = digitalPinToPWM4Num(pin);
        XMC_PWM4_t *pwm4 = &mapping_pwm4[pwm4_num];

        if (!(pwm4->enabled))
        {
            // Slice not yet initialized
            XMC_CCU4_SLICE_COMPARE_CONFIG_t pwm_config = {0};
            pwm_config.passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
            pwm_config.prescaler_initval = pwm4->prescaler;

            XMC_CCU4_Init(pwm4->ccu, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

            XMC_CCU4_SLICE_CompareInit(pwm4->slice, &pwm_config);

            XMC_CCU4_EnableClock(pwm4->ccu, pwm4->slice_num);

            XMC_CCU4_SLICE_SetTimerPeriodMatch(pwm4->slice, pwm4->period_timer_val);

            pwm4->enabled = ENABLED;
        }

        if (value != 0)
        {
            compare_reg  = (((value + 1) * pwm4->period_timer_val) >> _writeResolution);
        }

        XMC_CCU4_SLICE_SetTimerCompareMatch(pwm4->slice, compare_reg);

        XMC_CCU4_EnableShadowTransfer(pwm4->ccu, (CCU4_GCSS_S0SE_Msk << (4 * pwm4->slice_num)));

        XMC_GPIO_SetMode(pwm4->port_pin.port, pwm4->port_pin.pin, (XMC_GPIO_MODE_OUTPUT_PUSH_PULL | pwm4->port_mode));

        XMC_CCU4_SLICE_StartTimer(pwm4->slice);
    }
#ifdef CCU8V2
    else if (digitalPinHasPWM8(pin))
    {
        uint8_t pwm8_num = digitalPinToPWM8Num(pin);
        XMC_PWM8_t *pwm8 = &mapping_pwm8[pwm8_num];

        if (!(pwm8->enabled))
        {
            // Slice not yet initialized
            XMC_CCU8_SLICE_COMPARE_CONFIG_t pwm_config = {0};
            pwm_config.passive_level_out0 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
            pwm_config.passive_level_out1 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
            pwm_config.passive_level_out2 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
            pwm_config.passive_level_out3 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
            pwm_config.prescaler_initval = pwm8->prescaler;

            XMC_CCU8_Init(pwm8->ccu, XMC_CCU8_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

            XMC_CCU8_SLICE_CompareInit(pwm8->slice, &pwm_config);

            XMC_CCU8_EnableClock(pwm8->ccu, pwm8->slice_num);

            XMC_CCU8_SLICE_SetTimerPeriodMatch(pwm8->slice, pwm8->period_timer_val);

            pwm8->enabled = ENABLED;
        }

        if (value != 0)
        {
            compare_reg  = (((value + 1) * pwm8->period_timer_val) >> _writeResolution);
        }

        XMC_CCU8_SLICE_SetTimerCompareMatch(pwm8->slice, pwm8->slice_channel, compare_reg);

        XMC_CCU8_EnableShadowTransfer(pwm8->ccu, CCU8_GCSS_S0SE_Msk << (4 * pwm8->slice_num));

        XMC_GPIO_SetMode(pwm8->port_pin.port, pwm8->port_pin.pin, XMC_GPIO_MODE_OUTPUT_PUSH_PULL | pwm8->port_mode);

        XMC_CCU8_SLICE_StartTimer(pwm8->slice);
    }
#endif
#ifdef DAC
	else if(digitalPinHasDAC(pin))
	{
		uint8_t dac_num = digitalPinToDACNum(pin);
        XMC_ARD_DAC_t *dac = &(mapping_dac[dac_num]);
		XMC_DAC_Enable(dac->group);
		XMC_DAC_CH_EnableOutput(dac->group, dac->channel);
		XMC_DAC_CH_StartSingleValueMode(dac->group, dac->channel);
		uint16_t dacValue = map(value, 0, (0b10<<_writeResolution)-1, 0, (0b10<<dac->resolution)-1);
		XMC_DAC_CH_Write(dac->group, dac->channel, dacValue);
	}
#endif
    else // all the other pins
    {
        (value < 128) ?  digitalWrite(pin, LOW) : digitalWrite(pin, HIGH);
    }
}

extern int16_t setanalogWriteFrequency( uint8_t pin, uint32_t frequency )
{
	int16_t ret = -1;
	XMC_CCU4_SLICE_PRESCALER_t prescaler = (XMC_CCU4_SLICE_PRESCALER_t) 0;
	if(frequency < PCLK)
	{
		uint8_t exp = 0u;
		do
		{
			if(frequency > PCLK/(1u<<exp))
			{
				break;
			}
			exp++;
		}while(exp <= 12u);
		
		if (digitalPinHasPWM4(pin))
		{
			uint8_t pwm4_num = digitalPinToPWM4Num(pin);
			XMC_PWM4_t *pwm4 = &mapping_pwm4[pwm4_num];
					
			pwm4->prescaler = exp;
			pwm4->period_timer_val = PCLK/(frequency*(1u<<exp));
			
			if(pwm4->enabled == ENABLED)
			{
				// Disable pwm output
				pwm4->enabled = DISABLED;
				XMC_CCU4_SLICE_StartTimer(pwm4->slice);
			}
			
			ret = 0;
		}
#ifdef CCU8V2
		else if (digitalPinHasPWM8(pin))
		{
			uint8_t pwm8_num = digitalPinToPWM8Num(pin);
			XMC_PWM8_t *pwm8 = &mapping_pwm8[pwm8_num];
					
			pwm8->prescaler = exp;
			pwm8->period_timer_val = PCLK/(frequency*(1u<<exp));
			
			if(pwm8->enabled == ENABLED)
			{
				// Disable pwm output
				pwm8->enabled = DISABLED;
				XMC_CCU4_SLICE_StartTimer(pwm8->slice);
			}
			
				
			ret = 0;
		}
#endif
	}
	
	return ret;
}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************

