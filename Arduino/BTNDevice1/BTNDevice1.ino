
#include <SPI.h>
#include <SD.h>
#include "max6675.h"
#include "DS3231.h"
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <SHT1x.h>
#include "BTNThingSpeak.h"
#include "Sleep_n0m1.h"

Sleep sleep;

Time  t;

void setup()
{
#ifdef DEBUGER
  Serial.begin(9600);
  Serial.println("Initializing SD card...");
#endif
  /*------SETUP GPIO---*/
  pinMode(DTR, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, 1);
  pinMode(Network, OUTPUT);
  digitalWrite(Network, LOW);
  thermocouple1.setupMax6675();
  /*------SETUP RTC---*/
  rtc.begin();
#ifdef SETTIME
  rtc.setDOW(THURSDAY);     // Set Day-of-Week to SUNDAY
  rtc.setTime(17,01, 0);     // Set the time to 00:00:00 (24hr format)
  rtc.setDate(9, 5, 2019);   // Set the date to January 1st, 2014
#endif
  /*------SETUP SD CARD---*/
  Status.SDCard = sdFormat();
  Status.SDCard ? NetworkLed(4) : NetworkLed(2);
  /*------SET SLEEP SIM800---*/
  SIM.setTimeout(3000);
  SIM.begin(38400);
  delay(1000);
  SimDeepSleep();
  /*------SET INTERRUPT---*/
}

void loop()
{
  t = rtc.getTime();
#ifdef DEBUGER
  Serial.println("TIME: " + String(t.hour)+":" + String(t.min));
#endif
  if (t.min == 0 || t.min == 10 || t.min == 20 || t.min == 30 || t.min == 40 || t.min == 50)
  { 
    getDataStr();
    Status.StatusSendData = TCPSendData(2);
    Status.StatusSendData ? NetworkLed(5) : NetworkLed(2);
    DataStr.DataStringSave = Status.StatusSendData ? DataStr.DataStringSave + ",OK" : DataStr.DataStringSave + ",ENOR";
    saveData(DataStr.DataStringSave );
    enterSleep(60000);
    while (t.min == 0 || t.min == 10 || t.min == 20 || t.min == 30 || t.min == 40 || t.min == 50)
    {
      delay(5000);
      t = rtc.getTime();
    }
  }
  NetworkLed(1);
  enterSleep(30000);
}

/*.............................FUNTION TIMER AND INTERUPT........................................*/

void ResetBoard( uint8_t time)
{
  wdt_enable(time);
  while (1) {}
}

void timerSetup()
{
  TCCR1A = 0x00;
  TCNT1 = 49911;;
  TCCR1B = 0x05;
  TIMSK1 = 0x01; // Overflow interrupt enable
}

ISR (TIMER1_OVF_vect)
{
  if (Status.NetworkOn)
  {
    TCNT1 = 49911; //0x0000;
    digitalWrite(Network, !Status.StatusLed);
    Status.StatusLed = Status.StatusLed ? false : true;
  }
}

void enterSleep(int sleepTime)
{
  Serial.print("sleeping for ");
  Serial.println(sleepTime);
  delay(100); //delay to allow serial to fully print before sleep
  sleep.pwrDownMode(); //set sleep mode
  sleep.sleepDelay(sleepTime); //sleep for: sleepTime
}
