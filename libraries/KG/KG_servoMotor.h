#ifndef _KG_SERVOMOTOR_H_
#define _KG_SERVOMOTOR_H_
#include "Arduino.h"
#if defined (__AVR_ATmega16__) || defined (__AVR_ATmega32__) 
#include "KG_SoftwareServo.h"// editror br kru golf 2019 
// Update 28/03/2019 by KruGolf 

    #else
	#include "Servo.h"
    #if defined (_KG_H_)

	#define SERVO_B1 1
	#define SERVO_B2 2
	#define SERVO_B3 3
    #define SERVO_B4 4
	#define __IPSTservo13 A2    //Setpin digital pin5    servo1
	#define __IPSTservo14 A3     //Setpin analog A3   servo2
	#define __IPSTservo15 A4     //Setpin analog A4   servo3
	#define __IPSTservo16 A5     //Setpin analog A5   servo4
	Servo IPSTservo13;
	Servo IPSTservo14;
	Servo IPSTservo15;
	Servo IPSTservo16;	
///////////////////////////////////////////////////////////////////////////////////////////////
	void SV(uint8_t servo,signed int angle)
	{
///////////////////////////////////////////////////////////////
	  if (servo==SERVO_B1)
	  {
		if (angle==-1)
		{
		  IPSTservo13.detach();
		}
		else
		{
		  if (!(IPSTservo13.attached()))
		  {
			IPSTservo13.attach(__IPSTservo13);
		  }
		  IPSTservo13.write(angle);
		}
	  }
////////////////////////////////////////////////////////////////
	  if (servo==SERVO_B2)
	  {
		if (angle==-1)
		{
		  IPSTservo14.detach();
		}
		else
		{
		  if (!(IPSTservo14.attached()))
		  {
			IPSTservo14.attach(__IPSTservo14);
		  }
		  IPSTservo14.write(angle);
		}
	  }
///////////////////////////////////////////////////////////////

	  if (servo==SERVO_B3)
	  {
		if (angle==-1)
		{
		  IPSTservo15.detach();
		}
		else
		{
		  if (!(IPSTservo15.attached()))
		  {
			IPSTservo15.attach(__IPSTservo15);
		  }
		  IPSTservo15.write(angle);
		}
	  }
	
///////////////////////////////////////////////////////////////

	  if (servo==SERVO_B4)
	  {
		if (angle==-1)
		{
		  IPSTservo16.detach();
		}
		else
		{
		  if (!(IPSTservo16.attached()))
		  {
			IPSTservo16.attach(__IPSTservo16);
		  }
		  IPSTservo16.write(angle);
		}
	  }
	}

#endif
#endif
#endif
