void setup() {
 pinMode(5, OUTPUT);//PWM
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
pinMode(13, OUTPUT);
Serial.begin(9600);
}

void loop() {
// digitalWrite(13,0);
// delay(500);
// digitalWrite(13,1);
// delay(500);
digitalWrite(7,1);
digitalWrite(8,0);
analogWrite(5,50);
//inA-8  inB-7
}
