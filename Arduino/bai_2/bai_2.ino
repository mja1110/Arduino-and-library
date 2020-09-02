void setup()
{
  pinMode(10, INPUT_PULLUP);
  pinMode(12, OUTPUT);
}

void loop() {
    if (digitalRead(10) == 0)
    {
      for(int i=0;i<10;i++)
      {
      digitalWrite(12, 1);
      delay(100);
      digitalWrite(12, 0);
      delay(100);
      }
    }
   else digitalWrite(12,0);
}
