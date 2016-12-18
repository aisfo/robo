#include "robot.h"



Robot::Robot() 
{

}

void Robot::begin() 
{
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  reset();
}

void Robot::reset() 
{
  joints[ne0].moveTo(0);
  joints[ne1].moveTo(140);
  joints[ne2].moveTo(-50);

  joints[se0].moveTo(0);
  joints[se1].moveTo(140);
  joints[se2].moveTo(-50);

  joints[sw0].moveTo(0);
  joints[sw1].moveTo(140);
  joints[sw2].moveTo(-50);

  joints[nw0].moveTo(0);
  joints[nw1].moveTo(140);
  joints[nw2].moveTo(-50);
}

void Robot::moveTo(uint8_t jointId, float value) 
{
  if (jointId < 0 || jointId > 11) return;
  joints[jointId].moveTo(value);
}

void Robot::moveBy(uint8_t jointId, float value) 
{
  if (jointId < 0 || jointId > 11) return;
  joints[jointId].moveBy(value);
}


