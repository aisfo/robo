#include <SoftwareSerial.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

/* math constants */
#define SERVOMIN  150
#define SERVOMAX  570
#define FREQUENCY 60
#define DEGTOSEC 0.0088
#define PULSELEN 0.00406901042 // 1000 / FREQUENCY / 4096

/* joint ids */
#define ne0 0
#define ne1 1
#define ne2 2
#define se0 3
#define se1 4
#define se2 5
#define sw0 6
#define sw1 7
#define sw2 8
#define nw0 9
#define nw1 10
#define nw2 11

/* command codes */
#define RESET 1
#define MOVE_TO 2
#define MOVE_BY 3
#define READ_ORIENT 4


class Joint {
  uint8_t _pin;
  float _zeroPulse;
  bool _positive;
  float _currentPosition;
  static Adafruit_PWMServoDriver _pwm;

  public:
    Joint(uint8_t pin, float zeroPulse, bool positive) {
      _pin = pin;
      _zeroPulse = zeroPulse;
      _positive = positive; 
      _currentPosition = 0;  
    }

    void moveTo(float degree) { 
      if (_pin == UINT8_MAX) return; //not initialized
      
      float pulse = degree * DEGTOSEC / PULSELEN;
      if (!_positive) pulse *= -1;
      
      pulse += _zeroPulse;
  
      if (pulse < SERVOMIN || pulse > SERVOMAX) return;

      _currentPosition = degree;
  
      _pwm.setPWM(_pin, 0, pulse);
    }

    void moveBy(float degree) { 
      moveTo(_currentPosition + degree);
    }

    static void begin() {
      _pwm.begin();
      _pwm.setPWMFreq(FREQUENCY);
    }
};

Adafruit_PWMServoDriver Joint::_pwm = Adafruit_PWMServoDriver();

SoftwareSerial bluetooth(11, 10); // RX, TX
Adafruit_BNO055 bno = Adafruit_BNO055(55);

Joint joints[12] {
  Joint(2, 565, true), //ne0
  Joint(1, 150, true), //ne1
  Joint(0, 170, false),//ne2

  Joint(6, 159, true), //se0
  Joint(5, 555, false),//se1
  Joint(4, 535, true), //se2

  Joint(8, 540, true),  //sw0
  Joint(9, 170, true),  //sw1
  Joint(11, 180, false),//sw2

  Joint(13, 154, true), //nw0
  Joint(14, 560, false),//nw1
  Joint(15, 524, true)  //nw2
};

void reset() {
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

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  Joint::begin();
  bno.begin();

  delay(500);
  
  bno.setExtCrystalUse(true);

  reset();
}


void loop() {
  
  if (bluetooth.available()) {
    uint8_t command = bluetooth.parseInt();
    uint8_t jointId;
    float value;
    
    switch (command) {
      case MOVE_TO:
      case MOVE_BY:
        jointId = bluetooth.parseInt();
        value = bluetooth.parseFloat();
        break;
      case RESET:
        reset();
        return;
      case READ_ORIENT:
        sensors_event_t event; 
        bno.getEvent(&event);
        bluetooth.print("\x02"); // start of text
        bluetooth.print(event.orientation.x, 4);
        bluetooth.print("\x1f"); // value separator
        bluetooth.print(event.orientation.y, 4);
        bluetooth.print("\x1f"); // value separator
        bluetooth.print(event.orientation.z, 4);
        bluetooth.print("\x03"); // end of text
        return;
    }

    if (jointId < 0 || jointId > 11) return;
   
    switch (command) {
      case MOVE_TO:
        joints[jointId].moveTo(value);     
        break;
      case MOVE_BY: 
        joints[jointId].moveBy(value);     
        break;
    }
  }

  delay(50);
}
