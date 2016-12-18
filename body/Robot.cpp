#include "robot.h"


Robot::Robot() 
{ }


void Robot::begin() 
{
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  reset();
}


void Robot::reset() 
{
  joints[NE0].moveTo(pwm, 0);
  joints[NE1].moveTo(pwm, 140);
  joints[NE2].moveTo(pwm, -50);

  joints[SE0].moveTo(pwm, 0);
  joints[SE1].moveTo(pwm, 140);
  joints[SE2].moveTo(pwm, -50);

  joints[SW0].moveTo(pwm, 0);
  joints[SW1].moveTo(pwm, 140);
  joints[SW2].moveTo(pwm, -50);

  joints[NW0].moveTo(pwm, 0);
  joints[NW1].moveTo(pwm, 140);
  joints[NW2].moveTo(pwm, -50);
}


void Robot::moveTo(uint8_t jointId, float value) 
{
  if (jointId < 0 || jointId > 11) return;
  joints[jointId].moveTo(pwm, value);
}


void Robot::moveBy(uint8_t jointId, float value) 
{
  if (jointId < 0 || jointId > 11) return;
  joints[jointId].moveBy(pwm, value);
}


