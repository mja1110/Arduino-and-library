#include <ESP8266WiFi.h>

#define ssid  "Anderson"
#define password  "1234567890"
#define host  "tapit.vn"
#define port  80

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.print(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println("Connecting to " + (String)host + ":" + port);
  WiFiClient client;
  if (!client.connect(host, port))
  {
    Serial.println("Connection failed");
    return;
  }

  String url = "/";
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print("GET " + url + " HTTP/1.0\r\n" +
               "Host: " + host + "\r\n\r\n");
  Serial.println("Request sent");
  unsigned long timeout = millis();
  while (client.available() == 0)
  {
    if (millis() - timeout > 5000)
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(2000);
      return;
    }
  }

  Serial.println("Receiving from remote serve");
  while (client.available())
  {
    String line = client.readStringUntil('\n');
    if ((line.indexOf("Date") != -1) ||
        (line.indexOf("Connection") != -1) ||
        (line.indexOf("Expires") != -1))
      Serial.println(line);
  }

  Serial.println();
  Serial.println("Closing connection");
  client.stop();

  delay(1000000);

}
