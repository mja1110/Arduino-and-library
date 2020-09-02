#include <ESP8266WiFi.h>
void ICACHE_RAM_ATTR daotrangthai();
void setup() 
{
 pinMode(0,INPUT);
 pinMode(16,OUTPUT);
 attachInterrupt(digitalPinToInterrupt(0), daotrangthai,FALLING);
}
void loop() 
{
}
void daotrangthai()
{
  while(digitalRead(0)==0);     //chong nhieu
  digitalWrite(16,!digitalRead(16));
}
