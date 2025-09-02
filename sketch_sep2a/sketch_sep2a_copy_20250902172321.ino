int ss=A0;
int db;
void setup() {
Serial.begin(9600);
pinMode(ss,INPUT);

}

void loop() {
db=analogRead(ss);
Serial.print("Sensor just read this fucking data:");
Serial.println(db); delay(50);
}
