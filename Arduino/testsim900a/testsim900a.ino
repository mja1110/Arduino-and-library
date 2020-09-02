 
const String myphone = "0941369378";     // Thay so cua ban vao day
const int PWR_KEY =  6;                          // Chan so 9 arduino uno dung lam chan dieu khien bat tat module sim900A

void Gsm_Power_On();                                            // Bat module Sim 900A
void Gsm_Init();                                                       // Cau hinh Module Sim 900A
void Gsm_MakeCall(String phone);                            // Ham goi dien


void setup() {
  Serial.begin(9600);                           // Cau hinh UART de giao tiep module Sim 900A
 
  digitalWrite(PWR_KEY, LOW);         // Khai bao chan PWR_KEY de dieu khien bat bat module Sim 900A
  pinMode(PWR_KEY, OUTPUT);
  
  delay(1000);                       
  Gsm_Power_On();                                      // Bat Module Sim 900A
  delay(10000);
  Gsm_Init();                                                 // Cau hinh module Sim 900A
  Gsm_MakeCall(myphone);                          // Test cuoc goi 
 
}
 
void loop() {
  delay(1000);                                                                    // tre 1s 
  
}
 

 
void Gsm_Power_On()
{
  digitalWrite(PWR_KEY, HIGH);                // Du chan PWR_KEY len cao it nhat 1s 
  delay(1500);                                            // o day ta de 1,5s
  digitalWrite(PWR_KEY, LOW);                  // Du chan PWR_KEY xuong thap
  delay(100);                                              // cac ban xem trong Hardware designed sim900A de hieu ro hon
}
 
void Gsm_Init()
{
  Serial.println("ATE0");                            // Tat che do phan hoi (Echo mode)
  delay(2000);
  Serial.println("AT+IPR=9600");              // Dat toc do truyen nhan du lieu 9600 bps
  delay(2000);
  Serial.println("AT+CMGF=1");                // Chon che do TEXT Mode
  delay(2000);
  Serial.println("AT+CLIP=1");                  // Hien thi thong tin nguoi goi den
  delay(2000);
  Serial.println("AT+CNMI=2,2");              // Hien thi truc tiep noi dung tin nhan
  delay(2000);
}
 
void Gsm_MakeCall(String phone)           
{
  Serial.println("ATD" + phone + ";");         // Goi dien 
  delay(10000);                                        // Sau 10s
  Serial.println("ATH");                              // Ngat cuoc goi
  delay(2000);
}
 
