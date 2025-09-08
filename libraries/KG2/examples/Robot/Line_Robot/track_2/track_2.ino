//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//---
//---
//-------- โปรแกรมหุ่นยนต์เดินตามเส้นแบบ 2 เซนเซอร์ --------
#include <CP32.h>     // เรียกใช้ไลบารี่ของ CP32
int p ;           // ความเร็วในการเคลื่อนที่ 0-100%
int ref = 500 ;   // ค่าอ้างอิงเพื่อใช้ในเงื่อนไข
void setup() {
  set_robot();  
  OK(LR);         // หยุดรอ , แสดงค่าเซนเซอร์ L(A3) และ R(A0)
}
void loop() {
  p = 60  ;       // กำหนดความเร็วเริ่มต้นที่ 60%
  track_line(p);  // ใช้งานฟังก์ชั่นเดินตามเส้นแบบ 2 เซนเซอร์
}
//*
//*
//************* ฟังก์ชั่นหุ่นยนต์เดินตามเส้น 2 เซนเซอร์ *************
void track_line(int power)
{
  int senL = analog(3) , senR = analog(0);      // กำหนดตัวแปรและอ่านค่า Analog
  if (senL > ref && senR > ref)       // ซ้ายและขวา สีขาว  คล่อมเส้นดำ
    motor(power, power);
  else  if (senL < ref && senR > ref) // ซ้ายเจอเส้นสีดำ หุ่นยนต์เอียงขวา
    motor(-power, power);
  else  if (senL > ref && senR < ref) // ขวาเจอเส้นสีดำ หุ่นยนต์เอียงซ้าย
    motor(power, -power);
}
