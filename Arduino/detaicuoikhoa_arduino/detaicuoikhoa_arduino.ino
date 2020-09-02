byte led = 13;
byte in1 = 4;
byte in2 = 5;
byte tocdo = 6 ;
byte latchPin = 8;
byte clockPin = 12;
byte dataPin = 11;
char number[10] = { 0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X90};
void setup() {
  pinMode(led, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(2, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), vatthe, RISING);
}
void dongco() {
  for (int i = 50; i <= 200; i += 5)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(
  }
}
void loop() {

}
