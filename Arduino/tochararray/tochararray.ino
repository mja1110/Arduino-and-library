//String data = "abcxyz";
//String w = "rtyuiop";
//char buff[20];
//void setup() {
//  Serial.begin(115200);
//
//}
//
//void loop() {
//  // int data_length=data.length()+1;
//  //char char_array[data_length];
//  data.toCharArray(buff, data.length() + 1);
//  Serial.print(buff);
//  // Serial.print(data_length);
//  w.toCharArray(buff, w.length() + 1);
//  Serial.print(buff);
//  delay(1000);
//}






/*
  char buf[100];
  void setup() {

  Serial.begin(115200);


  }


  void loop() {
  // Hàm toCharArray sẽ tạo ra một chuỗi kiểu mảng mới với độ dài cho trước
  String text = "Arduino.VN - Cong dong Arduino Viet Nam";

  //Bạn hãy thử bỏ +1
  for (byte len = 1;len<=text.length()+1; len++){
    Serial.print("Length: ");
    Serial.print(len);
    Serial.print(" -- ");
    text.toCharArray(buf,len);
    Serial.println(buf);
    delay(1000);
  }

  }
*/



String data = "abcxyz";
String w = "rtyuiop";
char buff[20];
void setup() {
  Serial.begin(115200);

}

void loop() {
  // int data_length=data.length()+1;
  char char_array[data.length()+1];
  data.toCharArray(char_array, data.length() + 1);
  Serial.println(char_array);
  char char_array_1[w.length()+1];
  w.toCharArray(char_array_1,w.length()+1);
  Serial.println(char_array_1);
//  w.toCharArray(buff, w.length() + 1);
//  Serial.print(buff);
  delay(1000);
}
