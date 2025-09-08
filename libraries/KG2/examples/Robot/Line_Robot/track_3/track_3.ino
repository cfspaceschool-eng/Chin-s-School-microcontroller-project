//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//---
//---
//-------- โปรแกรมหุ่นยนต์เดินตามเส้นแบบ 3 เซนเซอร์ --------
#include <CP32.h>     // เรียกใช้ไลบารี่ของ CP32
int p ;           // ความเร็วในการเคลื่อนที่ 0-100%
int ref = 500 ;   // ค่าอ้างอิงเพื่อใช้ในเงื่อนไข
void setup() {
  set_robot();  
  OK(LCR);         // หยุดรอ , แสดงค่าเซนเซอร์ L(A3),R(A0) และ C(XA3)
}
void loop() {
  p = 70  ;         // กำหนดความเร็วเริ่มต้นที่ 70%
  track_line3(p);   // ใช้งานฟังก์ชั่นเดินตามเส้นแบบ 3 เซนเซอร์
}
//*
//*
//************* ฟังก์ชั่นหุ่นยนต์เดินตามเส้น 3 เซนเซอร์ *************
void track_line3(int power)
{
  int senL = analog(3) , senC = analog(xa3) , senR = analog(0) ;      // กำหนดตัวแปรและอ่านค่า Analog
  //---------------------เคลื่อนที่แบบพื้นฐาน-----------------------
  if (senL > ref && senC < ref && senR > ref) // ขาว - ดำ - ขาว
    motor(power , power);
  else if (senL > ref && senC < ref && senR < ref) // ขาว - ดำ - ดำ
    motor(power , 0);
  else if (senL < ref && senC < ref && senR > ref) // ดำ - ดำ - ขาว
    motor(0 , power);
  //---------------------หุ่นยนต์เกือบหยุดเส้นแทร็ก-----------------------
  else if (senL > ref && senC > ref && senR < ref) // ขาว - ขาว - ดำ
    motor(90 , -power);
  else if (senL < ref && senC > ref && senR > ref) // ดำ - ขาว - ขาว
    motor(-power , 90);
  //---------------------สถานะอื่นๆของหุ่นยนต์ ที่อาจะเกิดขึ้น-----------------------
  else if (senL > ref && senC > ref && senR > ref)     // ขาว - ขาว - ขาว
    motor(-power, -power);
  else if (senL < ref && senC > ref && senR < ref)    // ดำ - ขาว - ดำ
    motor(power , power);
}
