//รับค่าinput->output
//D5 input >> GND Logic>>0
int sw=5;//input
int led=2;//output
int data;//db
void setup() 
{
pinMode(sw,INPUT_PULLUP); //ทำงานบนสัญญาณ=กราว
pinMode(led,OUTPUT);
}

void loop() 
{
digitalWrite(sw,1); //ให้จ่ายไฟ3-5v
data=digitalRead(sw); //เก็บข้อมูลจากswว่า0/1
 if(data==0)
 {
  digitalWrite(led,1);
 }
 else 
 {
   digitalWrite(led,0);
 }
}