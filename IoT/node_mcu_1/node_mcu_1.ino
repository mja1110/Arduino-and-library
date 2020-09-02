#include<ESP8266WiFi.h>
void setup() {
  pinMode(D0, OUTPUT);
}

void loop() {
  digitalWrite(D0, LOW); //sang
  delay(1000);
  digitalWrite(D0, HIGH); // tat
  delay(1000);
}
