#include <KG2.h>
void FCKingTLV1(int speedL,int speedR)
{
  int L,R; 
    while(1)
    {
      pinMode(A0,INPUT);
      pinMode(A1,INPUT);
      L=digitalRead(A0); 
      R=digitalRead(A1);
      if(L==0 && R==0)
        {
         STOP();
         delay(5000);
         MD(40,40);
         delay(200);
         STOP();
         break; 
        }
          else if (L==0 && R==1)
            {
             ML(40); 
            }
              else if(L==1 && R==0)
              {
                MR(40);
              }
              else if(L==1 && R==1)
              {
                MD(40,40);
              }  
    }
}
void setup() 
{
OK();
FCKingTLV1(40,40);
}

void loop() 
{

}
