
#include <EEPROM.h>
void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 1024; i++)
  {
    int value = EEPROM.read(i);
    Serial.print("i = ");
    Serial.print(i);
    Serial.print(" : value = ");
    Serial.println(value);
  }
  //  EEPROM.write(i, i);
}

void loop()
{
}
