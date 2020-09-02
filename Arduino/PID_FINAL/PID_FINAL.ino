#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#define Kp 20
#define Ki 0.0001
#define Kd 0
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

volatile unsigned int temp, counter = 0;
float T;
float Setpoint, goc;
double E, E1, E2;
double alpha, beta, gamma;
double Output, LastOutput;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  //  lcd.init();
  //  lcd.backlight();
  //  lcd.clear();
  //TCCR2B = TCCR2B & B11111000 | B00000001;
  TCCR1B = TCCR1B & 0b11111000 | 1;
  Setpoint = 30; goc = 0;
  E = 0; E1 = 0; E2 = 0;
  Output = 0; LastOutput = 0; T = 0.01;
  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING);
  Timer1.initialize(10000);
  Timer1.attachInterrupt(PID);

}
void loop() {
  //  lcd.clear();
  //  lcd.print("Goc quay: ");
  //  lcd.setCursor(10, 0);
  //  lcd.print(goc);
  //delay(10);
}
void ai0() {
  if (digitalRead(3) == LOW) {
    counter++;
  } else {
    counter--;
  }
}
void ai1() {
  if (digitalRead(2) == LOW) {
    counter--;
  } else {
    counter++;
  }
}
void PID()
{
  if ( counter != temp ) {
    //float vitri = 1.0 * counter * 360 / 1200;
    
    long x;
    x = constrain(counter, 0, 1200);
    goc = map(x, 0, 1200, 0, 359);
    if (goc > 180) goc = 0;
    temp = counter;
  }
  //vitri = map(goc, 0, 359, 0, 255);
  E = Setpoint - goc;
  alpha = 2 * T * Kp + Ki * T * T + 2 * Kd;
  beta = T * T * Ki - 4 * Kd - 2 * T * Kp;
  gamma = 2 * Kd;
  Output = (alpha * E + beta * E1 + gamma * E2 + 2 * T * LastOutput) / (2 * T);
  LastOutput = Output;
  E2 = E1;
  E1 = E;

  if (Output > 255) Output = 255;
  if (Output < 0) Output = 0;
  analogWrite(5, Output);
  digitalWrite(7, 1);
  digitalWrite(8, 0);

  Serial.println(goc);
  //  lcd.clear();
  //  lcd.print("Goc quay: ");
  //  lcd.setCursor(10, 0);
  //  lcd.print(goc);
}
