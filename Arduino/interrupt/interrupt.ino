

int mode;
void setup() {
  pinMode(3, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  attachInterrupt(1, chuyenmode, FALLING);

}

void loop() {
 digitalWrite(11,!digitalRead(11));
 if(mode==0) delay(1000);
 else delay(200);
  
    }
void chuyenmode()
{
mode=!mode;

}
