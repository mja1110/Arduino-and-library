// Master
#include <Wire.h>
void setup()
{
  Serial.begin(9600); // Khởi tạo giao tiếp I2C
  Wire.begin(); // Khởi tạo truyền nhận dữ liệu I2C
}
void loop()
{
  // Bắt đầu quá trình truyền dữ liệu trên Serial Monitor
  while (Serial.available()) {
    char c = Serial.read(); // Đọc dữ liệu từ serial nếu có và lưu vào biến c
    if (c == 'H') {
      Wire.beginTransmission(3); // Bắt đầu truyền đến slave với address la 3
      Wire.write('H'); // Truyền chữ H đến slave
      Wire.endTransmission(); // Kết thúc quá trình truyền
    } else if (c == 'L') {
      Wire.beginTransmission(3);
      Wire.write('L');
      Wire.endTransmission();
    }
  }
}
