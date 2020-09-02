// Slave
#include <Wire.h>
#define pinLed 13 // Định nghĩa chân LED trên board Iotmaker Uno X
void setup()
{
  Wire.begin(3); // Khởi tạo giao tiếp I2C với địa chỉ của slave là 3
  Wire.onReceive(receiveEvent); // Đăng kí hàm receiveEvent sẽ được gọi khi nhận được dữ liệu
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, LOW);
}
void loop()
{
  // Không làm gì cả
}
void receiveEvent()
{
  while (Wire.available()) {
    char c = Wire.read(); // Lưu dữ liệu nhận được từ master vào biến c nếu có
    if (c == 'H') // So sánh dữ liệu nhận được và điều khiển LED
      digitalWrite(pinLed, HIGH);
    else if (c == 'L')
      digitalWrite(pinLed, LOW);
  }
}
