//เขียนไลบารี่โดยครูกอล์ฟ สหพล อ่อนหลวง
#ifndef _KG_H_
#define _KG_H_
#if defined(ARDUINO) || (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "pins_arduino.h"
#include "wiring_private.h"
#ifndef ALL
#define ALL 100
#endif
#ifndef all
#define all 100
#endif   
#define ao() motor_stop(ALL)
#define sleep(x) delay(x)

//Main System>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <KG_servoMotor.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>            //connection oled
#include <Adafruit_SSD1306.h>        //connection oled
#include <LiquidCrystal_I2C.h>       // connect to lcd
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <KG_MOTOR.h>

#include <KG_GO.h>
#include <KG_LED.h>
#include <doit_moter.h>
#include <PS2X_lib.h>
#include <KG_BLUETOOTH.h>
#include <KG_JOY.h>


#endif
