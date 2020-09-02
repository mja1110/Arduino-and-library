#include <SoftwareSerial.h>

SoftwareSerial sim808(2, 3); //Arduino(RX), Arduino(TX)
void ShowSerialData()
{
  while (sim808.available() != 0)
    Serial.write(sim808.read());
  delay(5000);

}

void sendThingspeak() {
  sim808.println("AT");
  delay(1000);

  sim808.println("AT+CPIN?");
  delay(1000);

  sim808.println("AT+CREG?");
  delay(1000);

  sim808.println("AT+CGATT?");
  delay(1000);

  sim808.println("AT+CIPSHUT");
  delay(1000);

  sim808.println("AT+CIPSTATUS");
  delay(2000);

  sim808.println("AT+CIPMUX=0");
  delay(2000);

  ShowSerialData();

  sim808.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);

  ShowSerialData();

  sim808.println("AT+CIICR");//bring up wireless connection
  delay(3000);

  ShowSerialData();

  sim808.println("AT+CIFSR");//get local IP adress
  delay(2000);

  ShowSerialData();

  sim808.println("AT+CIPSPRT=0");
  delay(3000);

  ShowSerialData();

  sim808.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);

  ShowSerialData();

  sim808.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();

  String str = "GET https://api.thingspeak.com/update?api_key=N48O1H3YEMZU1NTU&field1=2";
  Serial.println(str);
  sim808.println(str);//begin send data to remote server

  delay(4000);
  ShowSerialData();

  sim808.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet
  sim808.println();

  ShowSerialData();

  sim808.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
}


void setup() {

  sim808.begin(9600);
  Serial.begin(9600);
  Serial.println("Arduino MQTT Tutorial, Valetron Systems @www.raviyp.com ");
  delay(3000);
}




void loop() {

  sendThingspeak();

}
