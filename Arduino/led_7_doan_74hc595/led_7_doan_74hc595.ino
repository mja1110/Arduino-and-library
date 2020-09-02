/*
shiftOut ra 1 Module LED 7 đoạn đơn
*/
//chân ST_CP của 74HC595
int latchPin = 8;
//chân SH_CP của 74HC595
int clockPin = 12;
//Chân DS của 74HC595
int dataPin = 11;

// Ta sẽ xây dựng mảng hằng số với các giá trị cho trước
// Các bit được đánh số thứ tự (0-7) từ phải qua trái (tương ứng với A-F,DP)
// Vì ta dùng LED 7 đoạn chung cực dương nên với các bit 0
// thì các đoạn của LED 7 đoạn sẽ sáng
// với các bit 1 thì đoạn ấy sẽ tắt

//mảng có 10 số (từ 0-9) và 
const int Seg[10] = {
  0b11000000,//0 - các thanh từ a-f sáng
  0b11111001,//1 - chỉ có 2 thanh b,c sáng
  0b10100100,//2
  0b10110000,//3
  0b10011001,//4
  0b10010010,//5
  0b10000011,//6
  0b11111000,//7
  0b10000000,//8
  0b10010000,//9
};


void setup() {
  //Bạn BUỘC PHẢI pinMode các chân này là OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() { 
  static int point = 0;
  
  //shiftout - start
  digitalWrite(latchPin, LOW);
  //Xuất bảng ký tự ra cho Module LED
  shiftOut(dataPin, clockPin, MSBFIRST, Seg[point]);  
  digitalWrite(latchPin, HIGH);
  //shiftout - end
  
  point = (point + 1) % 10; // Vòng tuần hoàn từ 0--9
  delay(500);//Đợi 0.5 s cho mỗi lần tăng số
}
