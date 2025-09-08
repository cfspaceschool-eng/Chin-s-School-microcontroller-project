//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//---
//---
//-------- โปรแกรมทดควบคุมทิศทาง และความเร็วมอเตอร์ดีซีด้วย Pot --------
#include <CP32.h>     // เรียกใช้ไลบารี่ของ CP32
void setup() {
  set_robot();        // กำนหนดค่าของบอร์ด CP32
  OK();               // หยุดรอกดสวิคช์ OK เพื่อเริ่มโปรแกรม
}
void loop() {
  int pwm = 0;            // ตัวแปร pwm กำหนดความเร็วมอเตอร์
  pwm = pot(-100, 100);   // รับค่าจาก Pot -100 ถึง 100 เพื่อควบคุมมอเตอร์
  motor(pwm, pwm);

  //--------- แสดงความเร็วมอเตอร์ที่ OLED ---------
  OLED.setCursor( 30 ,  0);      OLED.print( "Speed:" );
  OLED.setCursor( 30 , 30);     OLED.print( pwm  , DEC);
  OLED.print( "\x25  " );       OLED.display();
}
