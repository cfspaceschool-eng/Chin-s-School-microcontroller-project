//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//---
//---
//-------- โปรแกรมกำเนิดเสียง beep --------
void setup() {
}
void loop() {
  sound();          // เรียกใช้ฟังก์ชั่นกำเนิดเสียง
  delay(2000);      // หน่วงเวลาขั้นระหว่างเสียงที่เกิดขึ้น
}
void sound(void)
{
  pinMode( 3 , OUTPUT );  // กำหนดขา D3 เป็นชนิดเอาท์พุท
  int i = 200;            // ช่วงเวลากำเนิดเสียง
  while (i--)             // วนตามจำนวนรอบของเวลากำเนิดเสียง
  {
    digitalWrite(3 , HIGH);  
    delayMicroseconds(400);    // ความถี่เสียงด้าน HIGH
    digitalWrite(3 , LOW);   
    delayMicroseconds(70);     // ความถี่เสียงด้าน LOW
  }
}
