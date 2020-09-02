#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

SoftwareSerial NodeMCU(D2,D3);//rx tx

void setup(){
	Serial.begin(9600);
	NodeMCU.begin(9600);

}

void loop(){
	String i = "abc";
	NodeMCU.print(i);
	//NodeMCU.println("\n");
	delay(3000);
  if(NodeMCU.available()) {
    String data = NodeMCU.readString();
    Serial.println(data);
  }
}
