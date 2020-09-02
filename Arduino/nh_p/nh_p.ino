#include <EEPROM.h>
void setup() {
  Serial.begin(9600);
 
    String a;String b;
   EEPROM.get(0,a);EEPROM.get(100,b);
   Serial.println(a);
   Serial.println(b);
}

void loop() {
  if (Serial.available())
  {
    String data = Serial.readString();
    int index = data.indexOf("_");
    String ten= data.substring(0,index);
    String std=data.substring(index+1);
    EEPROM.put(0,ten);EEPROM.put(100,std);
    String a;String b;
   EEPROM.get(0,a);EEPROM.get(100,b);
   Serial.println(a);
   Serial.println(b);
   }
  
}
