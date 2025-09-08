#ifndef _motorDC_H_
#define _motorDC_H_

int enL = 5;    //L
int dirL = 8;
int enR = 6;    //R
int dirR = 9;
 

//=====================================
//---------MOTOR USE ONLY--------------
void STOP()
{
  analogWrite(enL, 0);
  analogWrite(enR, 0);
}


void motorL(signed int x) 
{
  int L ;
  if (x >= -100 && x <= 100)
  {
    if (x >= 0)
      digitalWrite(dirL, LOW);  //L-fd
    else if (x < 0)
      digitalWrite(dirL, HIGH);  //L-rv

    L = abs(x) * 255 / 100;
    analogWrite(enL, L);
  } else analogWrite(enL, 0);
}
void motorR(signed int x) {
  int R ;
  if (x >= -100 && x <= 100)
  {
    if (x >= 0)
      digitalWrite(dirR, LOW);  //R-fd
    else if (x < 0)
      digitalWrite(dirR, HIGH);  //R-rv

    R = abs(x) * 255 / 100;
    analogWrite(enR, R);
  } else analogWrite(enR, 0);
}

/*
void motor(signed int x , signed int  y)
{
  motorL(x); motorR(y);
}
*/

void motor(signed int x , signed int  y)
{
  pinMode(dirL, OUTPUT);   //L
  pinMode(dirR, OUTPUT);  //R
int L , R ;      
      if(x>=-100 && x<=100 && y>=-100 && y<=100 )      
      {       
         if(x>=0) 
         {
              digitalWrite(dirL, LOW);  //L-fd      
         }        
         if(x< 0) 
         {
              digitalWrite(dirL, HIGH);  //L-rv
         }
         
         if(y>=0) 
          {
              digitalWrite(dirR, LOW);  //R-fd  
          }          
         if(y< 0) 
         {
              digitalWrite(dirR, HIGH);  //R-rv
         }             
          L=abs(x)*255/100;
          R=abs(y)*255/100;                  
           analogWrite(enL,L);
           analogWrite(enR,R);                   
      }
} 

//USE ONLY By Kru Golf

////////////////////////////////////////////////////
//ตรงไป
void MD(int powerL ,  int  powerR)
{
motor(powerL, powerR);
} 
////////////////////////////////////////////////////
//ถอยหลัง
void MB(int powerL ,  int  powerR)
{
motor(-powerL, -powerR);
} 
////////////////////////////////////////////////////
//หมุนซ้าย
void ML(int power )
{
motor(-power, power);
} 
////////////////////////////////////////////////////
//หมุนขวา
void MR(int power)
{
motor(power, -power);
} 


#endif
