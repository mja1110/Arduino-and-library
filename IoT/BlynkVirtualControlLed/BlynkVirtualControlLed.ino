/* 
	TAPIT Learning, Researching and Sharing

  **DESCRIPTION:
  - Using NodeMCU connect to Blynk to control LED via Blynk virtual pin 0 and NodeMCU button.
  - Also synchronous these button state.
*/
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "97005ff437f14442adb86fb1df94fcad";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IoT-Research";
char pass[] = "Tapit168";
int virtualPin;
int flag=0;
// WidgetLED led1(V1);

//Gửi dữ liệu trạng thái Button từ Blynk về Nodemcu
BLYNK_WRITE(V0)
{
  virtualPin = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("V0 Slider value is: ");
  Serial.println(virtualPin);
  flag = 1;
}

//Đồng bộ lại trạng thái khi mất nguồn
BLYNK_CONNECTED(){
  Blynk.syncVirtual(V0);  
  }
 
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(16, OUTPUT);
  pinMode(0, INPUT_PULLUP);

}

void loop()
{
  Blynk.run();
  
  if(flag == 1){
  if(virtualPin == 0){
    digitalWrite(16, LOW);
    }
    else digitalWrite(16, HIGH);
  }
  
  if(digitalRead(0) == LOW){
    while(digitalRead(0) == LOW);
    int ledStatus = digitalRead(16);
    if(ledStatus == 0){
      digitalWrite(16, HIGH);
      Blynk.virtualWrite(V0,1); //Ghi dữ liệu từ Nodemcu lên Blynk
      //led1.off();
      }
      else {
      digitalWrite(16, LOW);
      Blynk.virtualWrite(V0,0); ////Ghi dữ liệu từ Nodemcu lên Blynk
     // led1.on();
      }
    }
  flag = 0;
}

