#include <ESP8266WiFi.h>
byte dem = 0;
void setup() {
  pinMode(0, INPUT);
  pinMode(16, OUTPUT);
}
void loop() {
  if(digitalRead(0)==0)
  {
    delay(50);
    while(digitalRead(0)==0);
    delay(50);
    dem=dem+1;
    if(dem%2==0) 
    {
      if(digitalRead(16)==0) digitalWrite(16,HIGH);
      else digitalWrite(16,LOW);
      dem=0;
    }
  }

}
