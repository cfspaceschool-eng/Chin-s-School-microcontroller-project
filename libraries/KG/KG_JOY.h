#ifndef _KG_JOY_H_
#define _KG_JOY_H_
#if defined(ARDUINO) || (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"

#include <doit_moter.h>
#include <PS2X_lib.h>

#endif


volatile int vibrate;
#define PWMA 9
#define DIRA 8
#define PWMB 6
#define DIRB 7
#define PWMC 5
#define DIRC 4
#define PWMD 3
#define DIRD 2

#define PS2_DAT 13
#define PS2_CMD 11
#define PS2_CS  10
#define PS2_CLK 12
MOTER moter;
PS2X ps2x;

void STOPP() 
{
moter.setspeed(1,0,0);
moter.setspeed(2,0,0);
moter.setspeed(3,0,0);
moter.setspeed(4,0,0);
}

void FORWARD() 
{
moter.setspeed(1,1,255);
moter.setspeed(2,1,255);
moter.setspeed(3,1,255);
moter.setspeed(4,1,255);
}

void LEFT() 
{
moter.setspeed(1,0,127);
moter.setspeed(2,1,127);
moter.setspeed(3,0,127);
moter.setspeed(4,1,127);
}

void RIGHT() 
{
moter.setspeed(1,1,127);
moter.setspeed(2,0,127);
moter.setspeed(3,1,127);
moter.setspeed(4,0,127);
}

void BACK() 
{
moter.setspeed(1,0,255);
moter.setspeed(2,0,255);
moter.setspeed(3,0,255);
moter.setspeed(4,0,255);
}




void JOY(void)
{
  moter.init(PWMA,DIRA,PWMB,DIRB,PWMC,DIRC,PWMD,DIRD);
  vibrate = 0;
  Serial.begin(9600);
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_CS, PS2_DAT, true, true);


while(1)
{
  ps2x.read_gamepad(false,vibrate);
  if (ps2x.ButtonReleased(PSB_PAD_UP)||ps2x.ButtonReleased(PSB_PAD_RIGHT)||ps2x.ButtonReleased(PSB_PAD_DOWN)||ps2x.ButtonReleased(PSB_PAD_LEFT)) 
  {
    STOPP();
  }

  if (ps2x.ButtonPressed(PSB_PAD_UP)) 
  {
    //Serial.println("Up is being held:");
    FORWARD();
  }
  
  if (ps2x.ButtonPressed(PSB_PAD_RIGHT)) 
  {
    //Serial.println("Right is being held:");
    RIGHT();
  }
  
  if (ps2x.ButtonPressed(PSB_PAD_LEFT))
  {
    //Serial.print("Left is being held:");
    LEFT();
  }
  if (ps2x.ButtonPressed(PSB_PAD_DOWN)) 
  {
    //Serial.println("DOWM is being held:");
    BACK();
  }
delay(50);
   }
}
#endif
