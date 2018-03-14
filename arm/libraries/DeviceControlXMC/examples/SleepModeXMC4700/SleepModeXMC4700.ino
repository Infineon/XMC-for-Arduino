
/*
  Simple Sleep Mode for XMC4700 Relax Kit V1
  Demonstrates the ability to control peripherals on sleep mode.
  LED2 will blink fast on active mode. If CCU4 is ON in sleep mode, LED2 will blink slower (because of slower clock) while in sleep mode. 
  If CCU is OFF in sleep mode, LED2 will stop blinking, until device wakes up.
  Demonstrates the use of an alarm to wake up an XMC4700 from sleep mode.
  19 June 2017
 */

#include <RTC.h>
#include <XMC_DeviceControl.h>
#include "utility/timer.h"
#include <xmc_gpio.h>

/* Create an rtc object */
 RTCClass rtc;
 XMCClass xmc;

#define LED P5_8

/* Change these values to set the current initial time */
 const byte seconds = 0;
 const byte minutes = 0;
 const byte hours = 16;

/* Change these values to set the current initial date */
 const byte day = 25;
 const byte month = 9;
 const byte year = 15;

 int state = 0;  // 0- in active mode; 1 - changing mode; 2 - in sleep mode
 bool led_state = false;
void setup()
{
  Serial.begin(9600);
  rtc.begin();
  xmc.configureSleepMode(SLEEP_MODE,SYSCLK_FOFI,USB_OFF,SDMMC_OFF,ETH_OFF,EBU_OFF,CCU_ON,WDT_ON,FLASH_ON,PLL_ON,VCO_ON);
  pinMode(LED2,OUTPUT);

  TIMER_Init(0);  // Timer init, used to toggle LED2

  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(day, month, year);

  //Set alarm to go to sleep
  rtc.setAlarmTime(16, 0, 5);
  rtc.enableAlarm(rtc.ALARM);
  rtc.attachInterrupt(alarmMatch);
}

void loop()
{
  TIMER_Start(8000000U);  //

  if(state == 1){
    rtc.setAlarmTime(16, 0, 20);  // time to wake up
    state = 2;            // flag to wake up from sleep mode
    Serial.println("Entering sleep mode");
    delay(100);
    xmc.enterSleepMode();
  }
}
void alarmMatch()
{
  if(state == 2)  {
    xmc.enterActiveMode();
    Serial.println("Woke up");
  }
  else if(state == 0)
    state = 1;
}

void timer_cb(void)
{
  if(led_state == false)  {
      led_state = true;
      digitalWrite(LED2, HIGH);
    }
  else {
       led_state = false;
      digitalWrite(LED2, LOW);
    }

  TIMER_Stop();
  TIMER_Clear();
  TIMER_Start(8000000U);
}

