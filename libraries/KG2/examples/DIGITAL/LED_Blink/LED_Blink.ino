//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//---
//---
//-------- โปรแกรมไฟกระพริบที่ D13 หลอดไฟ LED --------
void setup() {
  pinMode(13, OUTPUT);    // กำหนดขา D13 เป็นชนิดเอาท์พุท
}
void loop() {
  digitalWrite(13, HIGH); // หลอดไฟติด
  delay(300);             // หน่วงเวลา 300mS
  digitalWrite(13, LOW);  // หลอดไฟดับ
  delay(300);             // หน่วงเวลา 300mS
}
