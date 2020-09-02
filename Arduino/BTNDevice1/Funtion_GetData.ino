
void getDataStr()
{ 
  digitalWrite(4,0);
  delay(100);
  DataStr.DataStringSend = "";
  DataStr.DataStringSave = "";
  DataStr.TimeData = rtc.getTimeStr();
  DataStr.DayData = rtc.getDateStr();
  DataStr.Tempurate1Data = thermocouple1.readCelsius();
  DataStr.Tempurate2Data = thermocouple2.readCelsius();
  DataStr.Tempurate3Data = thermocouple3.readCelsius();
  DataStr.Tempurate4Data = thermocouple4.readCelsius();
  DataStr.Tempurate5Data = thermocouple5.readCelsius();
  DataStr.Tempurate6Data = thermocouple6.readCelsius();
  DataStr.TempurateAir = get_Tempurate_Data();
  DataStr.HumidityAir = get_Humidity_Data();

  DataStr.DataStringSave = DataStr.DayData + "," + DataStr.TimeData + "," + String(DataStr.Tempurate1Data) + "," + String(DataStr.Tempurate2Data);
  DataStr.DataStringSave = DataStr.DataStringSave + "," + String(DataStr.Tempurate3Data) + "," + String(DataStr.Tempurate4Data)+ "," + String(DataStr.Tempurate5Data) + "," + String(DataStr.Tempurate6Data);
  DataStr.DataStringSave = DataStr.DataStringSave + String(DataStr.TempurateAir) + "," + String(DataStr.HumidityAir);

  DataStr.DataStringSend = "&field1=" + String(DataStr.Tempurate1Data) + "&field2=" + String(DataStr.Tempurate2Data) ;
  DataStr.DataStringSend = DataStr.DataStringSend +  "&field3=" + String(DataStr.Tempurate3Data) + "&field4=" + String(DataStr.Tempurate4Data)+ "&field5=" + String(DataStr.Tempurate5Data)+ "&field6=" + String(DataStr.Tempurate6Data);
  DataStr.DataStringSend = DataStr.DataStringSend + "&field5=" + String(DataStr.TempurateAir) + "&field6=" + String(DataStr.HumidityAir);
#ifdef DEBUGER
  Serial.println( "Read Data Done:");
  Serial.println( "Time : " + DataStr.TimeData);
  Serial.println( "Day : " + DataStr.DayData);
  Serial.println("Tempurate 1 : " + String(DataStr.Tempurate1Data));
  Serial.println("Tempurate 2 : " + String(DataStr.Tempurate2Data));
  Serial.println("Tempurate 3 : " + String(DataStr.Tempurate3Data));
  Serial.println("Tempurate 4 : " + String(DataStr.Tempurate4Data));
  Serial.println("Tempurate 5 : " + String(DataStr.Tempurate5Data));
  Serial.println("Tempurate 6 : " + String(DataStr.Tempurate6Data));
  Serial.println("Tempurate Air : " + String(DataStr.TempurateAir));
  Serial.println("Humidity Air : " + String(DataStr.HumidityAir));
  Serial.println("Data Send : " + DataStr.DataStringSend);
  Serial.println("Data Save : " + DataStr.DataStringSave);
  Serial.println("\n");
#endif
digitalWrite(4,1);
}

float get_Tempurate_Data()
{
  float temp_c;
  temp_c = sht1x.readTemperatureC();
#ifdef DEBUG
  Serial.print("Tempurate: ");
  Serial.print(temp_c);
  Serial.println("*C");
#endif
  return temp_c;
}

float get_Humidity_Data()
{
  float humidity;
  humidity = sht1x.readHumidity();
#ifdef DEBUG
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
#endif
  return humidity;
}

bool sdFormat()
{
  pinMode(CSpin, OUTPUT);
  if (!SD.begin(CSpin))
  {
#ifdef DEBUGER
    Serial.println("Card failed, or not present");
#endif
    return false;
  }
#ifdef DEBUGER
  Serial.println("Card OK ");
#endif
  if (!SD.exists("data.csv"))
  {
    sensorData = SD.open("data.csv", FILE_WRITE);
    sensorData.close();
    String dataString = "DAY,TIME,T-1,T-2,T-3,T-4,T-5,T-6,T-A,H-A,SEND";
    return saveData (dataString) ? true : false;
  }
  return true;
}

bool saveData(String DataStr)
{
  if (SD.exists("data.csv"))
  {
    sensorData = SD.open("data.csv", FILE_WRITE);
    if (sensorData)
    {
      sensorData.println(DataStr);
      sensorData.close(); // close the file
    }
  }
  else
  {
    return false;
#ifdef DEBUGER
    Serial.println("Error writing to file !");
#endif
  }
#ifdef DEBUGER
  Serial.println("Saved");
#endif
  return true;
}

void NetworkLed(byte i, byte Delay)
{
  for (byte num = 0; num < i; num++)
  {
    digitalWrite(Network, HIGH);
    delay(Delay);
    digitalWrite(Network, LOW);
    delay(Delay);
  }
}

void NetworkLed(byte i)
{
  for (byte num = 0; num < i; num++)
  {
    digitalWrite(Network, HIGH);
    delay(400);
    digitalWrite(Network, LOW);
    delay(1000);
  }
}
