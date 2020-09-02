#include<ESP8266WiFi.h>
String ssid = "Anderson";
String password = "11111111";
String host = "api.thingspeak.com";
String APIWriteKey = "PZFDC8J0AFKCLST8";
const byte port = 80;
byte value;
byte flag;
void ICACHE_RAM_ATTR daotrangthai()
{
  if (digitalRead(0) == 0)
  {
    flag = 1;
    while (digitalRead(0) == 0);
    if (digitalRead(16) == 0)
    {
      digitalWrite(16, 1);
      value = 0;
    }
    else
    {
      digitalWrite(16, 0);
      value = 1;
    }
  }
}
void setup() {
  pinMode(16, OUTPUT);
  pinMode(0, INPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(0), daotrangthai, FALLING);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println(String("Connecting to ") + host + " ,port: " + port);
  WiFiClient client;
  if (!client.connect(host, port))
  {
    Serial.println("Connection failed");
    return;
  }
  else
  {
    if (flag == 1)
    {
      client.print(String("GET ") + "/update?api_key=" + APIWriteKey + "&field1=" + value + " HTTP/1.0\r\n"
                   + "Host: " + host + "\r\n\r\n");
      Serial.println("Request sent");
      client.stop();
      delay(15000);
      flag = 0;
    }

  }

}
