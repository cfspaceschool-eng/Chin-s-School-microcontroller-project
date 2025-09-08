//==============================
//-------- สำหรับ CP32 - BMV2
//==============================
/*  ตำแหน่งเซนเซอร์ด้านหน้าหุ่นยนต์
  ด้านหน้า          XA3---XA2---XA1
  ด้านหลัง              A3----A2
  encoder(ช่อง DO)     A1____A0
*/

#define NUM_SENSORS  5          // จำนวนเซนเซอร์ที่ใช้งาน
int thresholdValue = 500;       // ค่าอ้างอิง กึ่งกลางระหว่างขาวและดำ(ค่า max 1000)
int val_max[NUM_SENSORS];       // เก็บค่ามากสุดของเซนเซอร์แต่ละตัว (พื้นสีขาว)
int val_min[NUM_SENSORS];       // เก็บค่าน้อยสุดของเซนเซอร์แต่ละตัว (พื้นสีดำ)
int pp[NUM_SENSORS] = { XA3 , XA2 , XA1 , 3 , 2 };    // pp=pointer_port  ตัวชี้ตำแหน่งพอร์ตเซนเซอร์ จะเรียงจากซ้ายไปขวา ใส่ตำแหน่งพอร์ตเช่น A7 ใส่เลข 7
int sensors[NUM_SENSORS];        // เก็บค่าเซนเซอร์หลังจาก map แล้ว
//---------------------------------
int checkSensors(int) ;
//----------------------------------memo
#include <EEPROM.h>

void write_EEprom(void);
void read_EEprom(void);
void Display_EEprom(void);
//----------------------------------memo
void clear_value(void)
{
  for (int i = 0; i < NUM_SENSORS; i++)      // Clear ข้อมูล และนำค่า max min ไปวางไว้ก่อนเก็บข้อมูล
  {
    val_max[i] = 0;
    val_min[i] = 1000;    // กำหนดค่า min  ก่อนเก็บค่าใหม่
  }
}
void line_sensors_scan()  //  เช็คเซนเซอร์  เพื่อเก็บค่าไว้ใน max  min ของแต่ละตัว
{
  long sensors_read[NUM_SENSORS];  // เก็บค่าเซนเซอร์แต่ละช่อง
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    sensors_read[i] = analog(pp[i]);          // อ่านค่าจากช่อง Analog
    if (sensors_read[i] > val_max[i])       // ถ้าค่าที่อ่านสูงกว่า max เดิม
      val_max[i] = sensors_read[i];         // เก็บค่า max ใหม่

    if (sensors_read[i] < val_min[i])      // ถ้าค่าที่อ่านต่ำกว่า min เดิม
      val_min[i] = sensors_read[i];        // เก็บค่า min ใหม่
  }
}
//----------หมุนตัวบนพื้นขาวและดำ เพื่อเก็บค่า---------
void move_scan(int po)
{ clear_value();
  for (int counter = 0; counter < 500; counter++)
  {
    //    motor(po, -po);
    line_sensors_scan();        // สแกนทุกค่า counter  เพื่อเก็บค่า mzx min ของแต่ละตัว
    delay(10);             // หน่วงเวลา เพื่อให้ครอบคลุมพื้นที่ขาวและดำ
  }
  ao();
}
//********************* แสดงค่าเซนเซอร์แบบเรียลไทม์ ********************************
void Display_sensor(void)   //-----For BMV2
{
  OLED.setTextColor(WHITE, BLACK);
  OLED.clearDisplay();
  OLED.setTextSize(1);
  //----------Encoder------------- encoderR_pin = A0;  encoderL_pin = A1;
  OLED.setCursor(0, 48);
  if (digitalRead(A1))
    OLED.print("");
  else
    OLED.print("H");

  OLED.setCursor(116 + 4, 48);
  if (digitalRead(A0))
    OLED.print(" ");
  else
    OLED.print("H");
  //-----------------------------
  OLED.setCursor(0, 0);       OLED.print("  xA3     xA2    xA1");
  //  OLED.setCursor(0, 37);      OLED.print("     A3       A2");

  OLED.setCursor(0, 37);      OLED.print("A1   A3       A2   A0");
  //-------------------
  OLED.setTextSize(2);
  OLED.setCursor(00, 12);    OLCD_putblank(checkSensors(0));
  OLED.setCursor(45, 12);    OLCD_putblank(checkSensors(1));
  OLED.setCursor(90, 12);    OLCD_putblank(checkSensors(2));
  OLED.setCursor(18, 48);    OLCD_putblank(checkSensors(3));
  OLED.setCursor(71, 48);    OLCD_putblank(checkSensors(4));
  OLED.display();
}
void Calibrate_MODE(int p)
{
  //------------- แสดงข้อความก่อน Calibrate -------------
  OLED.setTextSize(2);
  OLED.setCursor(10, 25);   OLED.print("Calibrate");
  OLED.display();
  beep();   delay(1500);
  //------------- Calibrate -------------
  move_scan(p);    // อ่านค่า Max Min ขณะที่หมุนบนเส้นดำ ความเร็ว 40%
  write_EEprom();     // บันทึกค่าลงในหน่วยความจำ
  beep(); delay(500);
  beep();
}
//------------- รอกด OK พร้อมแสดงค่าที่ Calibrate -------------
void OK_Calibrate(void)
{
  read_EEprom();

  while (press_OK())
  {
    Display_EEprom();
    Display_sensor();   // แสดงค่าเซนเซอร์แบบเรียลไทม์
    delay(200);
  }
  beep();
  OLED.clearDisplay();
  show_CP32();
  delay(500);
}


