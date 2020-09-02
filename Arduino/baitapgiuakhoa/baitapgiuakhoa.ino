
char number[10] = { 0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X90};
volatile int counter;
int reading;
int chiso, chisocu;
void hienthi(int n)
{
  for (int i = 4; i <= 11; i++)
  {
    int x = number[n] & (1 << (i - 4));
    digitalWrite(i, x);
  }
}
void tang()
{
  if (digitalRead(2) == 0)
  {
    counter++;
    delayMicroseconds(10000);
    if (counter >= 9) counter = 9;
    hienthi(counter);
  }
}
void giam()
{
  if (digitalRead(3) == 0)
  {
    counter--;
    delayMicroseconds(10000);
    if (counter <= 0) counter = 0;
    hienthi(counter);
  }
}
int chisocuabientro()
{
  if ((reading >= 0) && (reading <= 102)) chiso = 0;
  if ((reading > 102) && (reading <= 204)) chiso = 1;
  if ((reading > 204) && (reading <= 306)) chiso = 2;
  if ((reading > 306) && (reading <= 408)) chiso = 3;
  if ((reading > 408) && (reading <= 510)) chiso = 4;
  if ((reading > 510) && (reading <= 612)) chiso = 5;
  if ((reading > 612) && (reading <= 714)) chiso = 6;
  if ((reading > 714) && (reading <= 816)) chiso = 7;
  if ((reading > 816) && (reading <= 918)) chiso = 8;
  if ((reading > 918) && (reading <= 1023)) chiso = 9;
  return (chiso);
}
void setup()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  for (int i = 4; i <= 11; i++)
  {
    pinMode(i, OUTPUT);
  }
  attachInterrupt(0, tang, FALLING);
  attachInterrupt(1, giam, FALLING);
  Serial.begin(9600);
}
void loop()
{
  if (Serial.available())
  {
    String  data = Serial.readString();         //char data=Serial.read();
    counter = data.toInt();                           //int a = data-48;
    if ((counter >= 0) && (counter <= 9)) hienthi(counter);
    else Serial.print("Nhap ngoai khoang");
  }
 reading = analogRead(A0);
  chiso = chisocuabientro();
  if (chiso != chisocu)
  {
    hienthi(chiso);
    chisocu = chiso;
    counter = chisocu;
  }
}
/*  nếu rút biến trở thì
