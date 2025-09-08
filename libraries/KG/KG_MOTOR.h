#ifndef _KG_MOTOR_H_
#define _KG_MOTOR_H_
#if defined(ARDUINO) || (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


int ENA,IN1,IN2,IN3,IN4,ENB;
int speed;
int motorLastSpeed = speed;

void SET_PIN(int ena,int in1,int in2,int in3,int in4,int enb) //ฟังก์ชั่นเซตขาต่อกับไดร์มอเตอร์ L298N, L293D ,หรือบอร์ดไดร์รุ่นอื่นๆ
{
  ENA = ena;
  IN1 = in1;
  IN2 = in2;
  IN3 = in3;
  IN4 = in4;
  ENB = enb;
}

void motor(uint8_t mtr, int8_t speed)
{
  signed int speedMotor;
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

if (speed >= -100 && speed <= 100)
  {
    motorLastSpeed = speed;
    speedMotor = (speed * 255) / 100;

    if (mtr == 1)
    {
      if (speed > 0)
      {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
      }
      else
      {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
      }
      analogWrite(ENA, abs(speedMotor));
    }
    if (mtr == 2)
    {
      if (speed > 0)
      {
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      }
      else
      {
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      }
      analogWrite(ENB, abs(speedMotor));
    }
    if (mtr == ALL)
    {
      if (speed > 0)
      {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      }
      else
      {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      }
      analogWrite(ENA, abs(speedMotor));
      analogWrite(ENB, abs(speedMotor));
    }
  }
}

void motor_stop(uint8_t ch)
{
  if (ch == 1)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(ENA, HIGH);
  }
  else if (ch == 2)
  {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    digitalWrite(ENB, HIGH);
  }
  else if (ch == ALL)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
  }
  motorLastSpeed = 0;
}

void motor(char ch, int speed, int step)
{
  int i;
  if (speed > motorLastSpeed)
  {
    for (i = motorLastSpeed; i <= speed; i++)
    {
      motor(ch, i);
      delay(step);
    }
    motorLastSpeed = speed;
  }
  else
  {
    for (i = motorLastSpeed; i >= speed; i--)
    {
      motor(ch, i);
      delay(step);
    }
    motorLastSpeed = speed;
  }
}

//////////////////////////////////////////////Use function //////////////////////////////////////////////////////////////////////
void FDD(int8_t speed)
{
  motor(1, speed);
  motor(2, speed);
}

void FLR(int8_t speed1, int8_t speed2)
{
  motor(1, speed1); //motor_L
  motor(2, speed2); //motor_R
}

void BKK(int8_t speed)
{
  motor(1, -speed);
  motor(2, -speed);
}

void BLR(int8_t speed1, int8_t speed2)
{
  motor(1, -speed1);
  motor(2, -speed2);
}

void TL(int8_t speed)
{
  motor(1, 0);
  motor(2, speed);
}

void TR(int8_t speed)
{
  motor(1, speed);
  motor(2, 0);
}

void SLL(int8_t speed)
{
  motor(1, -speed);
  motor(2, speed);
}

void SRR(int8_t speed)
{
  motor(1, speed);
  motor(2, -speed);
}

void STOP()
{
motor_stop(ALL);
}

#endif
