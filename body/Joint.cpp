#include "Joint.h"


float pulseLen = 1000 / FREQUENCY / 4096;


Joint::Joint(uint8_t pin, float zeroPulse, bool positive) : 
  pin(pin), 
  zeroPulse(zeroPulse), 
  positive(positive), 
  currentPosition(0) 
{ }


void Joint::moveTo(Adafruit_PWMServoDriver pwm, float degree) 
{ 
  float pulse = degree * DEGTOSEC / pulseLen;
  
  if (!positive) 
    pulse *= -1;
    
  pulse += zeroPulse;

  if (pulse < SERVOMIN || pulse > SERVOMAX) return;

  currentPosition = degree;
  pwm.setPWM(pin, 0, pulse);
}


void Joint::moveBy(Adafruit_PWMServoDriver pwm, float degree) 
{ 
  moveTo(pwm, currentPosition + degree);
}

