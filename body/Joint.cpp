#include "Joint.h"


Joint::Joint(Adafruit_PWMServoDriver pwm, uint8_t pin, float zeroPulse, bool positive) : 
  _pwm(pwm), _pin(pin), _zeroPulse(zeroPulse), _positive(positive) 
{
  _currentPosition = 0;  
}


void Joint::moveTo(float degree) 
{ 
  float pulse = degree * DEGTOSEC / PULSELEN;
  if (!_positive) pulse *= -1;
  pulse += _zeroPulse;

  if (pulse < SERVOMIN || pulse > SERVOMAX) return;

  _currentPosition = degree;
  _pwm.setPWM(_pin, 0, pulse);
}


void Joint::moveBy(float degree) 
{ 
  moveTo(_currentPosition + degree);
}

