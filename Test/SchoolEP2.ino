int val=A0;
int led=13; //ขายาวต่อ13ขาสั่นต่อGND
int data;
void setup()
{
Serial.begin(9600);
pinMode(A0,INPUT);
pinMode(led,OUTPUT);
}
void loop()
{
  data=analogRead(val);
  Serial.println(data); delay(10);
  if(data>=600)
  {
    digitalWrite(led,1);
  }
  else
  {
    digitalWrite(led,0);
  }
}