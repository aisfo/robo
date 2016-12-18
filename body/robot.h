#include "Joint.h"
#include "common.h"


class Robot {
  
  Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
  
  Joint joints[12] {
      Joint(pwm, 2, 565, true), //ne0
      Joint(pwm, 1, 150, true), //ne1
      Joint(pwm, 0, 170, false),//ne2
    
      Joint(pwm, 6, 159, true), //se0
      Joint(pwm, 5, 555, false),//se1
      Joint(pwm, 4, 535, true), //se2
    
      Joint(pwm, 8, 540, true),  //sw0
      Joint(pwm, 9, 170, true),  //sw1
      Joint(pwm, 11, 180, false),//sw2
    
      Joint(pwm, 13, 154, true), //nw0
      Joint(pwm, 14, 560, false),//nw1
      Joint(pwm, 15, 524, true)  //nw2
  };


  public:
    Robot();
    void begin();
    void reset();
    void moveTo(uint8_t jointId, float value);
    void moveBy(uint8_t jointId, float value);

};

