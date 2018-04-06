
/*
  Simple RTC Alarm for XMC4700 Relax Kit V1
  Demonstrates the use of an alarm to wake up an XMC4700 from Hibernate mode   
  19 June 2017
 */

#include <RTC.h>
#include <DeviceControlXMC.h>
/* Create an rtc object */
 RTCClass rtc;
 XMCClass xmc;
/* Change these values to set the current initial time */
 const byte seconds = 0;
 const byte minutes = 0;
 const byte hours = 16;

/* Change these values to set the current initial date */
 const byte day = 25;
 const byte month = 9;
 const byte year = 15;
 int outLED = LED1;
void setup()
{
   Serial.begin(9600);
   
   pinMode(outLED,OUTPUT);
   digitalWrite(outLED, LOW);
   // Start RTC and then configure hibernate on XMC
   rtc.begin();
   xmc.configureHibernate(WAKEUP_ON_RTC);

   rtc.setTime(hours, minutes, seconds);
   rtc.setDate(day, month, year);
  
   //Set alarm to wake up from hibernate 
   rtc.setAlarmTime(16, 0, 3);
   rtc.enableAlarm(rtc.ALARM);
   rtc.attachInterrupt(alarmMatch);
}

void loop()
{
  // Enter hibernate and wait for alarm to wake up
   xmc.enterHibernate(EXTERNAL);
   delay(100); // to allow time for device to wake up
}

void alarmMatch()
{
    digitalWrite(outLED, HIGH);
}

