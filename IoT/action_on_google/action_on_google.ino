#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
 
#define LedPin 16
 
// Set these to run example.
#define FIREBASE_HOST "first-test-26815.firebaseio.com"
#define FIREBASE_AUTH "ExfFf42AyYcAkaAr6BnTcltaczraPr6iTgyzvKhA"
#define WIFI_SSID "Anderson"
#define WIFI_PASSWORD "11111111"
 
void setup() {
  pinMode(LedPin, OUTPUT);
  Serial.begin(115200);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ") ;
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/ESP8266");
}
void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }
 
  if (Firebase.available()) {
    FirebaseObject event = Firebase.readEvent();
    String eventType = event.getString("type");
    Serial.print("event: ");
    Serial.println(eventType);
    if (eventType == "put") {
      String path = event.getString("path");
      String data = event.getString("data");
      Serial.println(String("data: ") + data);
      if (path.equals("/light/value")) {
        if (data.equals("off")) {
          digitalWrite(LedPin, HIGH);
        } else {
          digitalWrite(LedPin, LOW);
        }
      }
    }
  }
}
