#include <SoftwareSerial.h>
SoftwareSerial sim808(11, 10); //Arduino(RX), Arduino(TX)
//Arduino(RX) to SIM808(TX)
//Arduino(TX) to SIM808(RX)

String loc;

unsigned int Counter = 0;
unsigned long datalength, CheckSum, RLength;
unsigned short topiclength;
unsigned char topic[30];
char str[250];
unsigned char encodedByte;
int X;
unsigned short MQTTProtocolNameLength;
unsigned short MQTTClientIDLength;
unsigned short MQTTUsernameLength;
unsigned short MQTTPasswordLength;

const char MQTTHost[30] = "tailor.cloudmqtt.com";
const char MQTTPort[10] = "14392";
const char MQTTClientID[20] = "ABCDSEF";
const char MQTTTopic[30] = "location";
const char MQTTProtocolName[10] = "MQIsdp";
const char MQTTLVL = 0x03;
const char MQTTFlags = 0xC2;
const unsigned int MQTTKeepAlive = 60;
const char MQTTUsername[30] = "zfvbdvzp";
const char MQTTPassword[35] = "eURfEh_8w9AH";
const char MQTTQOS = 0x00;
const char MQTTPacketID = 0x0001;


unsigned long time1 = 0;
String data[5];
#define DEBUG true
#define NUT2 2
String state, timegps, latitude, longitude;



void getGPSLocation()
{
  sendData("AT+CGNSPWR=1", 1000, DEBUG); //Turn on GPS(GNSS - Global Navigation Satellite System)
  delay(50);
  sendData("AT+CGNSSEQ=RMC", 1000, DEBUG);

  delay(150);

  //--------------------- send SMS containing google map location---------
  sendTabData("AT+CGNSINF", 1000, DEBUG); //Get GPS info(location)
  if (state != 0) {
    //Serial.println("State  :" + state);
    // Serial.println("Time  :" + timegps);
    Serial.println("Latitude  :" + latitude);
    Serial.println("Longitude  :" + longitude);



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
    delay(10000);
    sim808.flush();
    Serial.println("GPS Location sent! Check your mobile phone…");
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

void SendConnectPacket(void) {
  sim808.print("\r\nAT+CIPSEND\r\n");
  Serial.print("\r\nAT+CIPSEND\r\n");
  delay(3000);
  
  sim808.write(0x10);
  
  MQTTProtocolNameLength = strlen(MQTTProtocolName);
  MQTTClientIDLength = strlen(MQTTClientID);
  MQTTUsernameLength = strlen(MQTTUsername);
  MQTTPasswordLength = strlen(MQTTPassword);
  datalength = MQTTProtocolNameLength + 2 + 4 + MQTTClientIDLength + 2 + MQTTUsernameLength + 2 + MQTTPasswordLength + 2;
  X = datalength;
  do {
    encodedByte = X % 128;
    X = X / 128;
    if (X > 0) {
      encodedByte |= 128;
    }
    sim808.write(encodedByte);
  }
  while (X > 0);
  sim808.write(MQTTProtocolNameLength >> 8);
  sim808.write(MQTTProtocolNameLength & 0xFF);
  sim808.print(MQTTProtocolName);
  
  sim808.write(MQTTLVL); // LVL
  sim808.write(MQTTFlags); // Flags
  sim808.write(MQTTKeepAlive >> 8);
  sim808.write(MQTTKeepAlive & 0xFF);
  
  sim808.write(MQTTClientIDLength >> 8);
  sim808.write(MQTTClientIDLength & 0xFF);
  sim808.print(MQTTClientID);
  
  sim808.write(MQTTUsernameLength >> 8);
  sim808.write(MQTTUsernameLength & 0xFF);
  sim808.print(MQTTUsername);
  
  sim808.write(MQTTPasswordLength >> 8);
  sim808.write(MQTTPasswordLength & 0xFF);
  sim808.print(MQTTPassword);
  
  sim808.write(0x1A);
}
void SendPublishPacket(void) {
  sim808.print("\r\nAT+CIPSEND\r\n");
  delay(3000);
  
  memset(str, 0, 250);
  
  topiclength = sprintf((char * ) topic, MQTTTopic);
  datalength = sprintf((char * ) str, "%s%u", topic, Counter);
  delay(1000);
  sim808.write(0x30);
  X = datalength + 2;
  do {
    encodedByte = X % 128;
    X = X / 128;
    if (X > 0) {
      encodedByte |= 128;
    }
    sim808.write(encodedByte);
  }
  while (X > 0);
  sim808.write(topiclength >> 8);
  sim808.write(topiclength & 0xFF);
  sim808.print(str);
  Serial.print(str);
  
  sim808.write(0x1A);
}


void setup() {

  sim808.begin(9600);
  Serial.begin(9600);
  Serial.println("Arduino MQTT Tutorial, Valetron Systems @www.raviyp.com ");
  delay(3000);
  //delay(50);
  //getGPSLocation();
}

void loop() {

  if (Serial.available() > 0)
    sim808.write(Serial.read());
  if (sim808.available() > 0)
    Serial.write(sim808.read());

  //    delay(30000);
  sim808.print("AT+CIPSHUT\r\n");
  Serial.print("AT+CIPSHUT\r\n");
  delay(1000);
  sim808.print("AT+CSTT=\"www\",\"\",\"\"\r\n");
  Serial.print("AT+CSTT=\"www\",\"\",\"\"\r\n");
  delay(1000);
  sim808.print("AT+CIPMODE=0\r\n");
  Serial.print("AT+CIPMODE=0\r\n");
  delay(1000);
  sim808.print("AT+CIICR\r\n");
  Serial.print("AT+CIICR\r\n");
  delay(5000);
  sim808.print("AT+CIPSTART=\"TCP\",\"tailor.cloudmqtt.com\",\"14392\"\r\n");
  Serial.print("AT+CIPSTART=\"TCP\",\"tailor.cloudmqtt.com\",\"14392\"\r\n");
  delay(4000);
  SendConnectPacket();
  
  while (1) {
    delay(5000);
    //loc="13";
    SendPublishPacket();
    Counter++; 
  }


}
