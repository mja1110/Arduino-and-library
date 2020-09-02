#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define Kp 100

#define Kd 12
static float Ki;
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

unsigned long time1 = 0;
volatile unsigned int temp, counter = 0;
float T;
int Setpoint, goc;
double E, E1, E2;
double alpha, beta, gamma;
double Output, LastOutput, Output_first;
byte block1, block2;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  lcd.init();
  lcd.backlight();

  TCCR2B = TCCR2B & B11111000 | B00000001;
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
  time1 = millis();
  if (millis() - time1 < 50)
  {
    lcd.clear();
    lcd.print("Goc: ");
    lcd.setCursor(4, 0);
    lcd.print(goc);
    lcd.setCursor(8, 0);
    lcd.print("Kp:");
    lcd.setCursor(12, 0);
    lcd.print(Kp);
    lcd.setCursor(8, 1);
    lcd.print("Ki:");
    lcd.setCursor(12, 1);
    lcd.print(Ki);
    lcd.setCursor(8, 2);
    lcd.print("Kd:");
    lcd.setCursor(12, 2);
    lcd.print(Kd);
    lcd.setCursor(0, 3);
    lcd.print("Setpoint: ");
    lcd.setCursor(10, 3);
    lcd.print(Setpoint);
    time1 = millis();
  }
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
  Output_first = Output;
  if (Output > 255) Output = 255;
  if (Output < 0) Output = 0;
  if (Output_first != Output) block1 = 0;
  else block1 = 1;
  if (Output_first > 0 && E > 0) block2 = 1;
  else if (Output_first < 0 && E < 0) block2 = 0;
  if (block1 & block2 == 0) Ki = 0;
  else Ki = 0.5;
  analogWrite(5, Output);
  digitalWrite(7, 1);
  digitalWrite(8, 0);
  Serial.println(goc);
}
