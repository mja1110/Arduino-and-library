//Giao tiếp 2 board Arduino (Slave)
const int LED = 13; //Sử dụng chân 3 trên board để điều khiển đèn LED
String data = ""; //Khai báo biến data lưu lệnh mà master gửi đến
void setup()
{
  pinMode(LED, OUTPUT); // Khai báo sử dụng pin số 3 làm OUTPUT
  digitalWrite(LED, LOW); // Ban đầu cho đèn LED tắt
  Serial.begin(9600); // Khai báo sử dụng Serial với tốc độ baud = 9600
}
void loop()
{
  if (Serial.available() > 0) // Nếu có lệnh gửi đến
  {
    char c = Serial.read(); //Đọc từng kí tự
    // Kiểm tra kết thúc câu lệnh
    if (c == '\n') {
      if (data == "on") {
        digitalWrite(LED, HIGH);// Nếu lệnh gửi đến là "on" thì bật đèn LED
      } else if (data == "off") {
        digitalWrite(LED, LOW); //Nếu lệnh gửi đến là "off" thì tắt đèn LED
      }
      data = "";
    } else // Nếu chưa phát hiện kí tự kết thúc câu lệnh thì tiết tục ghi nhận.
      data = data + c;
  }
}
