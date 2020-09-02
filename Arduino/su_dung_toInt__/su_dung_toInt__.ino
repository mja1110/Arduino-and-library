String inString = "";    // biến inString dùng để lưu giá trị từ input

void setup() {
  // Mở cổng Serial với mức baudrate 9600
  Serial.begin(9600);
  while (!Serial) {
    ; // đợi cổng Serial được bật lên (chỉ cần với mạch Arduino Leonardo)
  }

  // Gửi một thông báo rằng hàm setup đã hoạt động xong
  Serial.println("\n\nChuyen doi chuoi so thanh so:");
  Serial.println();
}

void loop() {
  // Đọc giá trị từ Serial
  while (Serial.available() > 0) {
    int inChar = Serial.read(); //Xem thêm về Serial.read() tại http://arduino.vn/reference/library/serial/1/huong-dan-ham/read
    if (isDigit(inChar)) { // Hàm kiểm tra SỐ ĐÓ có là một ký tự số hay không (xem bảng ACSII http://arduino.vn/reference/bang-ma-ascii )
      // Chuyển đổi số đó thành ký tự
      // và thêm vào chuỗi. Nếu không thì bạn sẽ thêm một số nguyên vào đấy :P
      inString += (char)inChar;
    }
    // Nếu inChar là một ký tự xuống dòng. Ta in kết quả ra
    if (inChar == '\n' ) {//Một ký tự ta dùng dấu ' (nháy đơn) còn một chuỗi ta dùng " (dấu nháy kép)
      Serial.print("Gia tri :");
      Serial.println(inString.toInt());
      Serial.print("Chuoi: ");
      Serial.println(inString);
      // xóa giá trị của biến inString
      inString = "";
    }
  }
}
