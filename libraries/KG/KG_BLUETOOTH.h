#ifndef _KG_BLUETOOTH_H_
#define _KG_BLUETOOTH_H_
#if defined(ARDUINO) || (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
////////////////////////////////////////////////////////////////////////////////////////////
#include <KG_MOTOR.h>

////////////////////////////////////////////////////////////////////////////////////////////
#include <SoftwareSerial.h>

#endif




void TEST_BT(void)
	{
	SoftwareSerial mySerial(1,0);   // RX HC-06 , TX HC-06      กำหนดการการเชื่อมต่อ Bluetooth HC-06
	Serial.begin(9600);   
	while (!Serial);
	mySerial.begin(9600); 

	while(1)
		{
		if(mySerial.available()>=0)
		Serial.write(mySerial.read()>=0);
		if(Serial.available())
		mySerial.write(Serial.read()>=0);
		Serial.println("Rady...> GO >By KruGolf"); 
		delay(100);
		}
	}


void C_BT(void)//Chek data SerialRead from phone   >App Arduino bluetooth controller Mode switch 97>on  98>off
{
SoftwareSerial mySerial(1,0);   // RX HC-06 , TX HC-06      กำหนดการการเชื่อมต่อ Bluetooth HC-06
Serial.begin(9600);
int i;
while(1)
	{
		if(Serial.available()>0) 
		i=Serial.read();
	    Serial.println(i);
	    delay(500);
	}  
}


void CT_BT(void)//Chek data SerialRead from phone   *******UseApp >>>>>>>>> bluetooth Automation  
{
SoftwareSerial mySerial(1,0);   // RX HC-06 , TX HC-06      กำหนดการการเชื่อมต่อ Bluetooth HC-06
Serial.begin(9600);
int i;
pinMode(A4,OUTPUT);
pinMode(A5,OUTPUT);

while(1)
	{
		if(Serial.available()>0) 
		i=Serial.read();
	    //Serial.println(data);

		if(i==65)
		{
			digitalWrite(A4,0);
		}
		else if(i==97)
		{
			digitalWrite(A4,1);
		}

		else if(i==66)
		{
			digitalWrite(A5,1);
		}
		else if(i==98)
		{
			digitalWrite(A5,0);
		}
		else if(i==10)
		{
			//break;
		}
	    delay(100);
	}  
}



////////////////////////////////////////////////////////////////////////////////////////
/* >App Arduino bluetooth controller Mode Controller 
แผงควบคุมทิศทาง
ตรง          ค่าจากการอ่านผ่าน Serial.read > ตั้งค่า a>97
กลับหลัง      ค่าจากการอ่านผ่าน Serial.read >  ตั้งค่า b>98
ซ้าย         ค่าจากการอ่านผ่าน Serial.read > ตั้งค่า c>99
ขวา         ค่าจากการอ่านผ่าน Serial.read > ตั้งค่า d>100
128 == STOP
*/
void DRIVE_BT(void)
{

SoftwareSerial mySerial(1,0);   // RX HC-06 , TX HC-06      กำหนดการการเชื่อมต่อ Bluetooth HC-06
Serial.begin(9600);
SET_PIN(5,7,8,12,13,6);  // pwmA in1 in2 in3 in4 pwmB
int data;
while(1)
	{

	if(Serial.available()>0) 
	{
	    data = Serial.read();
	}
	////////////////////////////////////////////////////////////////////
	switch (data)
	{
	    case '*':{STOP();   Serial.println("STOP\n"); delay(200); data = '*';} break;
	    case 'D':{SRR(100); Serial.println("SRR\n");  delay(200); data = '*';} break;
	    case 'C':{SLL(100); Serial.println("SLL\n");  delay(200); data = '*';} break; 
	    case 'B':{BKK(100); Serial.println("BKK\n");  delay(200); data = '*';} break;
	    case 'A':{FDD(100); Serial.println("FDD\n");  delay(200); data = '*';} break;

	}
	////////////////////////////////////////////////////////////////////	  	  
	}
}









#endif
