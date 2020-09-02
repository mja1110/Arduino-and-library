void setup() {
  pinMode(16, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  if (Serial.available())
  {
    String data;
    data = Serial.readString();
    if (data.indexOf("LEDON") != -1) digitalWrite(16, LOW);
    else if (data.indexOf("LEDOFF") != -1) digitalWrite(16, HIGH);
    else if (data.indexOf("LEDBLINK") != -1)
    {
      for (int i = 0; i < 5; i++)
      {
        digitalWrite(16, LOW); delay(2000);
        digitalWrite(16, HIGH); delay(2000);
      }
    }
  }

}
