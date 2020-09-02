#include <SoftwareSerial.h>
SoftwareSerial sim808(11, 10); //Arduino(RX), Arduino(TX)
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
const char MQTTTopic[30] = "valetron";
const char MQTTProtocolName[10] = "MQIsdp";
const char MQTTLVL = 0x03;
const char MQTTFlags = 0xC2;
const unsigned int MQTTKeepAlive = 60;
const char MQTTUsername[30] = "zfvbdvzp";
const char MQTTPassword[35] = "eURfEh_8w9AH";
const char MQTTQOS = 0x00;
const char MQTTPacketID = 0x0001;
void setup() {
  //pinMode(led, OUTPUT);
  Serial.begin(9600);
  sim808.begin(9600);
  Serial.println("Arduino MQTT Tutorial, Valetron Systems @www.raviyp.com ");
  delay(3000);
}
void SendConnectPacket(void) {
  sim808.print("\r\nAT+CIPSEND\r\n");
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
  
  sim808.write(0x1A);
}

void loop() {
  
  sim808.print("AT+CIPSHUT\r\n");
 
  delay(1000);
  sim808.print("AT+CSTT=\"www\",\"\",\"\"\r\n");
  delay(1000);
  sim808.print("AT+CIPMODE=0\r\n");
  delay(1000);
  sim808.print("AT+CIICR\r\n");
  delay(5000);
  sim808.print("AT+CIPSTART=\"TCP\",\"tailor.cloudmqtt.com\",\"14392\"\r\n");
  delay(4000);
  SendConnectPacket();
  
  while (1) {
    delay(5000);
    SendPublishPacket();
    Counter++; 
  }
}
