#include<EEPROM.h>
void setup()
{
  Serial.begin(9600);
  String ten = "le";
  EEPROM.put(300,ten);
  String data;
  EEPROM.get(300,data);
  Serial.print(data);
}
void loop()
{
  
}
