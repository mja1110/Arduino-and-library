//const int sensor1 = 2;
//const int sensor2 = 3;
//const int sensor3 = 4;
//const int sensor4 = 5;
//const int sensor5 = 6;
//const int sensor6 = 7;
//const int sensor7 = 8;
//const int sensor8 = 9;
//const int sensor9 = 10;
//const int sensor10 = 11;
//const int sensor11 = 12;
//const int sensor12 = 13;

//const int sensor12 = 13;



void sendThingspeak() {
  sim808.println("AT");
  delay(1000);

  sim808.println("AT+CPIN?");
  delay(1000);

  sim808.println("AT+CREG?");
  delay(1000);

  sim808.println("AT+CGATT?");
  delay(1000);

  sim808.println("AT+CIPSHUT");
  delay(1000);

  sim808.println("AT+CIPSTATUS");
  delay(2000);

  sim808.println("AT+CIPMUX=0");
  delay(2000);

  ShowSerialData();

  sim808.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);

  ShowSerialData();

  sim808.println("AT+CIICR");//bring up wireless connection
  delay(3000);

  ShowSerialData();

  sim808.println("AT+CIFSR");//get local IP adress
  delay(2000);

  ShowSerialData();

  sim808.println("AT+CIPSPRT=0");
  delay(3000);

  ShowSerialData();

  sim808.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);

  ShowSerialData();

  sim808.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();

  String str = (String)"GET https://api.thingspeak.com/update?api_key=T65D75U8Z714FGRF&field1=" + "{\"relay1\":" + ;
  Serial.println(str);
  sim808.println(str);//begin send data to remote server

  delay(4000);
  ShowSerialData();

  sim808.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet
  sim808.println();

  ShowSerialData();

  sim808.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
}


void setup() {
  Serial.begin(9600);

  // define sensor
  for (int i =2; i<=13; i++) 
  {
    pinMode(i,INPUT_PULLUP);
  }

  // define relay
   for (int i =30; i<=49; i++) 
  {
    pinMode(i,INPUT_PULLUP);
  }
//  pinMode(sensor1, INPUT_PULLUP);
//  pinMode(sensor2, INPUT_PULLUP);
//  pinMode(sensor3, INPUT_PULLUP);
//  pinMode(sensor4, INPUT_PULLUP);
//  pinMode(sensor5, INPUT_PULLUP);
//  pinMode(sensor6, INPUT_PULLUP);
//  pinMode(sensor7, INPUT_PULLUP);
//  pinMode(sensor8, INPUT_PULLUP);
//  pinMode(sensor9, INPUT_PULLUP);
//  pinMode(sensor10, INPUT_PULLUP);
//  pinMode(sensor11, INPUT_PULLUP);
//  pinMode(sensor12, INPUT_PULLUP);

}

void loop() {

  // read sensor
  for (int i =2; i<=13; i++) 
  {
    Serial.println(digitalRead(i));
    delay(20);
  }


  // read relay
  for (int i =30; i<=49; i++) 
  {
    Serial.println(digitalRead(i));
    delay(20);
  }
  
  //Serial.println(digitalRead(32));
}
