//-------------------------------------
//-----------MOTOR BO1  1:120-----------
//-------------------------------------
int sen_FL = 0;     // ด้านหน้าซ้าย
int sen_FC = 1;     // ด้านหน้ากลาง  เช็คเส้นดำด้านหน้า(กำแพง)
int sen_FR = 2;     // ด้านหน้าขวา
int sen_RL = 3;     // ด้านหลังซ้าย
int sen_RR = 4;     // ด้านหลังขวา
void set_BM_V2(void)
{
  pinMode(A0, INPUT);   digitalWrite(A0, HIGH);     // Encoder R
  pinMode(A1, INPUT);   digitalWrite(A1, HIGH);     // Encoder L
  pinMode(A2, INPUT);
}
//===========================================================================
//=============ส่วนฟังก์ชั่นสำหรับใช้งาน ============================================
//===========================================================================
void track_wall(int p)      //    แทรกเส้นดำด้านข้าง และถอยหลังเมื่อเซนเซอร์ด้านหน้าเจอสีดำ
{
  while (checkSensors(sen_FC) > thresholdValue) track_w(p); //  เมื่อเซนเซอร์ด้านหน้าเจอสีดำ จะถอยหลัง
  ao();  delay(300);
  motor(-p, -p);  delay(200);      //  ถอยหลังออกจากเส้นดำ
  ao();  delay(50);
}
void track_w(int p)       //  แทรกเส้นดำด้านข้าง
{
  int L = checkSensors(sen_FL);
  int R = checkSensors(sen_FR);
  if ( L > thresholdValue && R > thresholdValue)
  {
    motor(p, p);
  }
  else    if ( L < thresholdValue && R > thresholdValue)
  {
    motor(p, -p);  delay(50);      // ดีเลย์สำหรับการหมุน  ปรับเปลี่ยนได้
    motor(p, p);  delay(5);
  }
  else    if ( L > thresholdValue && R < thresholdValue)
  {
    motor(-p, p); delay(50);       // ดีเลย์สำหรับการหมุน  ปรับเปลี่ยนได้
    motor(p, p);  delay(5);
  }
}
//---------------ปรับตำแหน่งหุ่นยนต์โดยใช้เซนเซอร์ด้านหน้า-----------------------------
void setbot_front(int p)
{ char di = 'N';
  motor(p, p);           // เดินตรงเข้าหาเส้น  เพื่อเช็คว่าหุ่นยนต์เอียงไปด้านใด
  while (1)
  { delay(1);
    if (checkSensors(sen_FL) < thresholdValue) di = 'L';
    if (checkSensors(sen_FR) < thresholdValue) di = 'R';
    if (di != 'N') break;
  }
  motor(-p, -p); delay(50);  ao();
  if (di == 'R')
  { beep();  delay(250);
    motor(p, 0);
    while (checkSensors(sen_FL) > thresholdValue) delay(5); //  โอเค
    motor(-p, 0); delay(50);
  }
  if (di == 'L')
  { beep();  delay(50);    beep();  delay(250);
    motor(0, p);
    while (checkSensors(sen_FR) > thresholdValue) delay(5);
    motor(0, -p); delay(50);
  }
  ao(); beep();  delay(200);
}
//---------------ปรับตำแหน่งหุ่นยนต์โดยใช้เซนเซอร์ด้านหลัง-------------------
void setbot_rear(int p)
{ p = p - 10;
  char di = 'N';
  motor(-p, -p);         // ถอยหลังเข้าหาเส้นดำ  เพื่อเช็คว่าหุ่นยนต์เอียงไปด้านใด
  while (1)
  { delay(1);
    if (checkSensors(sen_RL) < thresholdValue) di = 'L';
    if (checkSensors(sen_RR) < thresholdValue) di = 'R';
    if (di != 'N') break;
  }
  motor(p, p); delay(20);  ao();
  if (di == 'R')
  { beep();  delay(250);
    motor(-p, p - 10);
    while (checkSensors(sen_RL) > thresholdValue)   delay(5);
    motor(p, -p); delay(50);
  }
  if (di == 'L')
  { beep();  delay(50);    beep();  delay(250);
    motor(p - 10, -p);
    while (checkSensors(sen_RR) > thresholdValue)   delay(5);
    motor(-p, p); delay(50);
  }
  ao(); beep();  delay(200);
}

