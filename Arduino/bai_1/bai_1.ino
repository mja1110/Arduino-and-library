void setup()
{
  pinMode(10, INPUT);
  pinMode(12, OUTPUT);
}

void loop()
{
  if (digitalRead(10) == 0) digitalWrite(12, HIGH);
  else digitalWrite(12, LOW);
  delay(10);
}
