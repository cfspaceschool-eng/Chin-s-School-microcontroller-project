//-------หุ่นยนต์ BM_V2 ใช้บอร์ด CP-32 ในการควบคุมการทำงาน BO1  1:48
//---------First Edit 01/09/65-------
//---------ใช้โปรแกรมคาลิเบทสำหรับเก็บค่าพื้นสีดำ สีขาว อัตโนมัติ--------
#include <CP32.h>
int p = 00 ;        // กำลังของมอเตอร์(%)
void setup() {
  set_robot();
  //---------------------SET FOR BM V2
  set_BM_V2();
  pos_1();          // ชุดส่งกล่อง  เซอร์โวต่อช่อง SV1 (ตำแหน่งเริ่มต้น ใส่กล่องได้ 5 ใบ)
  //========ตรวจสอบการกดสวิตช์เพื่อคาลิเบท=========
  if (!press_OK()) Calibrate_MODE(60);    // หุ่นยนต์ไม่เคลื่อนที่  ให้จับหุ่นยนต์กวาดไปบนเส้นดำและขาว ช้าๆ
  //========================================
  OK_Calibrate();
} // setup


void loop() {

  p = pot(0, 100);      //--------หมุนปรับความเร็วที่ pot ปกติ 50%

  //-------  กำหนดฟังก์ชั่นสำหรับทำภารกิจ  ตามลำดับ  --------
  //goto AA;        คำสั่ง goto  ใช้สำหรับกระโดดไปทำงานที่ลาเบล AA:  เพื่อข้ามส่วนที่ทำภารกิจได้แล้ว
  track_wall(p);  turn_R90(p);          // แทร็กเส้นข้าง และหมุนขวา เมือเจอกำแพงด้านหน้า
  track_wall(p);  turn_R90(p);
  track_wall(p);  turn_R90(p);
  track_wall(p);  RV_encoder(p, 4);    turn_L90(p);  // แทร็กเส้นข้าง ถอยหลัง 4 step และหมุนซ้าย
  setbot_rear(p);         //  ตั้งลำตัวหุ่นยนต์ด้วยเซนเซอร์ด้านหลัง

  track_wall(p);
  RV_encoder(p, 10);   delay(50);  send_BOX();   // ถอยหลังแล้วส่งกล่อง
  RV_encoder(p, 20);
  turn_L90(p);
AA:                     //  ลาเบล AA  ตำแหน่งสำหรับการกระโดดมาทำงานด้วยคำสั่ง goto AA;
  track_wall(p);     RV_encoder(p, 6);    turn_L90(p);
  track_wall(p);     turn_L90(p); turn_L90(p);      //  เข้าจุด check point

  track_wall(p);     turn_R90(p);       //  เข้าจุด check point
  track_wall(p);     setbot_front(p);   //  ตั้งลำตัวหุ่นยนต์ด้วยเซนเซอร์ด้านหน้า

  RV_encoder(p, 15);   send_BOX();
  RV_encoder(p, 5);    send_BOX();
  RV_encoder(p, 5);    send_BOX();   send_BOX();

  ao();  beep(); delay(2000);
  while (1) delay(2000);    //  หยุดหุ่นยนต์

}