//-----------------หมุนตัว 90องศา ด้วย Encoder--------------------
void turn_R90(int p)    // ฟังก์ชั่นหมุนขวา 90 องศา
{
  RR_encoder(p, 10);    // 10 Step  กำหนดที่ 90 องศา  (ปรับเปลี่ยนได้ตามโครงสร้างหุ่นยนต์)
}
void turn_L90(int p)    // ฟังก์ชั่นหมุนซ้าย 90 องศา
{
  LL_encoder(p, 10);    // 10 Step  กำหนดที่ 90 องศา  (ปรับเปลี่ยนได้ตามโครงสร้างหุ่นยนต์)
}
//-----------------ชุดส่งกล่อง--------------------
void send_BOX(void)
{ pos_1();
  pos_2();
}
void pos_1(void)
{
  servo(1, 105);   //  ตำแหน่งเตรียมพร้อมปล่อยกล่อง
  delay(300);
}
void pos_2(void)
{
  servo(1, 10);   //  ตำแหน่งดันกล่องออกจากช่องเก็บ
  delay(500);     //  พักกล่องใบถัดไปไว้บนก้านส่งกล่อง
}

//============== ฟังก์ชั่น  เพิ่ม  สำหรับรวม CP32 ============================
void motorL_OFF()
{
  analogWrite(enL, 0);
}
void motorR_OFF()
{
  analogWrite(enR, 0);
}
//-----------------------62-------------------------------*******************************
int encoderR_pin = A0;
int encoderL_pin = A1;
void encoderL(int s )
{
  int old_sta = 0  ;
  while (s) {
    if (digitalRead(encoderL_pin))  // ä¿µÔ´ 500   ´Ñº ¤èÒÊÙ§
    {
      if (old_sta)
      { old_sta = 0;  s--;
        //Serial.println( s , DEC);
      }
    } else old_sta = 1;
  }
}
void encoderR(int s )
{
  int old_sta = 0  ;
  while (s) {
    if (digitalRead(encoderR_pin))  // ä¿µÔ´ 500   ´Ñº ¤èÒÊÙ§
    { if (old_sta)
      {
        old_sta = 0;
        s--;
      }
    } else old_sta = 1;
  }
}

void encoder_LR(int l , int r  )
{
  int old_sta6 = 0 , old_sta7 = 0  ;
  //========================================================
  while (l || r) {
    if (l > 0 && digitalRead(encoderL_pin) ) // ä¿µÔ´ 500   ´Ñº ¤èÒÊÙ§
    { //delayMicroseconds(200);
      if (old_sta7)
      { old_sta7 = 0;  l--;
        // Serial.print(" 7-"); Serial.println( l , DEC);
      }
    } else old_sta7 = 1;
    //========================================================
    if (r > 0 && digitalRead(encoderR_pin) ) // ä¿µÔ´ 500   ´Ñº ¤èÒÊÙ§
    { // delayMicroseconds(200);
      if (old_sta6)
      { old_sta6 = 0;  r--;
        //  Serial.print("           6-");  Serial.println( r , DEC);
      }
    } else old_sta6 = 1;
    //========================================================

    //--------------------------------------
    if (l == 0)  motorL_OFF();    //motorL(-30);
    if (r == 0)  motorR_OFF();    //motorR(-30);
  }
  //delay(50);   ao();  delay(200);         ////  ****************************
}


void FD_encoder(int p, int d)
{
  motor(p, p);  encoder_LR(d, d); //encoder(20);
  motor(-p, -p); delay(50);
  ao();    sbeep();  delay(100);
}
void RV_encoder(int p, int d)
{
  motor(-p, -p);  encoder_LR(d, d); //encoder(20);
  motor(p, p); delay(50);
  ao();    sbeep();  delay(100);
}
void RR_encoder(int p, int d)
{
  motor(p, -p);  encoder_LR(d, d); //encoder(20);
  motor(-p, p); delay(50);
  ao();    sbeep();  delay(100);
}
void LL_encoder(int p, int d)
{
  motor(-p, p);  encoder_LR(d, d); //encoder(20);
  motor(p, -p); delay(50);
  ao();    sbeep();  delay(100);
}























