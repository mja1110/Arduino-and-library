




#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


//DynamicJsonBuffer jb;
//JsonObject& obj=jb.createObject()

//FirebaseData eventData;

String FIREBASE_PATH = "ESP8266/light/state";
String FIREBASE_HOST = "test-5c566.firebaseio.com";
String FIREBASE_AUTH = "X1sEWDBKU6zZskR7HKKVLTOfEzCRpd3bHUh1cJeS";
String ssid = "Anderson";
String password = "1234567890";
String FIREBASE_STATE;
byte state;
byte lastState = 0;
byte ledState;

void setup() {

  pinMode(16, OUTPUT);
  pinMode(0, INPUT);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/ESP8266");
}

void loop()
{
  if (Firebase.available())
  {
    FirebaseObject event = Firebase.readEvent();
    String eventType = event.getString("type");
    eventType.toLowerCase();

    Serial.print("event: ");
    Serial.println(eventType);
    Serial.println(String("path: ") + event.getString("path"));
    Serial.print("data: ");
    Serial.println(event.getString("data"));







    /*FIREBASE_STATE = Firebase.getString(FIREBASE_PATH);
      if (FIREBASE_STATE == "on") digitalWrite(16, LOW);
      if (FIREBASE_STATE == "off") digitalWrite(16, HIGH);
      if (digitalRead(0) == 0)
      {
      delay(50);
      while (digitalRead(0) == 0);
      delay(50);
      if (digitalRead(16) == 0)
      {
        digitalWrite(16, HIGH);
        Firebase.set(FIREBASE_PATH, "off");
        Serial.println("LED OFF");
      }
      else if (digitalRead(16) == 1)
      {
        digitalWrite(16, LOW);
        Firebase.set(FIREBASE_PATH, "on");
        Serial.println("LED ON");
      }
      }
    */
  }
}
