#include <ThingSpeak.h>

#include<ESP8266WiFi.h>
String apiWritekey = "4XRVQ65VRCAD9VIT"; //mã Writekey ta thay vao day
const char* ssid = "Anderson"; //ten wifi
const char* password = "1234567890"; //mat khau

const char* serve = "api.thingspeak.com";
float resolution = 3.3 / 1023; //3.3 is the supply volt & 1023 is max analog read value
WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();
}

void loop() {
  float temp = (analogRead(A0) * resolution) * 100;

  if (client.connect(serve, 80))
  {
    String tsData = apiWritekey;
    tsData += "&field1=";
    tsData += String(temp);
    tsData += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X_THINGSPEAKAPIKEY: "+apiWritekey+"\n");
    client.print("Content-Type: appilication/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n"); //the 2 carriage returns indicate closing of Header fields & starting of data
    client.print(tsData);

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println("uploaded to Thingspeak serve...");
  }
  client.stop();

  Serial.println("Waiting to upload next reading...");
  Serial.println();
  //thingspeak needs minimum 15 sec delay between updates
  delay(15000);
}
