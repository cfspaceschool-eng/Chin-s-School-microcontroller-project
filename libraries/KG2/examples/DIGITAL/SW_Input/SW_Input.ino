//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//---
//---
//-------- โปรแกรมอ่านค่าการกดสวิคช์ OK --------
#include <CP32.h>     // เรียกใช้ไลบารี่ของ CP32
void setup() {
  set_robot();            // กำนหนดค่าของบอร์ด CP32
  pinMode(2, OUTPUT);     // กำหนดขา D2 เป็นชนิดอินพุท
  digitalWrite(2, HIGH);  // ส่งสถานะ HIGH ไปที่ D3 เพื่อเป็นการ Pull up.
}
void loop() {
  OLED.setCursor(10, 0);      // กำหนดตำแหน่งแสดงผล x=10 , y=0
  if (digitalRead(2) == LOW)  // อ่านค่าจากขา D2 ว่ากดหรือไม่(LOW)
  {
    OLED.print("ON ");        // หากมีการกด ให้แสดงข้อความ ON
  }
  else
  {
    OLED.print("OFF ");       // หากไม่มีการกด(HIGH)  ให้แสดงข้อความ OFF
  }
  OLED.display();     // เริ่มแสดงผลที่จอภาพ
}
