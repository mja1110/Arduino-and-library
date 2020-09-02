int number;
void setup() 
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}
void loop() 
{
  if (Serial.available())
  {
    String data = Serial.readString();
    number = data.toInt();
    if (number > 0 && number < 49)
    {
      digitalWrite(13, LOW);
      Serial.println(number);
    }
    if(number>50 && number<100)
    {
      digitalWrite(13,HIGH);
      Serial.println(number);
    }
  }
}
