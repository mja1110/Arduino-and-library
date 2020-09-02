#include <SoftwareSerial.h>
SoftwareSerial sim808(11, 10); //Arduino(RX), Arduino(TX)
//Arduino(RX) to SIM808(TX)
//Arduino(TX) to SIM808(RX)

//char phone_no[] = "+84903780253";// replace with your phone no.
unsigned long time1 = 0;
String data[5];
#define DEBUG true
#define NUT2 2
String state, timegps, latitude, longitude;

void setup() {

  sim808.begin(9600);
  Serial.begin(9600);
  delay(50);

  //getGPSLocation();

}

void loop() {

  if (Serial.available() > 0)
    sim808.write(Serial.read());
  if (sim808.available() > 0)
    Serial.write(sim808.read());

//  getGPSLocation();
//  delay(20000);
}

void getGPSLocation()
{


  sendData("AT+CGNSPWR=1", 1000, DEBUG); //Turn on GPS(GNSS - Global Navigation Satellite System)
  delay(50);
  sendData("AT+CGNSSEQ=RMC", 1000, DEBUG);

  delay(150);

  //--------------------- send SMS containing google map location---------
  sendTabData("AT+CGNSINF", 1000, DEBUG); //Get GPS info(location)
  if (state != 0) {
    
    Serial.println("Latitude  :" + latitude);
    Serial.println("Longitude  :" + longitude);

    //sim808.println("AT+CSCA=\"+84941369378\"");
    //sim808.println("AT+CMGS=\"84903780253\"");

    sim808.println("");

    delay(300);

    //sim808.print("http://maps.google.com/maps?q=loc:");
    sim808.print(latitude);
    sim808.print(",");
    sim808.print (longitude);
    delay(200);
    sim808.println((char)26); // End AT command with a ^Z, ASCII code 26
    delay(200);
    sim808.println();
    delay(20000);
    sim808.flush();
    Serial.println("GPS Location sent!");
  } else {
    Serial.println("GPS Initializing…");
  }
  //----------------------
}


void sendTabData(String command , const int timeout , boolean debug) {

  sim808.println(command);
  long int time = millis();
  int i = 0;

  while ((time + timeout) > millis()) {
    while (sim808.available()) {
      char c = sim808.read();
      if (c != ',') {
        data[i] += c;
        delay(100);
      } else {
        i++;
      }
      if (i == 5) {
        delay(100);
        goto exitL;
      }
    }
} exitL:
  if (debug) {
    state = data[1];
    timegps = data[2];
    latitude = data[3];
    longitude = data[4];
  }
}
String sendData (String command , const int timeout , boolean debug) {
  String response = "";
  sim808.println(command);
  long int time = millis();
  int i = 0;

  while ( (time + timeout ) > millis()) {
    while (sim808.available()) {
      char c = sim808.read();
      response += c;
    }
  }
  if (debug) {
    Serial.print(response);
  }
  return response;
}
