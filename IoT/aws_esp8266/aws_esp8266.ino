// Example of the different modes of the X.509 validation options
// in the WiFiClientBearSSL object
//
// Jul 2019 by Taejun Kim at www.kist.ac.kr

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <time.h>
#include <DHT.h>
#define DHTPIN D2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
String temp_str; //see last code block below use these to convert the float that you get back from DHT to a string =str
String hum_str;
char temp[50];
char hum[50];
const char *ssid = "IoT-Research";  // 와이파이 이름
const char *pass = "Tapit168";      // 와이파이 비밀번호
const char *thingId = "TAPIT-IoT";          // 사물 이름 (thing ID)
const char *host = "a3oxog0rr6kidc-ats.iot.us-west-2.amazonaws.com"; // AWS IoT Core 주소
const char *pubTopic1 = "$aws/things/TAPIT-IoT/shadow/update";

const char *subTopic1 = "$aws/things/TAPIT-IoT/shadow/update/delta";



// 사물 인증서 (파일 이름: xxxxxxxxxx-certificate.pem.crt)
const char cert_str[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUCG5xcjDruyHOOAd6LKDx0HCnMg4wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIwMDEyMTE4MTMz
MFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAL2vy6mYLmtIzpXACFUq
PCKFqt//uJmu2wSKCzy01XkvH4G5x6jLvzCyMhT1v/zTotBxvjsm1yRNHf7Qv5ZF
ZKpnObc7Kt3CdOvhD/WpvB6VpAcBGIUj1mRcsr0UVgYGQLvKx7sewiUXt15D0zWJ
2VQor3lfqRFV5E7QdQk6DxqfvlKnaKk6I8RwDDnOD8qOfCW+BOLhlS+C5JHq1JCs
odi+KPZxER7fne6/D6HqDZPPBp+M25M/MPBhTgfme3xECBmKteol0ULCEX+H5ydu
tOPfJXDkJMRrnetw6r57soNRhIfvzEnyGzVOHBRSxkCIVpLPreJp/y6ynb8lbIq7
AxMCAwEAAaNgMF4wHwYDVR0jBBgwFoAUqdyJcU+fbJANaoenrCGBj6jV3D0wHQYD
VR0OBBYEFJLIjPhe4AHvLSY3CVHJZgMxu/WUMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBDQH+75SV8B2P5ddZfKACuFLoK
v5FoewJ7cmnV+Lfn6MQe8I+dTp9DDLmhnf4ZHpjjvRDpPlJpzwFNoJfonDYIVcfb
m2/UMucYEICHU2JCDY9PnfQAAN2fSFEXke/NhWjaM36p3yBS3+O4iHwIoZ3uABLr
A+YMXwOIA3R06LKuR+bwDN+lq6KNPzOlJSL10pbMFF7ZoJ1O8O/6Nih5vxFzGo3j
2l8P07rc5NbLv/iojxcnPZR4hZ9QwhZqyZv8jv6bKhb+5eFzLwS+2u5P3baNtsB0
AQWLSOY1XlLLObbJn/S044fzbOxyFffk6mmzEoFw5AUoyyqXzpCVNQ/QKRf6
-----END CERTIFICATE-----
)EOF";
// 사물 인증서 프라이빗 키 (파일 이름: xxxxxxxxxx-private.pem.key)
const char key_str[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAva/LqZgua0jOlcAIVSo8IoWq3/+4ma7bBIoLPLTVeS8fgbnH
qMu/MLIyFPW//NOi0HG+OybXJE0d/tC/lkVkqmc5tzsq3cJ06+EP9am8HpWkBwEY
hSPWZFyyvRRWBgZAu8rHux7CJRe3XkPTNYnZVCiveV+pEVXkTtB1CToPGp++Uqdo
qTojxHAMOc4Pyo58Jb4E4uGVL4LkkerUkKyh2L4o9nERHt+d7r8PoeoNk88Gn4zb
kz8w8GFOB+Z7fEQIGYq16iXRQsIRf4fnJ260498lcOQkxGud63Dqvnuyg1GEh+/M
SfIbNU4cFFLGQIhWks+t4mn/LrKdvyVsirsDEwIDAQABAoIBACMqkkFw2zo8l0Ag
B+tyFw/3ZAR/LkQfrK8cwJSSmfkLiXXNcXyTuXBXuP01ylAfFFI8pB3nR3+NZIA3
Ry2e09jbplGYAIx4XqDUatcKjrvE1lIOG/Oi/z5ACUsQmBop0pp+L6U7QJcL3Iz3
WhLU6Zu2p0GDQJ7cI6WQ9AGv59jxbt8bPo4wyif69gOgOf9Onu5YWXM3lUxvjPrW
2xUFeqPCfu9XjBl1uYrbRuMIw9HmwaPMSRAD8qSJ/+0NohJvpzBdUo03JAFPuQGl
yzUsJUdgKlYo3bH1QBLKNJ+gRRNDISN+2kkAxsnjpC4XvekqDafzciM6LohNw+pU
2oaiibECgYEA5E16VuQg+a8yGtQf2UL9gacMOHeKplFukCM9IusnU2XBAIXZa+fU
ArojMrUdW/eFy5h57LHK5IgZiV0eA0DXmE4qX/0ZLz1D+DRM/7jTWKvo0YFpX7AA
45+PEoKXzrkNJaec3YbRMWwYSIoKNdCrxzgYrma0iOvOds8fL4gpY50CgYEA1LMA
MpERvY50eN1aUgO9WMifg5xTl9khkvWywJvb3nUSbIqVIPVv65ihudDeP4YQ8Pni
v8MM1MMJQ9K9s0TI0LdDyaF/u8JpW/j0w+NDh/hM7nSolDjj4Rs/Mmq7IC+8VaJr
rGUXkAOQouqTJtt818rzzdQHAfyuCjI1wQuQem8CgYEAokLax7T+Jte44c6QEEeH
i8WhbuSvm4PW9ATHp/DAE4sHgIqhPAsZ6RJIf/qvsjSbWFe3mF3I2WJN3A5djWxh
jvNHNM/bPXLqwxbQ/xNqyuPr5jN3JDYge6dk9X/xy1BEotWdLOlr9xdfrvbFSPhV
jpM1H4cJmyMVq+WLwamh2RUCgYBlC3yGiUBiSvCuEoo7+CbVrMmK3pMfyjkW9b4r
nl9/eSJ9igB6nd7Dj8kU21MZ3njh4fSEoQbRdK5MGCuipIS6ErYTbbOe4SboWIb/
IFIOoDj791O2xqgLYsRNEUNAcS0JiZWZWpUtB2SI4ONzTEYsxe+40odZvE557Yx3
3ySN5QKBgAp/T6jWi5y3l3begwzY9U5w29FpWd3w611QzMkI7Jp/zGAxH1q/HXXQ
YpP8ioxD+fOyhX5MqV9tb/lvUfHnIwvJdx8d7kjDh1e244FJfL7ef7uTrz2272zt
a6uDX2+/aUxMs94s09rTrL0a4Qv3oznLMb5fxk95xoRsNygucuoO
-----END RSA PRIVATE KEY-----
)EOF";
// Amazon Trust Services(ATS) 엔드포인트 CA 인증서 (서버인증 > "RSA 2048비트 키: Amazon Root CA 1" 다운로드)
const char ca_str[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String S="";
  for (int i = 0; i < length; i++) {
    S+=(char)payload[i];
  }
  Serial.println(S);
  
  

}

