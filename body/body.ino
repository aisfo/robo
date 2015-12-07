#include <SoftwareSerial.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define SERVOMIN  150
#define SERVOMAX  570
#define FREQUENCY 60
#define DEGTOSEC 0.0088
#define PULSELEN 0.00406901042 // 1000 / FREQUENCY / 4096

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

#define MOVE_TO 1
#define MOVE_BY 2


class Joint {
  uint8_t _pin;
  float _zeroPulse;
  bool _positive;
  float _currentPosition;
  static Adafruit_PWMServoDriver _pwm;

  public:
    Joint() {
      _pin = UINT8_MAX;
    }

    Joint(uint8_t pin, float zeroPulse, bool positive, float initialPosition) {
      _pin = pin;
      _zeroPulse = zeroPulse;
      _positive = positive;   
      _currentPosition = initialPosition;
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
Joint joints[12];

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  Joint::begin();
  bno.begin();

  delay(500);
  
  bno.setExtCrystalUse(true);

  
  joints[ne0] = Joint(2, 565, true, -45);
  joints[ne1] = Joint(1, 150, true, 120);
  joints[ne2] = Joint(0, 170, false, -30);

  joints[se0] = Joint(6, 154, true, 45);
  joints[se1] = Joint(5, 550, false, 120);
  joints[se2] = Joint(4, 535, true, -30);

  joints[sw0] = Joint(8, 540, true, -45);
  joints[sw1] = Joint(9, 170, true, 120);
  joints[sw2] = Joint(11, 180, false, -30);

  joints[nw0] = Joint(13, 154, true, 45);
  joints[nw1] = Joint(14, 565, false, 120);
  joints[nw2] = Joint(15, 524, true, -30);
}


void loop() {
  //  sensors_event_t event; 
  //  bno.getEvent(&event);
    
  //  Serial.print("Azimuth: ");
  //  Serial.print(event.orientation.x, 4);
  //  Serial.print("\tPitch: ");
  //  Serial.print(event.orientation.y, 4);
  //  Serial.print("\tRoll: ");
  //  Serial.print(event.orientation.z, 4);
  //  Serial.println("");
  
  if (bluetooth.available()) {
    uint8_t command = bluetooth.parseInt();
    uint8_t jointId;
    float value;

    Serial.println(command);
    
    switch (command) {
      case MOVE_TO:
      case MOVE_BY:
        jointId = bluetooth.parseInt();
        value = bluetooth.parseFloat();
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

  delay(100);
}
