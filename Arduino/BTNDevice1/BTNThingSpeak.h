
#define SIM Serial1
#define SIM_RESET 7

#define CSpin  53
#define Network A7

#define DEBUGER
#define SETTIME

#define thermo_cs_1   A0
#define thermo_cs_2   A1
#define thermo_cs_3   A2
#define thermo_cs_4   A3
#define thermo_cs_5   A4
#define thermo_cs_6   A5
#define DTR 6
#define button_Setup_Pin 3

#define SHT10_dataPin  10
#define SHT10_clockPin 11

SHT1x sht1x(SHT10_dataPin, SHT10_clockPin);

MAX6675 thermocouple1( thermo_cs_1);
MAX6675 thermocouple2( thermo_cs_2);
MAX6675 thermocouple3( thermo_cs_3);
MAX6675 thermocouple4( thermo_cs_4);
MAX6675 thermocouple5( thermo_cs_5);
MAX6675 thermocouple6( thermo_cs_6);

DS3231  rtc(SDA, SCL);

File sensorData;

String msgGPRS = "GET /update?api_key=XN6MA1R9H63Q1IZX"; // chanel 1

//String msgGPRS = "GET /update?api_key=W4T0W2PMLKD2Q047"; // chanel 2

String IP = "184.106.153.149";
String PORT = "80";

//volatile byte  Wait = 0;
volatile unsigned int Couter = 0;
struct DataStr
{
  String TimeData;
  String DayData;
  float Tempurate1Data;
  float Tempurate2Data;
  float Tempurate3Data;
  float Tempurate4Data;
  float Tempurate5Data;
  float Tempurate6Data;
  float TempurateAir;
  float HumidityAir;
  String DataStringSave;
  String DataStringSend;
};

struct Status
{
  volatile bool NetworkOn ;
  volatile bool StatusLed;
  volatile bool Sleep;
  bool SDCard ;
  bool StatusSendData;

};

DataStr DataStr = {"", "", 0.00 , 0.00 , 0.00 , 0.00 , 0.00 , 0.00 ,0.00 , 0.00, "" , ""};

Status Status = {true, false, false, true, true};
