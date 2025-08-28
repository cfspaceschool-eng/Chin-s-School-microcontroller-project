int i=A0;
int data;
void setup() 
{
Serial.begin(9600);
pinMode(i,INPUT);

}

void loop() 
{
 data=analogRead(i);
 Serial.print("AnalogRead= ");
 Serial.println(data); delay(10);
}