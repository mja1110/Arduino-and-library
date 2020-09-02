/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
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
float goc;
float E,Output_first;
byte block1,block2;
volatile unsigned int temp, counter = 0;
//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=16, Ki=0.01, Kd=7;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
//  lcd.init();
//  lcd.backlight();
//  lcd.clear();
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
 
  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING);
  //initialize the variables we're linked to
  Input = goc;
  Setpoint = 30;
  TCCR1B = TCCR1B & 0b11111000 | 1;

  //turn the PID on
  
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(1);
   myPID.SetOutputLimits(0, 255);
}

void loop()
{
  if ( counter != temp ) {
    //float goc = 1.0 * counter * 360 / 1200;
    long x;
    
    x = constrain(counter, 0, 1200);
    goc = map(x, 0, 1200, 0, 359);
    if(goc>180) goc =0;
    temp = counter;
  }
  Input = map(goc,0,359,0,255);
  myPID.Compute();
  E=Setpoint-Output;
  Output_first=Output;
  if (Output > 255) Output = 255;
  if (Output < 0) Output = 0;
  if(Output_first != Output) block1=0;
  else block1=1;
  if(Output_first>0&&E>0) block2=1;
  else if(Output_first<0&&E<0) block2=0;
  if(block1&block2==0) Ki=0;
  else Ki=0.1;
  
  analogWrite(5, Output);
  digitalWrite(7,1);
  digitalWrite(8,0);
  
  Serial.println(goc);
    
//  lcd.print("Goc quay: ");
//  lcd.setCursor(10, 0);
//  lcd.print(goc);
  
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
