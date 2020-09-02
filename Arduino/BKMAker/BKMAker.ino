#include <DHT.h>
const int DHTPIN = A0; 
const int DHTTYPE = DHT22;

DHT dht(DHTPIN,DHTTYPE);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
   
}
void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("Adruino.");
  Serial.print("Nhiet do: ");
  Serial.println(t); 
  Serial.println("Do am:"); 
  Serial.println(h); 
  delay(450);
}
