/*
   Simple RTC for XMC4700 Relax Kit V1
   Demonstrates the use of the RTC library for the XMC4700
 */

#include <RTC.h>

/* Create an rtc object */
 RTCClass rtc;

/* Change these values to set the current initial time */
 const byte seconds = 0;
 const byte minutes = 0;
 const byte hours = 16;

/* Change these values to set the current initial date */
 const byte day = 15;
 const byte month = 6;
 const byte year = 15;

void setup()
{
   Serial.begin(9600);

   rtc.begin(); // initialize RTC

   // Set the time
   rtc.setHours(hours);
   rtc.setMinutes(minutes);
   rtc.setSeconds(seconds);

   // Set the date
   rtc.setDay(day);
   rtc.setMonth(month);
   rtc.setYear(year);

   // you can use also
   //rtc.setTime(hours, minutes, seconds);
   //rtc.setDate(day, month, year);
}

void loop()
{
   // Print date...
   print2digits(rtc.getDay());
   Serial.print("/");
   print2digits(rtc.getMonth());
   Serial.print("/");
   print2digits(rtc.getYear());
   Serial.print(" ");

   // ...and time
   print2digits(rtc.getHours());
   Serial.print(":");
   print2digits(rtc.getMinutes());
   Serial.print(":");
   print2digits(rtc.getSeconds());

   Serial.println();

   delay(1000);
}



void print2digits(int number) {
   if (number < 10) {
     Serial.print("0"); // print a 0 before if the number is < than 10
   }
   Serial.print(number);
}


