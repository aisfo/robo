#include "common.h"


/* Joint class */
/* encapsulates details of joint motors */
class Joint {
  const uint8_t _pin;
  const float _zeroPulse;
  const bool _positive;
  float _currentPosition;
  Adafruit_PWMServoDriver _pwm;

  public:
    Joint(Adafruit_PWMServoDriver pwm, uint8_t pin, float zeroPulse, bool positive);
    void moveTo(float degree);
    void moveBy(float degree);
};

