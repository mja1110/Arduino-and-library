void setup() {
  pinMode(16,OUTPUT);
  Serial.begin(9600);
}
void loop() {
 if(Serial.available())
 {
  String a;
  a=Serial.readString();
  if(a=="on") digitalWrite(16,LOW);
  else if(a=="off") digitalWrite(16,HIGH);
 }
 
}
