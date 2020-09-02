
void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, daotrangthai, FALLING);
}
void loop()
{
  if (Serial.available())
  {
    String data = Serial.readString();
    if (data == "BATDEN") digitalWrite(13, HIGH);
    else if (data == "TATDEN") digitalWrite(13, LOW);
  }
}
void daotrangthai()
{
  digitalWrite(13, !digitalRead(13));
  if (digitalRead(13) == 1) Serial.print("LED ON");
  if (digitalRead(13) == 0) Serial.print("LED OFF");
}