X509List ca(ca_str);
X509List cert(cert_str);
PrivateKey key(key_str);
WiFiClientSecure wifiClient;
PubSubClient client(host, 8883, callback, wifiClient); //set  MQTT port number to 8883 as per //standard

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(thingId)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("a","successful");
      // ... and resubscribe
      client.subscribe(subTopic1);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      char buf[256];
      wifiClient.getLastSSLError(buf,256);
      Serial.print("WiFiClientSecure SSL error: ");
      Serial.println(buf);

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// Set time via NTP, as required for x.509 validation
void setClock() {
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}

void setup() {
  pinMode(0,INPUT);
  pinMode(16,OUTPUT);
  Serial.begin(115200);
  dht.begin();
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.println();

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  wifiClient.setTrustAnchors(&ca);
  wifiClient.setClientRSACert(&cert, &key);
  Serial.println("Certifications and key are set");

  setClock();
  //client.setServer(host, 8883);
  client.setCallback(callback);
}

long lastMsg = 0;
char msg[50];
int value = 0;



long messageSentAt = 0;
int dummyValue = 0;
char pubMessage[128];
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
   // Wait a few seconds between measurements.
  
  
      if (digitalRead(0) == 0)
      {
        delay(50);
        while (digitalRead(0) == 0);
        delay(50);
        if (digitalRead(16) == HIGH)
        {
            digitalWrite(16, LOW);
            // Reading temperature or humidity takes about 250 milliseconds!
            // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
            float h = dht.readHumidity();
            // Read temperature as Celsius (the default)
            float t = dht.readTemperature();
            // Read temperature as Fahrenheit (isFahrenheit = true)
            float f = dht.readTemperature(true);
            
            Serial.println("Bat den");
            Serial.print("Humidity: ");
            Serial.print(h);
            Serial.print("%  Temperature: ");
            Serial.print(t);
            Serial.print("°C ");
            Serial.print(f);
            Serial.println("°F");
            
            sprintf(pubMessage, "{\"state\":{\"reported\":{\"temp\":\"%.1f\",\"humi\":\"%.1f\",\"Light\":\"ON\"}}}",t,h);
            //sprintf(pubMessage, "{\"temp\":\"%.1f\",\"humi\":\"%.1f\"}",t,h);
            Serial.print("Publishing message to topic ");
            Serial.println(pubTopic1);
            Serial.println(pubMessage);
            client.publish(pubTopic1, pubMessage);
            Serial.println("Published.");
        }
        else
        {
            digitalWrite(16, HIGH);
            Serial.println("Tat den");
        }
      }
















  /*
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
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  Temperature: ");
  Serial.print(t);
  Serial.print("°C ");
  Serial.print(f);
  Serial.print("°F  Heat index: ");
  Serial.print(hic);
  Serial.print("°C ");
  Serial.print(hif);
  Serial.println("°F");
        messageSentAt = now;
        sprintf(pubMessage, "{\"temp\":\"%.1f\",\"humi\":\"%.1f\"}",t,h);      // {\"desired\":{\"foo\":\"%d\"}}}", dummyValue++);
        
        Serial.print("Publishing message to topic ");
        Serial.println(pubTopic);
        Serial.println(pubMessage);
        client.publish(pubTopic, pubMessage);
        Serial.println("Published.");
    }
  */
}
