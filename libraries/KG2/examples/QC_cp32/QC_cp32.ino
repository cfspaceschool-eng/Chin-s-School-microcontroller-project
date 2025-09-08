//---------- CP-32 Training Board ---------------
//---- https://www.facebook.com/mnrobot/ --------
//-------- โปรแกรมทดสอบการทำงานของบอร์ด CP-32 --------
#include <CP32.h>     // เรียกใช้ไลบารี่ของ CP32
void setup() {
  set_robot();        // กำนหนดค่าของบอร์ด CP32
  OK();               // หยุดรอกดสวิคช์ OK เพื่อเริ่มโปรแกรม
}
void loop() {
  ALL_SEN();
}
//------------------- ฟังก์ชั่นทดสอบอุปกรณ์ -------------------
void ALL_SEN(void)
{
  OLED.setTextColor(WHITE, BLACK);
  OLED.setTextSize(1);   OLED.clearDisplay();

  OLED.setCursor( 62, 0);   OLED.print(analog(xa3) , DEC);
  OLED.setCursor( 95, 0);   OLED.print(analog(xa2) , DEC);
  OLED.setCursor( 62, 9);   OLED.print(analog(xa1) , DEC);
  OLED.setCursor( 95, 9);   OLED.print(analog(xa0) , DEC);

  OLED.setCursor( 100, 28);  OLED.print(analog(xa4) , DEC);
  OLED.setCursor( 100, 40);  OLED.print(analog(xa5) , DEC);
  OLED.setCursor( 100, 52);  OLED.print(analog(xa6) , DEC);

  OLED.setCursor( 71, 43 + 4);  OLED.print("POT");
  OLED.setCursor( 70, 52 + 4);  OLED.print(analog(xa7) , DEC);

  OLED.setCursor( 15, 24);   OLED.print("L:");  OLED.print(analog(3) , DEC);
  OLED.setCursor( 55, 24);   OLED.print("R:");  OLED.print(analog(0) , DEC);
  OLED.setCursor(  0, 36);      OLED.print(":");  OLED.print(analog(7) , DEC);

  OLED.setTextSize(2);
  if (digitalRead(2) == HIGH)
  {
    OLED.setCursor( 5, 0);  OLED.print("HI ");
  }
  else
  { beep();
    OLED.clearDisplay(); OLED.display();
    OLED.setCursor( 5, 0);  OLED.print("LOW");
    OLED.setCursor( 0, 49);  OLED.print(":L MOTOR");
    OLED.display();
    motorL(80);     delay(3000);
    motorL(-80);    delay(3000);
    ao();           beep();
    OLED.setCursor( 0, 49);  OLED.print(":R MOTOR");
    OLED.display();
    motorR(80);     delay(3000);
    motorR(-80);    delay(3000);
    ao();

    beep();
    OLED.setCursor( 0, 49);  OLED.print("SERVO SV1 ");
    OLED.display();
    servo1.attach(sv1);
    servo1.write(30);  delay(1000);
    servo1.write(90);  delay(1000);
    servo1.write(120); delay(1000);

    beep();
    OLED.setCursor( 0, 49);  OLED.print("SERVO SV2 ");
    OLED.display();
    servo2.attach(sv2);
    servo2.write(30);  delay(1000);
    servo2.write(90);  delay(1000);
    servo2.write(120); delay(1000);
    servo1.detach();
    servo2.detach(); beep();
  }
  int dis = SonarSensor();
  if (dis > 60)  dis = -1;
  OLED.setTextColor(BLACK, WHITE);
  OLED.setCursor( 17, 49);  OLED.print(":"); OLED.print(dis , DEC);
  OLED.display();
  delay(1);
}
