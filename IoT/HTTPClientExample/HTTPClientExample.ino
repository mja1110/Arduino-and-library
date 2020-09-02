#include <ESP8266WiFi.h>

const char* ssid = "Anderson";
const char* password = "11111111";

const char* host = "daotao.dut.udn.vn";
const int port = 80;

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

  String url = "/";
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print("GET " + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +             
               "Connection: close\r\n\r\n");
  Serial.println("request sent");
  
  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(2000);
      return;// tro ve ham loop
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }

  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();

  delay(5000); // execute once every 5 minutes, don't flood remote service
}
