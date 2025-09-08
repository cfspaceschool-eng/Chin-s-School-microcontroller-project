#ifndef _SV_H_        // EDIT  FOR V2.1  18/10/61
#define _SV_H_
#include <Sm.h>
#include "pins_arduino.h"
#ifndef ALL 
#define ALL 100
#endif
int sv1 = 7; // D7
int sv2 = 4; // D4
int pre1=1500;
//  Servo  SV1  SV2
Sm servo1 ;
Sm servo2 ;

void SV(char s, int angle)
{
  //--------------------- ALL ---------------------
  if (s == ALL)
  {
    if (angle == -1)
    {
      servo1.detach();
      servo2.detach();
    }
    else
    {
      if (angle >= 0 && angle <= 180)
      {
        if (!(servo1.attached()))    servo1.attach(sv1);
        if (!(servo2.attached()))    servo2.attach(sv2);
        servo1.write(angle);
        servo2.write(angle);
      }
    }
  }

  //--------------------- Servo 1 ---------------------
  if (s == 1)
  {
    if (angle == -1)
      servo1.detach();
    else
    {
      if (angle >= 0 && angle <= 180)
      {
        if (!(servo1.attached()))    servo1.attach(sv1);
        servo1.write(angle);
      }
    }
  }
  //--------------------- Servo 2 ---------------------
  if (s == 2)
  {
    if (angle == -1)    servo2.detach();
    else
    {
      if (angle >= 0 && angle <= 180)
      {
        if (!(servo2.attached()))    servo2.attach(sv2);
        servo2.write(angle);
      }
    }
  }

}
#endif

