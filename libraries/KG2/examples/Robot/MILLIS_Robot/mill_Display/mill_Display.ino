//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//---
//---
//-------- โปรแกรมทดสอบแสดงค่าเวลา millis --------
#include <CP32.h>     // เรียกใช้ไลบารี่ของ CP32
void setup() {
  set_robot();        // กำนหนดค่าของบอร์ด CP32
  OK();
}
void loop() {
 static unsigned long  cur_tm = 0 ;   // ประกาศตัวแปรเก็บค่าเวลา

  if (digitalRead(2) == LOW)          // ถ้ากดสวิตช์ OK ให้เก็บค่าเวลา
  {
    cur_tm = millis();
    beep();
    delay(1000);
  }
  OLED.setCursor( 0 , 0);         // กำหนดตำแหน่งแสดงผล x=0 , y=0
  OLED.println( cur_tm , DEC);
  OLED.display();                 // เริ่มการแสดงผล
}
