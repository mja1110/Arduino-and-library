#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
// 0 -65535  673
// xanh 2 ,trang 3, do 5v, den gnd
volatile unsigned int temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder
byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};
void setup() {
  pinMode(5, OUTPUT);//PWM
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); // internal pullup input pin 2

  pinMode(3, INPUT_PULLUP); // internalเป็น pullup input pin 3
  //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(0, ai0, RISING);

  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(1, ai1, RISING);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  // lcd.createChar(1, degree);
}
void loop() {
  digitalWrite(7, 1);
  digitalWrite(8, 0);
  analogWrite(5, 70);
  // Send the value of counter
  if ( counter != temp ) {
    //float goc = 1.0 * counter * 360 / 1200;
    long x;
    float goc;
    x = constrain(counter, 0, 1200);
    goc = map(x, 0, 1200, 0, 359);
    Serial.println (counter); Serial.println (goc);
    lcd.clear();
    lcd.print("Goc quay: ");
    lcd.setCursor(10, 0);
    lcd.print(goc);
    temp = counter;
  }
}
void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if (digitalRead(3) == LOW) {
    counter++;
  } else {
    counter--;
  }
}
void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if (digitalRead(2) == LOW) {
    counter--;
  } else {
    counter++;
  }
}








































//void loop()
//{
//  if (Serial.available()) {
//    lcd.cursor();
//    lcd.blink();
//
//    lcd.write(Serial.read());
//  }
//}
