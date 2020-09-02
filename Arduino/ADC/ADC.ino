float Vout;
float nhietdo;
void setup() {
Serial.begin(9600);

}

void loop() {
  int value=analogRead(A0);
Serial.println(value);
Vout=(float(value)*5/1024);
nhietdo=Vout*100;
Serial.print("nhiet do: ");
Serial.println(nhietdo);




delay(1000);
}
