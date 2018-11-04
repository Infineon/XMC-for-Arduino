/*
   Simple RTC Alarm for XMC Boards
   Demonstrates how to set an RTC alarm for the XMC4700 Relax Kit V1
 */

 /*  
  Board Check 
  This library can currently only be used with the XMC4700 Relax Kit 
  If you modify the library to work with other XMC versions, remove the following lines 
*/ 
#if (UC_FAMILY != XMC4)
#error This XMC board is not supported, only XMC4700 Relax Kit is supported 
#endif 
// End of Board Check 

#include <RTC.h>

/* Create an rtc object */
 RTCClass rtc;

/* Change these values to set the current initial time */
 const byte seconds = 0;
 const byte minutes = 0;
 const byte hours = 16;

/* Change these values to set the current initial date */
 const byte day = 25;
 const byte month = 9;
 const byte year = 15;

void setup()
{
   Serial.begin(9600);

   rtc.begin(); // initialize RTC 24H format

   rtc.setTime(hours, minutes, seconds);
   rtc.setDate(day, month, year);

   rtc.setAlarmTime(16, 0, 10);
   rtc.enableAlarm(rtc.ALARM);
   
   rtc.attachInterrupt(alarmMatch);
}

void loop()
{

   // Print time
   print2digits(rtc.getHours());
   Serial.print(":");
   print2digits(rtc.getMinutes());
   Serial.print(":");
   print2digits(rtc.getSeconds());

   Serial.println();

   delay(1000);
}

void alarmMatch()
{
   Serial.println("Alarm Match!");
}

void print2digits(int number) {
   if (number < 10) {
     Serial.print("0"); // print a 0 before if the number is < than 10
   }
   Serial.print(number);
}