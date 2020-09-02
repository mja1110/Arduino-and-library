#include <ESP8266WiFi.h>
String APIWriteKey = "PZFDC8J0AFKCLST8";
String ssid = "IoT-Research";
String password = "Tapit168";

String host = "api.thingspeak.com";
const int port = 80;
byte value = 0;


void setup() {
  pinMode(16, OUTPUT);
  pinMode(0, INPUT);
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
    if (digitalRead(0) == 0)
    {
      delay(50);
      while (digitalRead(0) == 0);
      delay(50);
      if (digitalRead(16) == 1)
      {
        digitalWrite(16, 0);
        value = 1;
      }
      else
      {
        digitalWrite(16, 1);
        value = 0;
      }



      client.print("GET /update?api_key=" + APIWriteKey + "&field1=" + String(value) + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n\r\n");
      Serial.println("Request sent");
      client.stop();

      delay(15000); // execute once every 5 minutes, don't flood remote service
    }



  }
}
