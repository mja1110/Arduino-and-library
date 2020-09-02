/******************************************************************************
   Copyright 2018 Google
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 *****************************************************************************/
#include <CloudIoTCore.h>

#include "esp8266_mqtt.h"
#include <DHT.h>
#define DHTPIN D2
#define DHTTYPE DHT22

#ifndef LED_BUILTIN
#define LED_BUILTIN 16

#endif
DHT dht(DHTPIN, DHTTYPE);
char* id1 = "DHT_Sensor";
char* id2 = "Light";
char buffer[80];
void printLocalTime()
{
  time_t rawtime;
  struct tm * timeinfo;

  time (&rawtime);
  timeinfo = localtime (&rawtime);

  strftime (buffer, 80, "%d %B %Y %H:%M:%S %Z", timeinfo);
  //struct tm timeinfo;
  //time_t now = time(nullptr);
  Serial.println(buffer);
  //Serial.print(ctime(&now));
  //Serial.print(&timeinfo, " %d %B %Y %H:%M:%S ");
}


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
  setupCloudIoT(); // Creates globals for MQTT
  pinMode(LED_BUILTIN, OUTPUT);
}

unsigned long lastMillis = 0;

long messageSentAt = 0;
int dummyValue = 0;
char pubMessage1[128];
char pubMessage2[128];
void loop()
{
  mqtt->loop();
  delay(5); // <- fixes some issues with WiFi stability

  if (!mqttClient->connected())
  {
    ESP.wdtDisable();
    connect();
    ESP.wdtEnable(0);
  }

  // TODO: Replace with your code here
  /*
    if (millis() - lastMillis > 60000)
    {
    lastMillis = millis();
    publishTelemetry(getDefaultSensor());
    }
  */


  long now = millis();
  if (now - messageSentAt > 5000) {

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    // Compute heat index in Fahrenheit (the default)
  //  float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius (isFahreheit = false)
   // float hic = dht.computeHeatIndex(t, h, false);

//    Serial.print("Humidity: ");
//    Serial.print(h);
//    Serial.print("%  Temperature: ");
//    Serial.print(t);
//    Serial.print("°C ");
//    Serial.print(f);
//    Serial.println("°F ");
//    Serial.print(hic);
//    Serial.print("°C ");
//    Serial.print(hif);
//    Serial.println("°F");

    printLocalTime();
    //sprintf(pubMessage1, "{\"deviceID\":\"%s\",\"timestamp_DHT\":\"%s\",\"temperature\":\"%.1f\",\"humidity\":\"%.1f\"}", id1, buffer, t, h);  // {\"desired\":{\"foo\":\"%d\"}}}", dummyValue++);
    sprintf(pubMessage1, "{\"deviceID\":\"%s\",\"temperature\":\"%.1f\",\"humidity\":\"%.1f\"}", id1, t, h);
    Serial.print("Publishing message to topic ");
    Serial.println(pubMessage1);
    publishTelemetry(pubMessage1);
    //Serial.println("Published.");
    dummyValue++;
    Serial.print("so goi tin gui");
    Serial.println(dummyValue);
    messageSentAt = now;
  }

//  if (digitalRead(0) == 0)
//  {
//    //delay(50);
//    while (digitalRead(0) == 0);
//    //delay(50);
//    if (digitalRead(16) == HIGH)
//    {
//      printLocalTime();
//      sprintf(pubMessage2, "{\"deviceID\":\"%s\",\"status\":\"ON\",\"timestamp_Light\":\"%s\"}", id2, buffer);
//      Serial.print("Publishing message to topic ");
//      Serial.println(pubMessage2);
//      publishTelemetry(pubMessage2);
//      digitalWrite(16, LOW);
//    }
//    else
//    {
//      printLocalTime();
//      sprintf(pubMessage2, "{\"deviceID\":\"%s\",\"status\":\"OFF\",\"timestamp_Light\":\"%s\"}", id2, buffer);
//      Serial.print("Publishing message to topic ");
//      Serial.println(pubMessage2);
//      publishTelemetry(pubMessage2);
//      digitalWrite(16, HIGH);
//    }
//  }

}
//9h41
