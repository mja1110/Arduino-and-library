// Giao tiếp 2 board Arduino (Master)
void setup() {
  Serial.begin(9600); // Khai báo sử dụng Serial với tốc độ baud là 9600
}
void loop() {
  //Cứ sau 1 giây ta sẽ on rồi sau đó gửi off đến Slave để điều khiển LED
  Serial.print("on\n"); // Lưu ý: cần kèm kí tự kết thúc dòng '\n' ở cuối lệnh cần gửi
  delay(1000);
  Serial.print("off\n");
  delay(1000);
}
