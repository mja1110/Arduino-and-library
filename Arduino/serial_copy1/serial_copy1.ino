int incomingByte = 0;   // lưu tín hiệu đến

void setup() {
  Serial.begin(9600);     // mở cổng serial với mức baudrate là 9600
}

void loop() {

  // xuất tín hiệu khi nhận được tín hiệu
  if (Serial.available() > 0) {
    // đọc các giá trị nhận được
    incomingByte = Serial.read();

    // xuất ra những gì nhận được
    Serial.print("Toi nghe duoc: ");
    Serial.println(incomingByte, DEC);
  }
}
