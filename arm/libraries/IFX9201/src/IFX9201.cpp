/**
 * IFX9201.cpp - Library for Arduino to control the IFX9201 H-Bridge.
 * 
 * The IFX9201 is a general purpose 6A H-Bridge for industrial applications, home appliance and building 
 * automation, power tools battery management and medical applications, designed for the control of small 
 * DC motors and inductive loads.
 * 
 * Have a look at the application note/datasheet for more information.
 * 
 * Copyright (c) 2018 Infineon Technologies AG
 * 
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the 
 * following conditions are met:   
 *                                                                              
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
 * disclaimer.                        
 * 
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following 
 * disclaimer in the documentation and/or other materials provided with the distribution.                       
 * 
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote 
 * products derived from this software without specific prior written permission.                                           
 *                                                                              
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE  
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR  
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   
 */
 
/*!	\file IFX9201.cpp
 *	\brief This file defines functions and predefined instances from IFX9201.h
 */

#include "IFX9201.h"
#include "./util/IFX9201_conf.h"


IFX9201::IFX9201(void)
{
	m_Mode = IFX9201Mode_PWM;
	m_PWMFreq = 0u;
	m_SPIsettings = SPISettings(1000000u, MSBFIRST, SPI_MODE1);
}

void IFX9201::begin(SPIClass &bus, uint8_t pinSlaveSelect, uint8_t pinDirection, uint8_t pinPWM, uint8_t pinDisable)
{
	m_Mode = IFX9201Mode_SPI;
	m_bus = &bus;
	
	m_bus->begin();
	m_bus->setBitOrder(MSBFIRST); 
	m_bus->setClockDivider(SPI_CLOCK_DIV16);
	m_bus->setDataMode(SPI_MODE1);

	m_SlaveSelect = pinSlaveSelect;
	m_Disable = pinDisable;
	m_Direction = pinDirection;
	m_PWM = pinPWM;
	
	begin();
	
	setCTRLReg(IFX9201__CTRL_SIN_MSK);
}

void IFX9201::begin(uint8_t pinDirection, uint8_t pinPWM, uint8_t pinDisable)
{
	m_Mode = IFX9201Mode_PWM;
	
	m_Disable = pinDisable;
	m_Direction = pinDirection;
	m_PWM = pinPWM;

	begin();
}

void IFX9201::begin(void)
{
	if(m_Mode == IFX9201Mode_SPI){
		pinMode(m_SlaveSelect, OUTPUT);
		digitalWrite(m_SlaveSelect, HIGH);
	} 

	pinMode(m_Disable, OUTPUT);
	pinMode(m_Direction, OUTPUT);
	pinMode(m_PWM, OUTPUT);
	
	digitalWrite(m_PWM, LOW);
	digitalWrite(m_Direction, LOW);
	digitalWrite(m_Disable, LOW);
	
	setPWMFreqency(IFX9201__DEFAULT_PWM_FREQUENCY);
}

void IFX9201::setPWMFreqency(uint16_t freq)
{
	if(freq <= IFX9201__MAX_PWM_FREQ)
	{
		m_PWMFreq = freq;
		setAnalogWriteFrequency(m_PWM, m_PWMFreq);
	}
}

uint8_t IFX9201::forwards(void)
{
	uint8_t ret = IFX9201__NO_ERROR;
	if(m_Mode == IFX9201Mode_SPI)
	{
		ret = setCTRLReg(IFX9201__CTRL_SIN_MSK | IFX9201__CTRL_SEN_MSK | IFX9201__CTRL_SDIR_MSK | IFX9201__CTRL_SPWM_MSK);
	}
	else
	{
		ret = forwards(IFX9201__DEFAULT_DUTY_CYCLE);
	}
	return ret;
}

uint8_t IFX9201::backwards(void)
{
	uint8_t ret = IFX9201__NO_ERROR;
	if(m_Mode == IFX9201Mode_SPI)
	{
		ret = setCTRLReg(IFX9201__CTRL_SIN_MSK | IFX9201__CTRL_SEN_MSK | IFX9201__CTRL_SPWM_MSK);
	}
	else
	{
		ret = backwards(IFX9201__DEFAULT_DUTY_CYCLE);
	}
	return ret;
}

