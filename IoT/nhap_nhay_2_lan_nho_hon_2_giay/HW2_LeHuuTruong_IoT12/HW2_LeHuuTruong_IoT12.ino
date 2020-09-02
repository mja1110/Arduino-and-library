byte dem = 0;
unsigned long time1 = 0;
unsigned long time2 = 0;
int interval = 2000;
void setup() {
  pinMode(16, OUTPUT);
  pinMode(0, INPUT);
  Serial.begin(9600);
}
void loop() {
  if (digitalRead(0) == 0)
  {
    delay(50);
    while (digitalRead(0) == 0);
    delay(50);
    dem++;
    if (dem == 1) time1 = millis();
    if (dem == 2)
    {
      dem = 0;
      if (millis() - time1 < interval)digitalWrite(16, !digitalRead(16));
    }
  }
}
