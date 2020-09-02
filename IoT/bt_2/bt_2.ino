#include <ESP8266WiFi.h>
void ICACHE_RAM_ATTR daotrangthai();
void setup() {
  pinMode(0, INPUT);
  pinMode(16, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(0),daotrangthai,FALLING);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0)
  {
    String data;
    data = Serial.readString();
    if (data == "LED ON") digitalWrite(16, LOW);
    else if (data == "LED OFF") digitalWrite(16, HIGH);
  }
}
void daotrangthai() {
  if(digitalRead(0)==0)
  {
    if(digitalRead(16)==0) 
    {
      digitalWrite(16,HIGH);
      Serial.println("LED OFF");
    }
    else 
    {
      digitalWrite(16,LOW);
      Serial.println("LED ON");
    }
  }
}
