#ifndef _SW_SPI_H
#define _SW_SPI_H

#include <Arduino.h>
#include <binary.h>

const uint8_t MSBFIRST_BITS[] = { 
    B10000000,
    B01000000,
    B00100000,
    B00010000,
    B00001000,
    B00000100,
    B00000010,
    B00000001
};

const uint8_t LSBFIRST_BITS[] = { 
    B00000001,
    B00000010,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B10000000
};

#define SW_SPI_CLOCK_DIV2_DELAY_HALF_PERIOD_REDUCED     asm volatile("nop")                                               
#define SW_SPI_CLOCK_DIV2_DELAY_HALF_PERIOD             asm volatile("nop");\
                                                            asm volatile("nop")  
                                                            
#define SW_SPI_CLOCK_DIV4_DELAY_HALF_PERIOD_REDUCED     asm volatile("nop");\
                                                            asm volatile("nop")                                               
#define SW_SPI_CLOCK_DIV4_DELAY_HALF_PERIOD             asm volatile("nop");\
                                                            asm volatile("nop");\
                                                            asm volatile("nop");\
                                                            asm volatile("nop") 
                                                            
#define SW_SPI_CLOCK_DIV8_DELAY_HALF_PERIOD_REDUCED     asm volatile("nop");\
                                                            asm volatile("nop");\
                                                            asm volatile("nop");\
                                                            asm volatile("nop");\
                                                            asm volatile("nop");\
                                                            asm volatile("nop")                                               
#define SW_SPI_CLOCK_DIV8_DELAY_HALF_PERIOD             asm volatile("nop");\
                                                            asm volatile("nop");\
                                                            asm volatile("nop");\
                                                            asm volatile("nop");\
                                                            asm volatile("nop");\
                                                            asm volatile("nop");\
                                                            asm volatile("nop");\
                                                            asm volatile("nop") 

static inline uint8_t SW_SPI_transfer_clock_div_2(uint8_t mosi, uint8_t miso, uint8_t clk, uint8_t data, bool delay, uint8_t dir)
{
    uint8_t data_in = 0;
    
    // Time critical
    noInterrupts();
    if(dir == LSBFIRST)
    {
        if(delay)
        {
            digitalToggle(clk);
            SW_SPI_CLOCK_DIV2_DELAY_HALF_PERIOD_REDUCED;
        }
  
        for(uint8_t i = 0; i <= 7 ; i++)
        {
            digitalToggle(clk);
            digitalWrite(mosi, (data & LSBFIRST_BITS[i]));  
            SW_SPI_CLOCK_DIV2_DELAY_HALF_PERIOD;
            digitalToggle(clk);
            data_in |= (digitalRead(miso) << i);
            SW_SPI_CLOCK_DIV2_DELAY_HALF_PERIOD_REDUCED;
        }
        
        uint8_t temp = data_in;
        data_in = 0;
        for(uint8_t i = 0; i <= 7; i++)
        {
            data_in |= ((temp & LSBFIRST_BITS[i]) << (7-i));
        }
        
        if(delay)
        {
            digitalToggle(clk);
        }
    }
    else
    {
        if(delay)
        {
            digitalToggle(clk);
            SW_SPI_CLOCK_DIV2_DELAY_HALF_PERIOD_REDUCED;
        }
  
        for(uint8_t i = 0; i <= 7 ; i++)
        {
            digitalToggle(clk);
            digitalWrite(mosi, (data & MSBFIRST_BITS[i]));  
            SW_SPI_CLOCK_DIV2_DELAY_HALF_PERIOD;
            digitalToggle(clk);
            data_in |= (digitalRead(miso) << i);
            SW_SPI_CLOCK_DIV2_DELAY_HALF_PERIOD_REDUCED;
        }
        
        if(delay)
        {
            digitalToggle(clk);
        }
    }
    interrupts();
    return data_in;
}

