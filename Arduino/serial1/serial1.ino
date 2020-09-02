void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available())
  {
    
    String data = Serial.readString();
    if (data.indexOf("on") != -1)  digitalWrite(13, 1);
   
    else if (data.indexOf("off") != -1) digitalWrite(13, 0);
  }
}
