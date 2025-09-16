#include<KG2.h>
void setup()
{
OK();
 OLED.clearDisplay();
 OLED.setCursor(0,0);

}
void loop()
{

 OLED.print("10");
 delay(1000);
 OLED.display();
  delay(1000);
 OLED.clearDisplay();
 OLED.print("9");
  delay(1000);
 OLED.display();
  OLED.clearDisplay();
 OLED.print("8");
 OLED.display();
  OLED.clearDisplay();
   delay(1000);
 OLED.print("7");
 OLED.display();
  OLED.clearDisplay();
   delay(1000);
 OLED.print("6");
 OLED.display();
  OLED.clearDisplay();
   delay(1000);
 OLED.print("5");
 OLED.display();
  OLED.clearDisplay();
   delay(1000);
 OLED.print("4");
 OLED.display();
  OLED.clearDisplay();
   delay(1000);
 OLED.print("3");
 OLED.display();
  OLED.clearDisplay();
   delay(1000);
 OLED.print("2");
 OLED.display();
  OLED.clearDisplay();
   delay(1000);
 OLED.print("1");
 OLED.display();
}

