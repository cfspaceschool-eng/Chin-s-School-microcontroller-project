#ifndef _GO_H_
#define _GO_H_


#define LR  50
#define LCR  51
#define LLRR  52

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


void DIS_OLED(void)
{
  int dis = SonarSensor();
  if (dis > 60)  dis = -1;
//  OLED.setCursor( 0, 45);    OLED.print("Dis:    ");
  OLED.setCursor( 50, 45);    OLED.print(dis , DEC);
}
void SEN2_OLED(void)
{
  OLED.setTextSize(2);
  OLED.clearDisplay();
  OLED.setCursor(8, 0);
  OLED.print("L3 -- R0 ");
//  OLED.setCursor( 0, 20);    OLED.print("   ");
//  OLED.setCursor(75, 20);    OLED.print("   ");
  OLED.setCursor( 0, 20);    OLED.print(analog(3) , DEC);
  OLED.setCursor(75, 20);    OLED.print(analog(0) , DEC);
  DIS_OLED();
  OLED.display();
  //exit
}
void SEN3_OLED(void)
{
  OLED.setTextSize(2);
  OLED.clearDisplay();
  OLED.setCursor(8, 0);
  OLED.print("L3 -- R0 ");
//  OLED.setCursor( 0, 20);    OLED.print("   ");
//  OLED.setCursor(75, 20);    OLED.print("   ");
  OLED.setCursor( 0, 20);    OLED.print(analog(3) , DEC);
  OLED.setCursor(75, 20);    OLED.print(analog(0) , DEC);
  
  OLED.setCursor( 0, 45);    OLED.print("XA3:    ");
  OLED.setCursor( 50, 45);    OLED.print(analog(XA3) , DEC);
  
  
  OLED.display();
  //exit
}
void SEN4_OLED(void)
{
  
  OLED.clearDisplay();  
  OLED.setTextSize(1);
  OLED.setCursor( 35, 39); OLED.print("A7  XA3");
  OLED.setTextSize(2);
  OLED.setCursor(8, 0);  OLED.print("L3 -- R0 ");
  OLED.setCursor( 0, 20);    OLED.print(analog(3) , DEC);
  OLED.setCursor(75, 20);    OLED.print(analog(0) , DEC);  
  OLED.setCursor( 0, 50);    OLED.print(analog(A7) , DEC);
  OLED.setCursor(75, 50);    OLED.print(analog(XA3) , DEC);     
  OLED.display();
  //exit
}




void SEN1_OLED(int i)
{
  OLED.setTextSize(2);
  OLED.clearDisplay();  
  OLED.setCursor(8, 0);  
  if(i>=100)
  {
      OLED.print("XA"); OLED.print(i-100 , DEC);
  }else
  if(i<=7)
  {
      OLED.print("A"); OLED.print(i , DEC);
  }  
  OLED.print(":");    
  OLED.print(analog(i) , DEC);   OLED.print("   ");
  OLED.display();
  //exit
}


void GO1(int i)
{ OLED.clearDisplay();   OLED.display();
  int sw_ok = 2 ; STOP();
  pinMode(sw_ok , INPUT);  digitalWrite(sw_ok, HIGH);
  Serial.println("   === KG2 POWER ON ===  ");
  OLED.setCursor(0, 0);   OLED.print("OK > > >");
  OLED.setTextSize(4);
  OLED.setCursor(12, 25);     OLED.print("KG2");  
  OLED.display();        delay(1000);       
  while (digitalRead(sw_ok) == HIGH)
  {
            if (i == LR) 
               SEN2_OLED();
     else   if (i == LCR) 
               SEN3_OLED();               
     else   if (i == LLRR) 
               SEN4_OLED();                    
     else   if ( (i >= 100) && (i <= 107) || (i <= 7)) 
               SEN1_OLED(i);    
    delay(30);
  }
  beep();  delay(300);
  OLED.clearDisplay(); OLED.setTextSize(2);
  OLED.display();
  
  //exit
}


//-----------------------------------------------


void GO2(void)
{   OLED.clearDisplay();   OLED.display();
  int sw_ok = 2 ; STOP();
  pinMode(sw_ok , INPUT);  digitalWrite(sw_ok, HIGH);
  OLED.setCursor(0, 0);   OLED.print("OK.");
  OLED.setTextSize(4);
  Serial.println("   === KG2 POWER ON ===  ");
  OLED.setCursor(12, 25);     OLED.print("KG2");  //OLED.print("OK..");
  OLED.display();       delay(500);
  while (digitalRead(sw_ok) == HIGH)
  { OLED.setTextSize(2);
    OLED.setCursor(0, 0);   OLED.print("   ");
    OLED.display();  //delay(100);
    Serial.print(" \tDis: ");     Serial.print(SonarSensor() , DEC);
    Serial.print(" \tA7:  ");    Serial.print(analog(7) , DEC);
    Serial.print(" \tA3: ");    Serial.print(analog(3) , DEC);
    Serial.print(" \tA2: ");    Serial.print(analog(2) , DEC);
    Serial.print(" \tA1: ");    Serial.print(analog(1) , DEC);
    Serial.print(" \tA0: ");    Serial.print(analog(0) , DEC);
    Serial.println();
    OLED.setCursor(0, 0);   OLED.print("OK.");
    OLED.display();  delay(100);
  }
  beep();  delay(300);
  OLED.clearDisplay(); OLED.setTextSize(2);
  OLED.display();
}
//===================== 
 

bool press_OK(void)
{
            int sw_ok = 2 ; STOP();
            pinMode(sw_ok , INPUT);  digitalWrite(sw_ok, HIGH);
            
         if(digitalRead(sw_ok) == HIGH)  
                  return HIGH;
         else
                  return LOW;          // Press         
}



void show_CP32(void)
{
  OLED.setTextSize(4);
  OLED.setCursor(12, 25);   OLED.print("KG2");  
  OLED.setTextSize(2);      OLED.display();        
} 
 
 void OK(void)
{   
SET_ROBOT();
OLED.clearDisplay();   
OLED.display();

  int sw_ok = 2 ;  STOP();
  pinMode(sw_ok , INPUT);  digitalWrite(sw_ok, HIGH);
  OLED.setCursor(0, 0);   
  OLED.print("OK.");
  OLED.setTextSize(4);
  OLED.setCursor(12, 25);    
  OLED.print("KG2");  
  OLED.display();       
  delay(500);
  while (digitalRead(sw_ok) == HIGH)
  { 
    OLED.setTextSize(2);
    OLED.display();  

    OLED.setCursor(0, 0);   OLED.print("OK.");
    OLED.display();  delay(100);
  }
beep();  delay(100);

  OLED.clearDisplay(); 
  OLED.setTextSize(2);
  OLED.setCursor(18, 0);    
  OLED.print("SPARTAN");  
  OLED.setTextSize(2);
  OLED.setCursor(14, 30);    
  OLED.print("KRU_GOLF");  
  OLED.display();   
}
 
 
#endif