/*

//-------------------------------------
//-----------MOTOR BO1  1:48-----------
//-------------------------------------
int sen_FL = 0;     // ด้านหน้าซ้าย
int sen_FC = 1;     // ด้านหน้ากลาง  เช็คเส้นดำด้านหน้า(กำแพง)
int sen_FR = 2;     // ด้านหน้าขวา
int sen_RL = 3;     // ด้านหลังซ้าย
int sen_RR = 4;     // ด้านหลังขวา
//===========================================================================
//=============ส่วนฟังก์ชั่นสำหรับใช้งาน ============================================
//===========================================================================
void set_BM_V2(void)
{
  pinMode(A0, INPUT);   digitalWrite(A0, HIGH);     // Encoder R
  pinMode(A1, INPUT);   digitalWrite(A1, HIGH);     // Encoder L
  pinMode(A2, INPUT);
}
void track_wall(int p)      //    แทรกเส้นดำด้านข้าง และถอยหลังเมื่อเซนเซอร์ด้านหน้าเจอสีดำ
{
  while (checkSensors(sen_FC) > thresholdValue) track_w(p); //  เมื่อเซนเซอร์ด้านหน้าเจอสีดำ จะถอยหลัง
  ao();  delay(100);
  motor(-p, -p);  delay(300);  //  ถอยหลังออกจากเส้นดำ
  ao();  delay(50);
}
void track_w(int p)       //  แทรกเส้นดำด้านข้าง
{
  int L = checkSensors(sen_FL);
  int R = checkSensors(sen_FR);
  if ( L > thresholdValue && R > thresholdValue)
  {
    motor(p, p);
  }
  else
  {
    if ( L < thresholdValue && R > thresholdValue)
    {
      motor(15, -p);    delay(100 - p);     // ดีเลย์สำหรับการหมุน  ปรับเปลี่ยนได้ ใช้ motor(p, -p) กรณีทางระยะสั้น
      motor(p, p);      delay(p);
    }
    else    if ( L > thresholdValue && R < thresholdValue)
    {
      motor(-p, 15);    delay(100 - p);    // ดีเลย์สำหรับการหมุน  ปรับเปลี่ยนได้ ใช้ motor(-p, p) กรณีทางระยะสั้น
      motor(p, p);      delay(p);
    }
  }
}
//---------------ปรับตำแหน่งหุ่นยนต์โดยใช้เซนเซอร์ด้านหน้า-----------------------------
void setbot_front(int p)
{ char di = 'N';
  motor(p, p);           // เดินตรงเข้าหาเส้น  เพื่อเช็คว่าหุ่นยนต์เอียงไปด้านใด
  while (1)
  { delay(1);
    if (checkSensors(sen_FL) < thresholdValue) di = 'L';
    if (checkSensors(sen_FR) < thresholdValue) di = 'R';
    if (di != 'N') break;
  }
  motor(-p, -p); delay(50);  ao();
  if (di == 'R')
  { beep();  delay(250);
    motor(p + 5, 0);
    while (checkSensors(sen_FL) > thresholdValue) delay(5); //  โอเค
    motor(-p, 0); delay(50);
  }
  if (di == 'L')
  { beep();  delay(50);    beep();  delay(250);
    motor(0, p + 5);
    while (checkSensors(sen_FR) > thresholdValue) delay(5);
    motor(0, -p); delay(50);
  }
  ao(); beep();  delay(200);
}
//---------------ปรับตำแหน่งหุ่นยนต์โดยใช้เซนเซอร์ด้านหลัง-------------------
void setbot_rear(int p)
{ p = p - 5;
  char di = 'N';
  motor(-p, -p);         // ถอยหลังเข้าหาเส้นดำ  เพื่อเช็คว่าหุ่นยนต์เอียงไปด้านใด
  while (1)
  { //delay(1);
    if (checkSensors(sen_RL) < thresholdValue) di = 'L';
    if (checkSensors(sen_RR) < thresholdValue) di = 'R';
    if (di != 'N') break;
  }
  motor(50, 50); delay(200);
  ao(); delay(200);
  if (di == 'R')
  { beep();  delay(250);
    motor(-p, p+5);
    while (checkSensors(sen_RL) > thresholdValue)   delay(1);
    motor(p, -p); delay(20);
  }
  if (di == 'L')
  { beep();  delay(50);    beep();  delay(250);
    motor(p+5, -p);
    while (checkSensors(sen_RR) > thresholdValue)   delay(1);
    motor(-p, p); delay(20);
  }
  ao(); beep();  delay(200);
}

//-----------------หมุนตัว 90องศา ด้วย Encoder--------------------
void turn_R90(int p)    // ฟังก์ชั่นหมุนขวา 90 องศา
{
  RR_encoder(p + 5, 10);  // 10 Step  กำหนดที่ 90 องศา  (ปรับเปลี่ยนได้ตามโครงสร้างหุ่นยนต์)
}
void turn_L90(int p)    // ฟังก์ชั่นหมุนซ้าย 90 องศา
{
  LL_encoder(p + 5, 10);  // 10 Step  กำหนดที่ 90 องศา  (ปรับเปลี่ยนได้ตามโครงสร้างหุ่นยนต์)
}
//-----------------ชุดส่งกล่อง--------------------
void send_BOX(void)
{ pos_1();
  pos_2();
}
void pos_1(void)
{
  servo(1, 105);   //  ตำแหน่งเตรียมพร้อมปล่อยกล่อง
  delay(300);
}
void pos_2(void)
{
  servo(1, 10);   //  ตำแหน่งดันกล่องออกจากช่องเก็บ
  delay(500);     //  พักกล่องใบถัดไปไว้บนก้านส่งกล่อง
}

//============== ฟังก์ชั่น  เพิ่ม  สำหรับรวม CP32 ============================
void motorL_OFF()
{
  analogWrite(enL, 0);
}
void motorR_OFF()
{
  analogWrite(enR, 0);
}
//-----------------------62-------------------------------*******************************
int encoderR_pin = A0;
int encoderL_pin = A1;
void encoderL(int s )
{
  int old_sta = 0  ;
  while (s) {
    if (digitalRead(encoderL_pin))  // ä¿µÔ´ 500   ´Ñº ¤èÒÊÙ§
    {
      if (old_sta)
      { old_sta = 0;  s--;
        //Serial.println( s , DEC);
      }
    } else old_sta = 1;
  }
}
void encoderR(int s )
{
  int old_sta = 0  ;
  while (s) {
    if (digitalRead(encoderR_pin))  // ä¿µÔ´ 500   ´Ñº ¤èÒÊÙ§
    { if (old_sta)
      {
        old_sta = 0;
        s--;
      }
    } else old_sta = 1;
  }
}

void encoder_LR(int l , int r  )
{
  int old_sta6 = 0 , old_sta7 = 0  ;
  //========================================================
  while (l || r) {
    if (l > 0 && digitalRead(encoderL_pin) ) // ä¿µÔ´ 500   ´Ñº ¤èÒÊÙ§
    { //delayMicroseconds(200);
      if (old_sta7)
      { old_sta7 = 0;  l--;
        // Serial.print(" 7-"); Serial.println( l , DEC);
      }
    } else old_sta7 = 1;
    //========================================================
    if (r > 0 && digitalRead(encoderR_pin) ) // ä¿µÔ´ 500   ´Ñº ¤èÒÊÙ§
    { // delayMicroseconds(200);
      if (old_sta6)
      { old_sta6 = 0;  r--;
        //  Serial.print("           6-");  Serial.println( r , DEC);
      }
    } else old_sta6 = 1;
    //========================================================

    //--------------------------------------
    if (l == 0)  motorL_OFF();    //motorL(-30);
    if (r == 0)  motorR_OFF();    //motorR(-30);
  }
  //delay(50);   ao();  delay(200);         ////  ****************************
}


void FD_encoder(int p, int d)
{
  motor(p, p);  encoder_LR(d, d); //encoder(20);
  motor(-p, -p); delay(50);
  ao();    sbeep();  delay(100);
}
void RV_encoder(int p, int d)
{
  motor(-p, -p);  encoder_LR(d, d); //encoder(20);
  motor(p, p); delay(50);
  ao();    sbeep();  delay(100);
}
void RR_encoder(int p, int d)
{
  motor(p, -p);  encoder_LR(d, d); //encoder(20);
  motor(-p, p); delay(50);
  ao();    sbeep();  delay(100);
}
void LL_encoder(int p, int d)
{
  motor(-p, p);  encoder_LR(d, d); //encoder(20);
  motor(p, -p); delay(50);
  ao();    sbeep();  delay(100);
}


*/
