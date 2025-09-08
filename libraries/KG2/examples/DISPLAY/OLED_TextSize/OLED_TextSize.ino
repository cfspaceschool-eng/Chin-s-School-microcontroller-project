//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//---
//---
//-------- โปรแกรมทดสอบขนาดตัวอักษร --------
//-------- หมุนปรับที่ pot จากขนาด 1 ถึง 8 --------
#include <CP32.h>     // เรียกใช้ไลบารี่ของ CP32
void setup() {
  set_robot();        // กำนหนดค่าของบอร์ด CP32
}
void loop() {
  dis_textsize();     // ฟังก์ชั่นปรับขนาดตัวอักษรจาก pot
}
//*************************************
void dis_textsize(void)
{
  int s = pot(1 , 8);           // ประกาศตัวแปรและอ่านค่าจาก pot 1-8 ขนาด
  OLED.setTextSize(s);          // กำหนดขนาดของตัวอักษร ตามค่าตัวแปร
  OLED.clearDisplay();          // ล้างหน้าจอ OLED
  OLED.setCursor( 0 , 0);       // กำหนดตำแหน่งแสดงผล x=0 , y=0
  OLED.print("SIZE ");          // แสดงข้อความ
  OLED.println( s  , DEC);      // แสดงค่าตัวแปร s
  OLED.print("(1-8)");
  OLED.display();               // เริ่มการแสดงผล
  delay(10);
}