int checkSensors(int i)   // ใช้สำหรับอ่านค่าเซนเซอร์ และรีเทรินค่าที่ map ค่าแล้ว
{
  sensors[i] = analog(pp[i]);           // อ่านค่าเซนเซอร์
  sensors[i] = map(sensors[i], val_min[i], val_max[i], 0, 1000);    // ปรับสเกล 0-1000
  sensors[i] = constrain(sensors[i], 0, 999);      // กำหนดขอบเขตให้ค่าระหว่าง 0-1000
  return sensors[i];
}
void check_all(void)    // อ่านค่าเซนเซอร์ทั้งหมดตามจำนวนในค่า NUM_SENSORS
{
  for (int i = 0; i < NUM_SENSORS - 1; i++)
  {
    checkSensors(i);
  }
}
//----------------- save memory -----------------
void write_EEprom(void)
{
  for (int h = 0; h <= NUM_SENSORS - 1 ; h++) {
    int add;
    add = h * 2;
    eeprom_write_word(add, val_max[h]);
    delay(5);
    add = 0x40 + (h * 2) ;
    eeprom_write_word(add, val_min[h]);
    delay(5);
  }
}
//----------------- read memory -----------------
void read_EEprom(void)
{
  for (int h = 0; h <= NUM_SENSORS - 1 ; h++)
  {
    int add;
    add = h * 2;
    val_max[h]  =  eeprom_read_word(add);
    delay(5);
    add = 0x40 + (h * 2);
    val_min[h]  =  eeprom_read_word(add);
    delay(5);
  }
}
//----------------- แสดงค่าบน Serial Monitor -----------------
void Display_EEprom(void)
{
  static int count1 = 0 ;
  ln_1();
  Serial.print("\n  ");
  Serial.print(++count1 , DEC);
  Serial.print("\t");
  for (int h = 0; h <= NUM_SENSORS - 1 ; h++)
  {
    char c = pp[h] ;
    if (c < 20)
    {
      Serial.print(" A");
      Serial.print(c, DEC);
    } else if (c >= 100)      //-----------XA
    {
      Serial.print(" xA");
      Serial.print(c - 100, DEC);
    }
    Serial.print("\t");
  }
  Serial.print("\n  ADC: ");
  for (int h = 0; h <= NUM_SENSORS - 1 ; h++)
  {
    char c = pp[h] ;
    Serial.print(" ");
    Serial.print(analog(c), DEC);
    Serial.print("\t");
  }
  ln_1();
  Serial.print("\nIndex: ");
  for (int h = 0; h <= NUM_SENSORS - 1 ; h++)
  {
    Serial.print(" ");
    Serial.print(h, DEC);
    Serial.print("\t");
  }

  Serial.print("\n  MAX:  ");
  for (int h = 0; h <= NUM_SENSORS - 1 ; h++)
  { Serial.print(val_max[h]);
    Serial.print("\t");
  }

  Serial.print("\n  MIN:  ");
  for (int h = 0; h <= NUM_SENSORS - 1 ; h++)
  { Serial.print(val_min[h]);
    Serial.print("\t");
  }

  Serial.print("\n Curr:  ");
  for (int h = 0; h <= NUM_SENSORS - 1 ; h++)
  { Serial.print(checkSensors(h));
    Serial.print("\t");
  }
  Serial.print("\n\n");
}
//-----------------------------------------------------------
void ln_1(void)
{
  Serial.print("\n        ");
  for (int h = 0; h <= NUM_SENSORS - 1 ; h++)
    Serial.print("--------");
}
//=============================================
void OLCD_putblank( int val)
{
  val = constrain(val, 0, 999);
  if (val < 10)
    OLED.print("  ");
  else   if (val >= 10 && val < 100 )
    OLED.print(" ");
  OLED.print(val , DEC);
}
//=============================================
