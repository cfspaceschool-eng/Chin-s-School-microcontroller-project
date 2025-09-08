//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//---
//---
//-------- โปรแกรมทดสอบแสดงตัวอักษร และตัวแปร --------
#include <CP32.h>     // เรียกใช้ไลบารี่ของ CP32
void setup() {
  set_robot();        // กำนหนดค่าของบอร์ด CP32
}
void loop() {
  static int i = 0 ;              // ประกาศตัวแปรสำหรับนับจำนวน
  OLED.setTextSize(2);            // กำหนดขนาดตัวอักษร  ปรับเปลี่ยนได้เพื่อทดสอบ
  OLED.clearDisplay();            // ล้างหน้าจอ OLED
  OLED.setCursor( 0 , 0);         // กำหนดตำแหน่งแสดงผล x=0 , y=0
  OLED.print("TEXT ");            // แสดงข้อความ TEXT
  OLED.println("CP32");           // แสดงข้อความ CP32 ในบรรทัดเดียวกับข้อความ TEXT
                                  // และให้ข้อความต่อไปแสดงในบรรทัดใหม่ [println]
  OLED.println("MONTHAR TRAINING");   // แสดงข้อความที่ยาวกว่า 1 บรรทัด  จะตัดข้อความขึ้นบรรทัดใหม่อัตโนมัติ     
  OLED.print( i++  , DEC);        // แสดงค่าตัวแปร i แบบเลขฐานสิบ
  OLED.display();                 // เริ่มการแสดงผล
  delay(10);
}
