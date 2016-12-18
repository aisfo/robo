#include "common.h"


/* Joint class */
/* encapsulates details of joint motors */
class Joint {
  
  const uint8_t pin;
  const float zeroPulse;
  const bool positive;
  float currentPosition;

  public:
    Joint(uint8_t pin, float zeroPulse, bool positive);
    void moveTo(Adafruit_PWMServoDriver pwm, float degree);
    void moveBy(Adafruit_PWMServoDriver pwm, float degree);
    
};

