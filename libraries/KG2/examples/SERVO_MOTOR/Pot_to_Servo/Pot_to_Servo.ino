//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//---
//---
//-------- โปรแกรมทดควบคุมตำแหน่งเซอร์โวมอเตอร์ด้วย Pot --------
#include <CP32.h>     // เรียกใช้ไลบารี่ของ CP32
void setup() {
  set_robot();        // กำนหนดค่าของบอร์ด CP32
  OK();               // หยุดรอกดสวิคช์ OK เพื่อเริ่มโปรแกรม
}
void loop() {
  //---------------- ควบคุม SV1 ด้วยการหมุน Pot ----------------
  int angle = 0;           // ตัวแปร pwm กำหนดความเร็วมอเตอร์
  angle = pot(0, 180);     // รับค่าจาก Pot 0-180 องศา
  servo( 1 , angle );      // เซอร์โซ SV1  หมุนไปตำแหน่งจากค่า angle
  
  //--------- แสดงองศาที่ OLED ---------
  OLED.setCursor( 30 ,  0);      OLED.print( "Angle:" );
  OLED.setCursor( 30 , 30);      OLED.print( angle  , DEC);
  OLED.print( "\xf7  " );        OLED.display();
}
