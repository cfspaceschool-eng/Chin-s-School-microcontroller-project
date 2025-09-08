//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//---
//---
//-------- อ่านค่าจากเซนเซอร์ช่อง A0 และ A3 --------
#include <CP32.h>     // เรียกใช้ไลบารี่ของ CP32
void setup() {
  set_robot();        // กำนหนดค่าของบอร์ด CP32
  OK();               // หยุดรอกดสวิคช์ OK เพื่อเริ่มโปรแกรม
}
void loop() {
  OLED.clearDisplay();      // ล้างหนาจอ OLED
  OLED.setCursor(0, 0);     // กำหนดตำแหน่งแสดงผล x=0 , y=0
  OLED.print(analog(3) , DEC);  OLED.print("  ");   // แสดงค่าของเซนเซอร์ช่อง A3
  OLED.print(analog(0) , DEC);  OLED.print("  ");   // แสดงค่าของเซนเซอร์ช่อง A0
  OLED.display();           // เริ่มแสดงผลที่จอภาพ
}
