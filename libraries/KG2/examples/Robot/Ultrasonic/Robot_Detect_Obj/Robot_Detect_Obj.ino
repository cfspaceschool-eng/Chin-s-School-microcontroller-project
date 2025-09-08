//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//---
//---
//-------- อ่านค่าจากอัลตร้าโซนิค A1 และ A2 แล้วหลบวัตถุด้านหน้า--------
#include <CP32.h>     // เรียกใช้ไลบารี่ของ CP32
void setup() {
  set_robot();        // กำนหนดค่าของบอร์ด CP32
  OK(LR);
}
void loop() {
  int p = 60 ;
  int distance ;                    // กำหนดค่าตัวแปร และอ่านค่าจากเซนเซอร์
  while ( SonarSensor() > 15 )  motor(p, p);  // ตรวจเช็คระยะห่าง ถ้ามากกว่า 15 ซม ให้ตรงไปเรื่อยๆ
  ao();  beep();                    // หยุดการเคลื่อนที่ เมื่อระยะน้อยกว่า 15 ซม
  //---------- แสดงผลระยะห่าง ----------  
  delay(500);
  distance  = SonarSensor();        // อ่านค่าจากเซนเซอร์  
  OLED.clearDisplay();          OLED.setCursor(0, 20);
  OLED.print( distance , DEC);  OLED.print(" cm  ");
  OLED.display();
  delay(500);
  //-----------------------------------
  motor(-p, -p);  delay(600);     // ถอยหลังเล็กน้อย
  motor(-p, p);   delay(300);     // หมุนหุ่นยนต์ไปด้านซ้าย แล้วเริ่มตรวจเช็คระยะอีกครั้ง
}
