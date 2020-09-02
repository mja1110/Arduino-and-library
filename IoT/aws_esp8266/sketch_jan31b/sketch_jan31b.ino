// Example of the different modes of the X.509 validation options
// in the WiFiClientBearSSL object
//
// Jul 2019 by Taejun Kim at www.kist.ac.kr

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <time.h>
#include "DHT.h"
#define DHTPIN D0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
String temp_str; //see last code block below use these to convert the float that you get back from DHT to a string =str
String hum_str;
char temp[50];
char hum[50];
const char *ssid = "GOLD TEA & COFFEE";  // 와이파이 이름
const char *pass = "64dungsithanhkhe";      // 와이파이 비밀번호
const char *thingId = "abc";          // 사물 이름 (thing ID)
const char *host = "a3o2rr7ubdaa9o-ats.iot.us-west-2.amazonaws.com"; // AWS IoT Core 주소
char *pubTopic = "$aws/things/IOT_THING_1/shadow/update";
char *subTopic = "$aws/things/IOT_THINGS_1/shadow/update/delta";

// 사물 인증서 (파일 이름: xxxxxxxxxx-certificate.pem.crt)
const char cert_str[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUePAeNikTIXmuEYXPwiJI8iBGVgswDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIwMDIwMjA3Mjcx
MloXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMttP7zjLBnc47Ks+Elu
JZ6BszsOyEWv1H9wuzpxRbesue9JOj6Mb28Bl4SUnSEFAWLNBNsMf97yI2Qq2Seo
gwgUhBCMf8A1pTtGFmGochA2q7wLGks6WgvO4XqX/DsyLB89VTOUBEV8qpxsMM7G
KciNv45Ty0dZIXrnnQ8RI5T6ko2eiu1wWceTfyUKDnPcQruKIJ0qLXw7NxiTu57F
wp5i17NrJ2nGjc8gqzUTjr4vcgFS6REREOUX6xCPQFoC8J7vZ8xwUF4gsKG8tjdY
iGYdCq5ZsaNojK97pPwhbQ/hp/qrHw7AS9uaVX3DwQiMu9INWRrygu9oNAWtl634
sJcCAwEAAaNgMF4wHwYDVR0jBBgwFoAUrNusfB90cwcPhPaWa/j5mha9noMwHQYD
VR0OBBYEFNPZBqvuqt8eytM/tJHjU90kfUs7MAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQDGsYjM8baN0UE1lcMWb1B+uGsf
fPx1CIjhs+0XpVFVpbHGMGcQzucWL3DNppEgcml0zpEbwQLY6A8c+edBxy17CP6W
4xoeeLW688b+atK3gnMgUf+m6nmwCvGKrXlrP+llASt/Nqm98rZz7qDhOkUpDWRg
CJGfinhShdcoMT9+SdlGJywmVGRls/ZjwouO9hSJ3LKDp6JTu2MSNHxZyxpVGsFL
R97s3F3mMm72iZNePS7a3ZZ+R9poc+Ufba6Q7PCaig39riy/Tf25vSpYLaG+tOPd
UMLqERzgU9iLenA3zErWT2ZujjAJtkdTDjBGrcqlNsWDtKQCq19G/7JO/be2
-----END CERTIFICATE-----
)EOF";
// 사물 인증서 프라이빗 키 (파일 이름: xxxxxxxxxx-private.pem.key)
const char key_str[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAy20/vOMsGdzjsqz4SW4lnoGzOw7IRa/Uf3C7OnFFt6y570k6
PoxvbwGXhJSdIQUBYs0E2wx/3vIjZCrZJ6iDCBSEEIx/wDWlO0YWYahyEDarvAsa
SzpaC87hepf8OzIsHz1VM5QERXyqnGwwzsYpyI2/jlPLR1kheuedDxEjlPqSjZ6K
7XBZx5N/JQoOc9xCu4ognSotfDs3GJO7nsXCnmLXs2snacaNzyCrNROOvi9yAVLp
EREQ5RfrEI9AWgLwnu9nzHBQXiCwoby2N1iIZh0Krlmxo2iMr3uk/CFtD+Gn+qsf
DsBL25pVfcPBCIy70g1ZGvKC72g0Ba2XrfiwlwIDAQABAoIBAAWpZLy9Fd0iaLPw
XHiuuB1RPsvF/Yzy99cULCHURTx3cjVWtGhJQFC2mqD2AemJWiCF1DzEfEqYMqP3
DVQtPHhdGc/cGTIgTBj6OmU9au9Ilj8FkBXH6fmqKFxhHoQHQXMdIeHtnLDSZ20z
Fairmz4Zs9siOeYidOwWxihFMdhTlDrV7CxmIvabFMOVNROfyY+pWtVhJf6F1NK9
uby0gbPe963zMo9Xzsumj2xuzhwv8pwyywrH8EKNnfwl2FEfrQ656oN+BWqlRZX8
GG93VUIQ7szFKuZdedBA0k+xM14x+FBize+uBMkDXrZCf2ZBTTWDKbPQvcC11WHG
Bv5HngECgYEA/WktOSRt2DrsWG8OlGnI0FOBO87wnCC138UlDchIiTi+LHnWfsZ7
b7NRYPExUxFe7uvajWhMwOLEOgFeEQ7F2qlIy3offEgfH7/82PRH2OlFT1QfVg0s
DjH88PCrg9ioa3aGmrwL21JQMKTAYbBkAGgLP5Hv53wOjkf0WoSQ0t8CgYEAzYFV
Y2ydiv01RlZEXdo8Q1NqOlEI0EflbtMTGmizV6jq6EoE3i0Q/i9EwNzVhnuu/yIv
e3A1SgubectJQoa/li8O24/+vGnW3eYBNXa/Lishty8BJBLQrfeC1agpIXDcQK0/
syHeescFsPhIMTQhglFBFk9ncJSH80Ua0MSMUUkCgYBF0hnUubXOMwX1o7vHppHe
3HMqEG15BwY1fnMkJf/eVxUG2hcAXR2bfDO62xm1An8+oxtXhNpI9vIL7V6GoqRf
B+93qNFOA+0XaWV4PW4iVLt1DP+JTR3LV3iSxizrqeFVopWZwqAdsMNJc8tR3zDe
b8xRmpsYE7VK/IZV/lqMzwKBgQCci1ADa+La1KW3jdGIeMz9MFa0U7RWDN6OPIXJ
0UYEma1QA8qPgF74cgN6sv6I8kDNIzpuWnyNiigGcD+/SKw6+F/mC1uuJSXDZQk4
s9tQjRSi2VCSLS7/xpLItM+YJMPzFMZ4a21xs5f3RjqgGKkJ/2GIYDZYwRyKyPJz
Y7XL2QKBgQDbazjItQhZqezV50V2eIZ00nxuaqKnBy0aua8+T1FWDK2Y9B/GD+to
RG1ZAqpAyIFpe48W0sXcPwprMQVq/j3ZGR74kAp6jLDwXe3rQkL1OXL3RviuaZqZ
dY6lvB3TiaKUZz2+30N3dnWYxMdedCpCzsZc+ptbeor6euEccwSFWg==
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
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

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
      client.publish(pubTopic,"ESP_reconnected");
      // ... and resubscribe
      client.subscribe(subTopic);
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
  Serial.begin(115200);
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

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();


  
  
  //Đọc nhiệt độ độ ẩm
delay(2000);
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
   temp_str = String(t); //converting ftemp (the float variable above) to a string
  temp_str.toCharArray(temp, temp_str.length() + 1);
  hum_str = String(h); //converting Humidity (the float variable above) to a string
  hum_str.toCharArray(hum, hum_str.length() + 1);
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "{\"state\": {\"desired\":{\"foo\":\"%d\"}}}", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(pubTopic, msg);
    delay(1000);
    Serial.print("Heap: "); Serial.println(ESP.getFreeHeap()); //Low heap can cause problems
  }
}
