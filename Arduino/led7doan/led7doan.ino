int a;
char number[10] = { 0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X90};

void setup() {
  Serial.begin(9600);

  for (int i = 2; i <= 9; i++)
  {
    pinMode(i, OUTPUT);
  }
}
void loop() {
  if (Serial.available())                               
  {
    String  data = Serial.readString();         //char data=Serial.read();
    a = data.toInt();                           //int a = data-48;
    hienthi(a);
  }
}
void hienthi(int n)
{
  for (int i = 2 ;i <= 9; i++)
  {
    int x = number[n] & (1 << (i - 2));
    digitalWrite(i, x);
  }
}
