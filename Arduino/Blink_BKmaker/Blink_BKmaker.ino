///*
//  Blink
//
//  Turns an LED on for one second, then off for one second, repeatedly.
//
//  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
//  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
//  the correct LED pin independent of which board is used.
//  If you want to know what pin the on-board LED is connected to on your Arduino
//  model, check the Technical Specs of your board at:
//  https://www.arduino.cc/en/Main/Products
//
//  modified 8 May 2014
//  by Scott Fitzgerald
//  modified 2 Sep 2016
//  by Arturo Guadalupi
//  modified 8 Sep 2016
//  by Colby Newman
//
//  This example code is in the public domain.
//
//  http://www.arduino.cc/en/Tutorial/Blink
//*/
//
//// the setup function runs once when you press reset or power the board
//void setup() {
//  // initialize digital pin LED_BUILTIN as an output.
// pinMode(13, OUTPUT);
//    pinMode(A0, INPUT);
//    Serial.begin(9600);
//}
//// the loop function runs over and over again forever
//void loop() {
//  int reading = analogRead(A0);
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(100);
//  // wait for a second
//  Serial.println();
//}
int volatile dem=0;
void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  for (int i = 9; i <= 13; i++)
  {
    pinMode(i, OUTPUT);
  }
  attachInterrupt(0, ngat, FALLING);

}
void loop()
{
  if(digitalRead(2)==0) 
  {
    while (digitalRead(2)==0){}
    dem++;
  }
  Serial.println(dem);
  if (dem == 1) digitalWrite(13, 1);
  else if (dem == 2) digitalWrite(12, 1);
  else if (dem == 3) digitalWrite(11, 1);
  else if (dem == 4) digitalWrite(10, 1);
  else if (dem == 5) digitalWrite(9, 1);
  else if (dem == 6)
  {
    for (int i = 9; i <= 13; i++)
    {
      digitalWrite(i, 0);
    }
  }
  else if (dem == 7) dem = 0;
}
void ngat()
{
  if(digitalRead(2)==0)
  dem++;
}