static inline uint8_t SW_SPI_transfer_clock_div_4(uint8_t mosi, uint8_t miso, uint8_t clk, uint8_t data, bool delay, uint8_t dir)
{
    uint8_t data_in = 0;
    
    // Time critical
    noInterrupts();
    if(dir == LSBFIRST)
    {
        if(delay)
        {
            digitalToggle(clk);
            SW_SPI_CLOCK_DIV4_DELAY_HALF_PERIOD_REDUCED;
        }
  
        for(uint8_t i = 0; i <= 7 ; i++)
        {
            digitalToggle(clk);
            digitalWrite(mosi, (data & LSBFIRST_BITS[i]));  
            SW_SPI_CLOCK_DIV4_DELAY_HALF_PERIOD;
            digitalToggle(clk);
            data_in |= (digitalRead(miso) << i);
            SW_SPI_CLOCK_DIV4_DELAY_HALF_PERIOD_REDUCED;
        }
        
        uint8_t temp = data_in;
        data_in = 0;
        for(uint8_t i = 0; i <= 7; i++)
        {
            data_in |= ((temp & LSBFIRST_BITS[i]) << (7-i));
        }
        
        if(delay)
        {
            digitalToggle(clk);
        }
    }
    else
    {
        if(delay)
        {
            digitalToggle(clk);
            SW_SPI_CLOCK_DIV4_DELAY_HALF_PERIOD_REDUCED;
        }
  
        for(uint8_t i = 0; i <= 7 ; i++)
        {
            digitalToggle(clk);
            digitalWrite(mosi, (data & MSBFIRST_BITS[i]));  
            SW_SPI_CLOCK_DIV4_DELAY_HALF_PERIOD;
            digitalToggle(clk);
            data_in |= (digitalRead(miso) << i);
            SW_SPI_CLOCK_DIV4_DELAY_HALF_PERIOD_REDUCED;
        }
        
        if(delay)
        {
            digitalToggle(clk);
        }
    }
    interrupts();
    return data_in;
}

static inline uint8_t SW_SPI_transfer_clock_div_8(uint8_t mosi, uint8_t miso, uint8_t clk, uint8_t data, bool delay, uint8_t dir)
{
    uint8_t data_in = 0;
    
    // Time critical
    noInterrupts();
    if(dir == LSBFIRST)
    {
        if(delay)
        {
            digitalToggle(clk);
            SW_SPI_CLOCK_DIV8_DELAY_HALF_PERIOD_REDUCED;
        }
  
        for(uint8_t i = 0; i <= 7 ; i++)
        {
            digitalToggle(clk);
            digitalWrite(mosi, (data & LSBFIRST_BITS[i]));  
            SW_SPI_CLOCK_DIV8_DELAY_HALF_PERIOD;
            digitalToggle(clk);
            data_in |= (digitalRead(miso) << i);
            SW_SPI_CLOCK_DIV8_DELAY_HALF_PERIOD_REDUCED;
        }
        
        uint8_t temp = data_in;
        data_in = 0;
        for(uint8_t i = 0; i <= 7; i++)
        {
            data_in |= ((temp & LSBFIRST_BITS[i]) << (7-i));
        }
        
        if(delay)
        {
            digitalToggle(clk);
        }
    }
    else
    {
        if(delay)
        {
            digitalToggle(clk);
            SW_SPI_CLOCK_DIV8_DELAY_HALF_PERIOD_REDUCED;
        }
  
        for(uint8_t i = 0; i <= 7 ; i++)
        {
            digitalToggle(clk);
            digitalWrite(mosi, (data & MSBFIRST_BITS[i]));  
            SW_SPI_CLOCK_DIV8_DELAY_HALF_PERIOD;
            digitalToggle(clk);
            data_in |= (digitalRead(miso) << i);
            SW_SPI_CLOCK_DIV8_DELAY_HALF_PERIOD_REDUCED;
        }
        
        if(delay)
        {
            digitalToggle(clk);
        }
    }
    interrupts();
    return data_in;
}

static inline uint8_t SW_SPI_transfer_clock_div_16(uint8_t mosi, uint8_t miso, uint8_t clk, uint8_t data, bool delay, uint8_t dir)
{}

static inline uint8_t SW_SPI_transfer_clock_div_32(uint8_t mosi, uint8_t miso, uint8_t clk, uint8_t data, bool delay, uint8_t dir)
{}

static inline uint8_t SW_SPI_transfer_clock_div_64(uint8_t mosi, uint8_t miso, uint8_t clk, uint8_t data, bool delay, uint8_t dir)
{}

static inline uint8_t SW_SPI_transfer_clock_div_128(uint8_t mosi, uint8_t miso, uint8_t clk, uint8_t data, bool delay, uint8_t dir)
{}
                                                            
#endif
