#ifndef _KG2_H_
#define _KG2_H_
#include <util/delay.h>
#include <Arduino.h>
#include "pins_arduino.h"
//#include "wiring_private.h"
//#include <Adafruit_SSD1306.h>
#include <SV.h>
#include <motorDC.h>
/////////////////////////////////////////////
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

////////////////////////////////////////////

#define xa0  100
#define xa1  101
#define xa2  102
#define xa3  103
#define xa4  104
#define xa5  105
#define xa6  106
#define xa7  107
#define XA0  100
#define XA1  101
#define XA2  102
#define XA3  103
#define XA4  104
#define XA5  105
#define XA6  106
#define XA7  107

Adafruit_SSD1306 OLED(-1);
#define  in_1  10     //    POP-X2 2(RxD) ==> IN1 MPX8
#define  in_2  11     //    POP-X2 3(TxD) ==> IN2 MPX8
#define  in_4  12     //    POP-X2 8(SCL) ==> IN4 MPX8
#define  analog_out  A6    //    POP-X2 A5 ==> ANALOG OUT  MPX8

//void OK(char);



bool sta_beep=1;
 
void beep(void) {    //   return;
  int i = 200;
  int buz = 3;
  pinMode(buz , OUTPUT );
  while (i--) 
  {
    digitalWrite(buz , HIGH);  delayMicroseconds(400);
    digitalWrite(buz , LOW);   delayMicroseconds(70);
  }
}
void sbeep(void) 
{
  // return;
  int i = 200/4;
  int buz = 3;
  pinMode(buz , OUTPUT );
  while (i--) 
  {
    digitalWrite(buz , HIGH);  delayMicroseconds(400/2);
    digitalWrite(buz , LOW);   delayMicroseconds(70/2);
  }
}
 
void SET_ROBOT()
{

  pinMode(in_1 , OUTPUT);  digitalWrite(in_1, HIGH);
  pinMode(in_2 , OUTPUT);  digitalWrite(in_2, HIGH);
  pinMode(in_4 , OUTPUT);  digitalWrite(in_4, HIGH);
  pinMode(analog_out , INPUT);   // A6 A7  USE Input
  
  pinMode(2, OUTPUT);  digitalWrite(2, HIGH);

  pinMode(dirL, OUTPUT);   //L
  pinMode(enL, OUTPUT);
  analogWrite(enL, 0);

  pinMode(dirR, OUTPUT);  //R
  pinMode(enR, OUTPUT);
  analogWrite(enR, 0);

  pinMode( 7 , OUTPUT);  
  pinMode( 4 , OUTPUT);  
  //servo1.attach(sv1);
  //servo2.attach(sv2);
  //servo1.write(90);
  //servo2.write(90);

  Serial.begin(57600);
  Serial.println("Start......  ");  beep();

  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x64)
  OLED.setTextColor(WHITE, BLACK);
  OLED.setTextSize(2);  OLED.clearDisplay();

  //  OLED.setCursor(0, 0);
  //  OLED.print("OK..");
  //  OLED.display();
  beep();
} 
 
 
 

//======================== ANALOG SENSOR ==================================
unsigned int SonarSensor(void)
{
#define trigPin1 A1              //A5    
#define echoPin1 A2           //A4
  unsigned int duration, distance ;
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);  digitalWrite(echoPin1, HIGH);
  digitalWrite(trigPin1, LOW);      delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);     delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  distance = (duration / 2) / 29.1;
  return (distance);
}
//========================================================================
unsigned int XA(char sel)
{
  byte t ;
  t = sel & 0b001;
  if (t == 1)  digitalWrite(in_1, HIGH);  else  digitalWrite(in_1, LOW);
  t = sel & 0b010;
  if (t == 2)  digitalWrite(in_2, HIGH);  else  digitalWrite(in_2, LOW);
  t = sel & 0b100;
  if (t == 4)  digitalWrite(in_4, HIGH);  else  digitalWrite(in_4, LOW);
  return (analogRead(analog_out));
}
//==================================================================
unsigned int analog(int ch)
{ int x ;
  if (ch < 100)
  {
    return (analogRead(ch));
  }
  else
  {
    x = ch - 100;
    return (XA(x));
  }
}

int  pot(int _min, int _max)
{
  int in = analog(xa7);
  int in2 = map(in , 0 , 1000 , _min , _max) ;
  if (in2 > _max) in2 = _max;
  return (in2);
}
 
