//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//---
//---
//-------- อ่านค่าจากอัลตร้าโซนิค A1 และ A2 --------
#include <CP32.h>     // เรียกใช้ไลบารี่ของ CP32
void setup() {
  set_robot();        // กำนหนดค่าของบอร์ด CP32
}
void loop() {
  int distance  = SonarSensor();  // กำหนดค่าตัวแปร และอ่านค่าจากเซนเซอร์
  OLED.clearDisplay();
  OLED.setCursor(0, 20);    // กำหนดตำแหน่งแสดงผล x=0 , y=20
  OLED.print( distance , DEC);  OLED.print(" cm  ");   // แสดงค่าระยะห่างที่หน้าจอ
  OLED.display();           // เริ่มแสดงผลที่จอภาพ
}
