#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(3,2);

void setup(){
	
	Serial.begin(9600);
	ArduinoUno.begin(9600);

}

void loop(){
	
	if(ArduinoUno.available()>0){
	String val = ArduinoUno.readString();
	ArduinoUno.print("123");
	Serial.println(val);
	
}
delay(30);
}
