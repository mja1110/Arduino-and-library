int led=13;
unsigned long time=0;
unsigned long delayTime=1000;
void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  
}
void loop() {
  if (Serial.available())
  {
    time=millis();
    digitalWrite(led,HIGH);
    while (Serial.available())
    {
      Serial.read();
      delay(3);
    }
  
  Serial.println("Da nhan duoc");
  }
  if(millis()-time>delayTime) digitalWrite(led,LOW);
}
