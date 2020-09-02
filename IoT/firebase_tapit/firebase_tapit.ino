#include <ArduinoJson.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "YOUR_FIREBASE_PROJECT.firebaseio.com"
#define FIREBASE_AUTH "YOUR_FIREBASE_DATABASE_SECRET"
#define WIFI_SSID "YOUR_WIFI_AP"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

FirebaseData firebaseData;

void setup()
{
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["id"] = "001";
  root["firstName"] = "John";
  root["lastName"] = "Peter";
  root["address"] = "quangnam";

  root.prettyPrintTo(Serial);
  Serial.println();

  String jsonStr = "";
  root.printTo(jsonStr);

  String path = "/TAPIT_IOT_GROUP";

  if (Firebase.setJSON(firebaseData, path + "/Test", jsonStr))
  {
    Serial.println("PUT JSON --------------------");
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  String jsonRecvStr = "";
  if (Firebase.getJSON(firebaseData, path + "/Test"))
  {
    Serial.println("GET JSON -------------------------");
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("VALUE: ");
    jsonRecvStr = firebaseData.jsonData();
    Serial.println(jsonRecvStr);
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  char jsonParse[jsonRecvStr.length() + 1];
  for (int i = 0; i <= jsonRecvStr.length(); i++)
  {
    jsonParse[i] = jsonRecvStr[i];
  }

  JsonObject& rootRecv = jsonBuffer.parseObject(jsonParse);
  if (!rootRecv.success())
  {
    Serial.println("parseObject() failed");
    return;
  }
  int id = rootRecv["id"];
  Serial.println(id);
  const char* lastName = rootRecv["lastName"];
  Serial.println(lastName);
  const char* address = rootRecv["address"];
  Serial.println(address);
}

void loop()
{

}
