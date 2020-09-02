#include <ESP8266WiFi.h>
void setup() 
{
  pinMode(0, INPUT);
  pinMode(16, OUTPUT);
}
void loop() 
{
  if (digitalRead(0) == 0) 
  {
    delay(50);     //nhieu suon xuong
    while (digitalRead(0) == 0);   //neu digitalRead(0)==0 thi khong lam gi ca
    delay(50);    //nhieu suon len
    if (digitalRead(16) == 0) digitalWrite(16, 1);     // digitalWrite(16,!digitalRead(16));
    else digitalWrite(16,0);                           //thay 2 dong tren
  }
}
