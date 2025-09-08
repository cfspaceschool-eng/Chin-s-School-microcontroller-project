#ifndef _KG_GO_H_
#define _KG_GO_H_
#if defined(ARDUINO) || (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
////////////////////////////////////////////////////////////////////////////////////////////
#include <KG_MOTOR.h>
// Recall FuncTion SET_PIN(3,9,8,7,6,11);
////////////////////////////////////////////////////////////////////////////////////////////
#endif


void GO(void)
{
int X = 0;
pinMode(12,INPUT);    
digitalWrite(12,HIGH);  
while(1)
 {
   X= digitalRead(12); 
   if (X ==HIGH)
	   {
	     //digitalWrite(led,HIGH); 
	   }
   else
	   {
         digitalWrite(X, LOW); 
         break;
	   }
 }

SET_PIN(3,9,8,6,7,11); //Connection function MOTOR  Or borad controller  (pwa,in1,in2,in3,in4,pwb) 
//SET_PIN(3,9,8,7,6,11);>> OK

}
#endif