uint8_t IFX9201::forwards(uint8_t duty_cycle)
{
	uint8_t ret = IFX9201__NO_ERROR;
	if(m_Mode == IFX9201Mode_SPI)
	{
		ret = IFX9201__ILLEGAL_OPERATION_ERROR;
	}
	else
	{
		digitalWrite(m_Direction, HIGH);
		analogWrite(m_PWM, DutyCycleToanlogWriteValue(duty_cycle));
		digitalWrite(m_Disable, LOW);
	}
	return ret;
}

uint8_t IFX9201::backwards(uint8_t duty_cycle)
{
	uint8_t ret = IFX9201__NO_ERROR;
	if(m_Mode == IFX9201Mode_SPI)
	{
		ret = IFX9201__ILLEGAL_OPERATION_ERROR;
	}
	else
	{
		digitalWrite(m_Direction, LOW);
		analogWrite(m_PWM, DutyCycleToanlogWriteValue(duty_cycle));
		digitalWrite(m_Disable, LOW);
	}
	return ret;
}

uint8_t IFX9201::stop(void)
{
	uint8_t ret = IFX9201__NO_ERROR;
	if(m_Mode == IFX9201Mode_SPI)
	{
		ret = setCTRLReg(IFX9201__CTRL_SIN_MSK);
	}
	else
	{
		digitalWrite(m_Direction, LOW);
		analogWrite(m_PWM, 0u);
		digitalWrite(m_Disable, HIGH);
	}
	return ret;
}

void IFX9201::end(void)
{
	pinMode(m_Disable, INPUT);
	pinMode(m_SlaveSelect, INPUT);
	pinMode(m_Direction, INPUT);
	pinMode(m_PWM, INPUT);
}
		
uint8_t IFX9201::getDIAReg(void)
{
	(void)SPItransfer(IFX9201__RD_DIA);
	return SPItransfer(IFX9201__RD_DIA);
}

uint8_t IFX9201::getREVReg(void)
{
	(void)SPItransfer(IFX9201__RD_REV);
	return SPItransfer(IFX9201__RD_REV);
}

uint8_t IFX9201::getCRTLReg(void)
{
	(void)SPItransfer(IFX9201__RD_CTRL);
	return SPItransfer(IFX9201__RD_CTRL);
}

uint8_t IFX9201::setCTRLReg(uint8_t data_out)
{
	uint8_t ret = IFX9201__NO_ERROR;
	if(m_Mode == IFX9201Mode_SPI)
	{
		SPItransfer(IFX9201__WR_CTRL | (IFX9201__CTRL_DATA_MSK & data_out));
		
		if( (SPItransfer(IFX9201__RD_CTRL) & IFX9201__CTRL_DATA_MSK) != (data_out & IFX9201__CTRL_DATA_MSK))
		{	
			ret = IFX9201__SPI_WRITE_ERROR;
		}
	}
	else
	{
		ret = IFX9201__MODE_ERROR;
	}
	
	return ret;
}
void IFX9201::resetDIAReg(void)
{
	if(m_Mode == IFX9201Mode_SPI)
	{
		(void)SPItransfer(IFX9201__RES_DIA);
	}
}

uint8_t IFX9201::SPItransfer(uint8_t data_out)
{
	uint8_t data_in = 0x00u;
	
	m_bus->beginTransaction(m_SPIsettings);
	
	digitalWrite(m_SlaveSelect, LOW);
	data_in = m_bus->transfer(data_out);
	digitalWrite(m_SlaveSelect, HIGH);
	
	return data_in;
}


uint8_t IFX9201::DutyCycleToanlogWriteValue(uint8_t duty_cycle)
{
	uint8_t ret = ( (duty_cycle >= 100u) ? 255u : (uint8_t)((double)duty_cycle * 2.55) );
	return ret;
}
