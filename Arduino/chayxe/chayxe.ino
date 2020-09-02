void setup() {
  pinMode(6, OUTPUT);
   pinMode(7, OUTPUT);
     pinMode(8, OUTPUT);
       pinMode(9, OUTPUT);
}
void loop() {
digitalWrite(6, 1);  
digitalWrite(7, 0);
digitalWrite(8, 1);
digitalWrite(9, 0);
analogWrite(5,150);
analogWrite(10,150);


delay(500);
digitalWrite(6, 1);
digitalWrite(7, 0);
digitalWrite(8, 0);
digitalWrite(9, 1);
analogWrite(5,120);
analogWrite(10,120);



delay(1000);
digitalWrite(6, 0);
digitalWrite(7, 1);
digitalWrite(8, 0);
digitalWrite(9, 1);
analogWrite(5,200);
analogWrite(10,200);


delay(1000);
digitalWrite(6, 0);
digitalWrite(7, 1);
digitalWrite(8, 1);
digitalWrite(9, 0);
analogWrite(5,100);
analogWrite(10,100);



delay(700);
}
