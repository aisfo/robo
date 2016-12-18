#include "Joint.h"
#include "common.h"


class Robot {
  
  Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
  Joint joints[12] {
      Joint(2, 565, true),  //ne0
      Joint(1, 150, true),  //ne1
      Joint(0, 170, false), //ne2
    
      Joint(6, 159, true),  //se0
      Joint(5, 555, false), //se1
      Joint(4, 535, true),  //se2
    
      Joint(8, 540, true),  //sw0
      Joint(9, 170, true),  //sw1
      Joint(11, 180, false),//sw2
    
      Joint(13, 154, true), //nw0
      Joint(14, 560, false),//nw1
      Joint(15, 524, true)  //nw2
  };

  public:
    Robot();
    void begin();
    void reset();
    void moveTo(uint8_t jointId, float value);
    void moveBy(uint8_t jointId, float value);

};

