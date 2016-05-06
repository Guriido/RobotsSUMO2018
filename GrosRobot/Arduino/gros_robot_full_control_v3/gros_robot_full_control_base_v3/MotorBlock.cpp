#include <Arduino.h>
#include "MotorBlock.h"

MotorBlock::MotorBlock(int dir,int brake,int pwm, int encoderA, int encoderB) : D(dir), B(brake), P(pwm), pinA(encoderA), pinB(encoderB), encoderPos(0), targetSpeed(0), currSpeed(0)
{}

void MotorBlock::init()
{
  pinMode(D, OUTPUT); //Init Direction
  pinMode(B, OUTPUT); //Init Frein 
  pinMode(P, OUTPUT); //Init PWM 
}

void MotorBlock::setSpeed(double targetSpeedRequired){
  targetSpeed = targetSpeedRequired;
}

void MotorBlock::run()
{
  currSpeed = nbTopsDone * 0.3330 / (50);
  nbTopsDone = 0;
  float cmd = (targetSpeed - currSpeed) * 200;
  
  // Offset
  cmd += ((cmd > 0) - (cmd < 0)) * OFFSET;
  
  // Saturation
  cmd = constrain(cmd, -255, 255);
  
  cmdDEBUG = cmd;
  
  
  digitalWrite(D, cmd > 0 ? LOW : HIGH);

  analogWrite(P, abs(cmd));
}