//========== ENCODER   ==============
void encoder_sb(int s )
{
  bool old_sta = 0  ;
  while (s) {
    if (analog(xa2) > 500) // >500 LED ดับ  // <500 LED ติด
    {
      if (old_sta) {
        old_sta = 0;
        s--;          sbeep();
      }
    } else old_sta = 1;
  }
   STOP(); delay(200);         ////  ****************************
}
//=============================================================
void encoder(int s )
{
  bool old_sta = 0  ;
  while (s) {
    if (analog(xa2) > 500) // >500 LED ดับ  // <500 LED ติด
    {
      if (old_sta) {
        old_sta = 0;
        s--;
      }
    } else old_sta = 1;
  }
   STOP(); delay(500);         ////  ****************************
}

void READ_SENSOR(void) 
{
pinMode(A0,INPUT); //L1
pinMode(A1,INPUT); //L2
pinMode(A2,INPUT); //R1
pinMode(A3,INPUT); //R2
while (1) 
 {
OLED.setTextSize(2);

OLED.setCursor(0, 0);
OLED.print("L1");
OLED.setTextSize(2);
OLED.setCursor(0, 20);
OLED.print(digitalRead(A0));
OLED.setCursor(0, 50);
OLED.print("A0");

OLED.setTextSize(2);
OLED.setCursor(30, 0);
OLED.print("L2");
OLED.setCursor(30, 20);
OLED.print(digitalRead(A1));
OLED.setCursor(30, 50);
OLED.print("A1");

OLED.setTextSize(2);
OLED.setCursor(60, 0);
OLED.print("R2");
OLED.setCursor(60, 20);
OLED.print(digitalRead(A3));
OLED.setCursor(60, 50);
OLED.print("A3");

OLED.setTextSize(2);
OLED.setCursor(90, 0);
OLED.print("R1");
OLED.setCursor(90, 20);
OLED.print(digitalRead(A2));
OLED.setCursor(90, 50);
OLED.print("A2");

OLED.display();
OLED.clearDisplay();
  }
}

void READ_POT(void) 
{

while (1) 
 {
int a = pot(0,100);	 
  OLED.clearDisplay();      // ล้างหนาจอ OLED
  OLED.setCursor(0, 0);     // กำหนดตำแหน่งแสดงผล x=0 , y=0
  OLED.print("POT%= ");   OLED.print( a , DEC);        // แสดงค่าของ pot 0-100
  OLED.setCursor(0, 20);  
  OLED.print("XA7 = ");   OLED.print( analog(XA7) , DEC);    // แสดงค่าของช่อง XA7
OLED.setCursor(0, 40);
OLED.print("0-1023");  
  OLED.display();           // เริ่มแสดงผลที่จอภาพ
  }
}

void POT_SV1(void) 
{

while (1) 
 {
int a = pot(0,100);	 
  OLED.clearDisplay();      // ล้างหนาจอ OLED
  OLED.setCursor(0, 0);     // กำหนดตำแหน่งแสดงผล x=0 , y=0
  OLED.print("POT%= ");   OLED.print( a , DEC);        // แสดงค่าของ pot 0-100
  OLED.setCursor(0, 20);  
  OLED.print("XA7 = ");   OLED.print( analog(XA7) , DEC);    // แสดงค่าของช่อง XA7

OLED.setCursor(0, 40);
OLED.print("0-1023");
  
  OLED.display();           // เริ่มแสดงผลที่จอภาพ
  SV(1,a); 
  }
}

void READ_BUTTON(void) 
{
  int sw_ok = 2 ;  STOP();
  pinMode(sw_ok , INPUT_PULLUP);  
while (1) 
 {
int b = digitalRead(sw_ok);	 
  OLED.clearDisplay();      // ล้างหนาจอ OLED
  OLED.setCursor(0, 0);     // กำหนดตำแหน่งแสดงผล x=0 , y=0
  OLED.print("BUTTON= ");   OLED.print( b , DEC);      
 
 OLED.setCursor(0, 30);  
  OLED.print(">> PULL_UP");   
  
  OLED.setCursor(0, 50);  
  OLED.print("PIN =D2");   
  OLED.display();           // เริ่มแสดงผลที่จอภาพ

  }
}


//=============================================================

//-----------------  OK  SW  --------------------
#include <GO.h>

 

 
#endif
