int i;
int led=13;
char a,b;
void setup() 
{
Serial.begin(9600);
pinMode(led,OUTPUT);
}
void loop() 
{
if(Serial.available()>0)
{
  i=Serial.read();
  if(i=='a')
  {
    digitalWrite(led,1);
  }
    else if(i=='b')
  {
    digitalWrite(led,0);
  }
      else if(i=='c')
  {
    digitalWrite(led,1);
    delay(1);
    digitalWrite(led,0);
  }
}
}
