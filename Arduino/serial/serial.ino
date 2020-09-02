void readData()
{
 
  float wd = 0, ws = 0;
  for(int i = 0; i<20; i++)
  {
    ws = ws + analogRead(A7);
    wd = wd + analogRead(A8);
    delay(5);
  }
 
  wd = wd/20 * 360.0 / 1023.0;
  if (wd > 180) wd = 180 - (wd - 180);
  ws = ((ws/20 * 0.00478) - 0.4) / 1.6 * 32.4;
  if (ws < 0.2) ws = 0;
  Serial.print("wd = "); Serial.print(wd);
  Serial.print("     ws = "); Serial.print(ws);
  int rs = setLimit(ws);
  
  Serial.print("     v = ");
  Serial.println(rs);
 
}
int setLimit(float mWs)
{
  if ((mWs >= 0) && (mWs <= 12))
    return 60;
  else if (mWs <= 16)
    return 50;
  else if (mWs <= 18)
    return 40;
  else if (mWs <= 20)
    return 30;
  else if (mWs <= 22)
    return 20;
  else if (mWs <= 24)
    return 10;
  else if (mWs <= 10000)
    return 0;
  else return 1;
}
void setup() {
  Serial.begin(9600);
  
}

void loop() {

 readData();
 delay(3000);
}
