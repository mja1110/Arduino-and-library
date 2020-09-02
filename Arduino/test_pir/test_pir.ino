void setup() {
  pinMode(2,OUTPUT);
  Serial.begin(9600);
}

void loop() {
 Serial.println(digitalRead(2));
}
