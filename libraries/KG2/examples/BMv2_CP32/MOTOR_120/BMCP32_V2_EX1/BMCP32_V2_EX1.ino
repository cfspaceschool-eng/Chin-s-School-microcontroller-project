//-------หุ่นยนต์ BM_V2 ใช้บอร์ด CP-32 ในการควบคุมการทำงาน BO1  1:120
//---------Edit 31/10/65-------
//---------ใช้โปรแกรมคาลิเบทสำหรับเก็บค่าพื้นสีดำ สีขาว อัตโนมัติ--------
//--------- VDO ตัวอย่างการทำคาลิเบต  https://youtu.be/nKL0HHoO7wg   --------

//---------------- โปรแกรมตัวอย่างการทำภารกิจ ------------------------
//--------   หุ่นยนต์ BM_V2  แสดงตามคลิป EX1  https://www.facebook.com/mnrobot/videos/867467483639222/


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
  p = pot(0, 100);
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
//=========================================
//=========================================
void move_test(void)
{
  motor(p, p);     delay(2500); // ตรง
  motor(-p, -p);   delay(2500); // ถอย
  motor(-p, p);    delay(1500); // หมุนซ้าย
  motor(p, -p);    delay(1500); // หมุนขวา
  ao();            delay(100); // หมุนขวา
}

void encoder_test(void)
{
  FD_encoder(p, 50);     // เคลื่อนที่ตรง จำนวน 50 step
  delay(500);
  RV_encoder(p, 25);     // ถอยหลัง จำนวน 55 step
  delay(500);
  LL_encoder(p, 10);     // หมุนซ้าย จำนวน 10 step
  delay(500);
  RR_encoder(p, 20);     // หมุนขวา จำนวน 10 step
  delay(500);
  LL_encoder(p, 10);
  delay(500);
  //---------------------------------
  RV_encoder(p, 25);
}
