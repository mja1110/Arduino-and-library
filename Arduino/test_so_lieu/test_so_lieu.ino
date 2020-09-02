long counter,temp;
float goc;
void setup() {
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING);
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
void loop() {
  if ( counter != temp )
  {
    long x;
    x = constrain(counter, 0, 1200);
    goc = map(x, 0, 1200, 0, 359);
    
    
    temp = counter;
  }
  analogWrite(5,200);
    digitalWrite(7,1);
    digitalWrite(8,0);
    Serial.println(goc);
}
