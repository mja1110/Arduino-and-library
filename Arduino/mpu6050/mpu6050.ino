#include <Wire.h> //Thư viện giao tiếp I2C
const int MPU_addr=0x68;  //Địa chỉ I2C của MPU6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; //Các biến lấy giá trị

void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr); //Gửi tín hiệu đến địa chỉ MPU
  Wire.write(0x6B);  
  Wire.write(0);     //Đưa về 0 để bật MPU
  Wire.endTransmission(true); 
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop()
{
  Wire.beginTransmission(MPU_addr); //Gửi tín hiệu đến địa chỉ MPU
  Wire.write(0x3B);                 //Gửi giá trị lên MPU
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  //Đề nghị thanh ghi của MPU
  
  //Đọc dữ liệu
  AcX=Wire.read()<<8|Wire.read();  //Gia tốc trục x
  AcY=Wire.read()<<8|Wire.read();  //Gia tốc trục y
  AcZ=Wire.read()<<8|Wire.read();  //Gia tốc trục z
  Tmp=Wire.read()<<8|Wire.read();  //Nhiệt độ
  GyX=Wire.read()<<8|Wire.read();  //Góc nghiên trục x
  GyY=Wire.read()<<8|Wire.read();  //Góc nghiên trục y
  GyZ=Wire.read()<<8|Wire.read();  //Góc nghiên trục z
  
  //Xuất ra Serial
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.println(AcZ);
  if(AcY>15000||AcY<-15000) digitalWrite(7,1);
  else digitalWrite(7,0);
//  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //Tính toán để đổi ra độ C
//  Serial.print(" | GyX = "); Serial.print(GyX);
//  Serial.print(" | GyY = "); Serial.print(GyY);
//  Serial.print(" | GyZ = "); Serial.println(GyZ);
  delay(333); //Chờ (1/3)s
}
