//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//---
//---
//-------- อ่านค่าจากตัวต้านทานปรับค่าได้ POT --------
#include <CP32.h>     // เรียกใช้ไลบารี่ของ CP32
void setup() {
  set_robot();        // กำนหนดค่าของบอร์ด CP32
}
void loop() {
  int pot_val = pot(0 , 100);   // กำหนดค่าตัวแปร และเก็บค่าจากฟังก์ชั่น pot
  OLED.clearDisplay();      // ล้างหนาจอ OLED
  OLED.setCursor(0, 0);     // กำหนดตำแหน่งแสดงผล x=0 , y=0
  OLED.print("POT: ");   OLED.print( pot_val , DEC);        // แสดงค่าของ pot 0-100
  OLED.setCursor(0, 20);  
  OLED.print("XA7: ");   OLED.print( analog(XA7) , DEC);    // แสดงค่าของช่อง XA7
  OLED.display();           // เริ่มแสดงผลที่จอภาพ
}
