/*
  Simple Sleep Mode for XMC1100 series
  Demonstrates the use of an alarm to wake up an XMC1100 from sleep mode.
 */

#include <RTC.h>
#include <DeviceControlXMC.h>

// Create an RTC object
RTCClass RTC;
XMCClass XMC1100;

// Change these values to set the current initial time
const byte seconds = 0;
const byte minutes = 0;
const byte hours = 16;

/* Change these values to set the current initial date */
const byte day = 25;
const byte month = 9;
const byte year = 15;

int state = 0;  // 0- in active mode; 1 - changing mode; 2 - in sleep mode

void setup()
{
  Serial.begin(9600);
  RTC.begin();
  XMC1100.configureSleepMode(SLEEP_MODE,USIC_ON ,LEDT_OFF,CCU_ON,WDT_ON,FLASH_ON);

  RTC.setTime(hours, minutes, seconds);
  RTC.setDate(day, month, year);

  // Set alarm to go to sleep
  RTC.setAlarmTime(16, 0, 5);
  RTC.enableAlarm(RTC.ALARM);
  RTC.attachInterrupt(alarmMatch);
}

void loop()
{
  // Print time
  print2digits(RTC.getHours());
  Serial.print(":");
  print2digits(RTC.getMinutes());
  Serial.print(":");
  print2digits(RTC.getSeconds());
  Serial.println();
  delay(1000);

  if(state == 1){
    RTC.setAlarmTime(16, 0, 20);
    state = 2;  // Flag to wake up from sleep mode
    Serial.println("Entering sleep mode");
    delay(100);
    XMC1100.enterSleepMode();
  }
}

void print2digits(int number)
{
  if (number < 10) {
    Serial.print("0"); // Print a 0 before if the number is < than 10
  }
  Serial.print(number);
}

void alarmMatch()
{
  if(state == 2)  {
    XMC1100.enterActiveMode();
    Serial.println("Woke up");
  }
  else if(state == 0) // If device is in active state, set it to changing state
    state = 1;
}


