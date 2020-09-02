#include<SoftwareSerial.h>

extern uint8_t SmallFont[];

#define rxPin 11
#define txPin 10

SoftwareSerial mySerial(rxPin, txPin);

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);

}

void loop() {
  if(mySerial.available()) Serial.write(mySerial.read());

  if(Serial.available()) mySerial.write(Serial.read());

}
