#include<TimerOne.h>

#define PWM 5
#define DIR1 7
#define DIR2 8

#define Kp 0.01
#define Kd 0.0002
#define Ki 0.04

volatile unsigned int temp, counter = 0;
float T;
float vitri, vitridat;
double E, E1, E2;
double alpha, beta, gamma;
double Output, LastOutput;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(PWM, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  //TCCR2B = TCCR2B & B11111000 | B00000001; // for PWM frequency of 31372.55 Hz
  vitridat = 30; vitri = 0;
  E = 0; E1 = 0; E2 = 0;
  Output = 0; LastOutput = 0; T = 0.001;
  Serial.begin(9600);
  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING);
  Timer1.initialize(10000);  //don vi us
  Timer1.attachInterrupt(PID);
}

void loop() {

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

  vitri = 1.0 * counter * 360 / 1200;
  //xung = 0;
  E = vitridat - vitri;
  alpha = 2 * T * Kp + Ki * T * T + 2 * Kd;
  beta = T * T * Ki - 4 * Kd - 2 * T * Kp;
  gamma = 2 * Kd;
  Output = (alpha * E + beta * E1 + gamma * E2 + 2 * T * LastOutput) / (2 * T);
  LastOutput = Output;

  E2 = E1;
  E1 = E;


 
    analogWrite(DIR1, 1);
    analogWrite(DIR2, 0);
    analogWrite(PWM, Output);
  
  Serial.println(vitri);
  //  digitalWrite(DIR1, HIGH);
  //  digitalWrite(DIR2, LOW);
  //  analogWrite(PWM, abs(Output));
  //  Serial.println(tocdo);
}
