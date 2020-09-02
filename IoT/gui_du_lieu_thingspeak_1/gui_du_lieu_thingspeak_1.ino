#include <ESP8266WiFi.h>
String APIWriteKey = "PZFDC8J0AFKCLST8";
String ssid = "Anderson";
String password = "11111111";

String host = "api.thingspeak.com";
const int port = 80;
byte value = 0;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return; //tro ve ham loop
  }
  else
  {
    if (value == 0) value = 1;
    else value = 0;
    client.print(String("GET ")+ "/update?api_key=" + APIWriteKey + "&field1=" + value + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n\r\n");
    Serial.println("Request sent");

  }
  /* client.print("GET " + url + " HTTP/1.1\r\n" +
                  "Host: " + host + "\r\n" +
                  "Connection: close\r\n\r\n");
      Serial.println("request sent");*/
  client.stop();

  delay(15000); // execute once every 5 minutes, don't flood remote service
}
