#include <SoftwareSerial.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define SERVOMIN  150
#define SERVOMAX  570
#define FREQUENCY 60
#define DEGTOSEC 0.0088
#define PULSELEN 0.00406901042 // 1000 / FREQUENCY / 4096

SoftwareSerial bluetooth(11, 10); // RX, TX
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Adafruit_BNO055 bno = Adafruit_BNO055(55);

class Joint {
  uint8_t _pin;
  float _zeroPulse;
  uint16_t _curPos;
  bool _positive;

  public:

    Joint(uint8_t pin, float zeroPulse, bool positive) {
      _pin = pin;
      _zeroPulse = zeroPulse;
      _positive = positive;
      //_curPos = 0;
    }

    void move(float degree) { 
      float pulse = degree * DEGTOSEC;
      if (!_positive) pulse *= -1;
      
      pulse /= PULSELEN;
      pulse += _zeroPulse;
  
      if (pulse < SERVOMIN || pulse > SERVOMAX) return;
  
      pwm.setPWM(_pin, 0, pulse);
    }
};

//void rotate(int newPosition[]) {
//
//  boolean done = false;
//  while (!done) {
//    done = true;
//
//    for (int m = 0; m < 16; m++) {
//      float curPos = currentPosition[m];
//      int newPos = newPosition[m];
//      if (newPos == (int)curPos) continue;
//
//      done = false;
//
//      float stepSize = 0.5;
//      if (newPos < curPos) stepSize *= -1;
//      curPos += stepSize;
//      currentPosition[m] = curPos;
//
//      
//     // setServoPulse(m, curPos);
//    }
//
//    delay(3);
//  }
//
//}

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  pwm.begin();
  bno.begin();

  delay(1000);

  pwm.setPWMFreq(FREQUENCY);
  bno.setExtCrystalUse(true);

  Joint nw0(13, 154, true);
  Joint nw1(14, 565, false);
  Joint nw2(15, 524, true);

  Joint ne0(2, 565, true);
  Joint ne1(1, 150, true);
  Joint ne2(0, 170, false);

  Joint se0(6, 154, true);
  Joint se1(5, 550, false);
  Joint se2(4, 535, true);

  Joint sw0(8, 540, true);
  Joint sw1(9, 170, true);
  Joint sw2(11, 180, false);

  nw0.move(45);
  nw1.move(130);
  nw2.move(-40);
  
  ne0.move(-45);
  ne1.move(130);
  ne2.move(-40);

  se0.move(45);
  se1.move(130);
  se2.move(-40);

  sw0.move(-45);
  sw1.move(130);
  sw2.move(-40);
}


void loop() {
  if (bluetooth.available()) {
    int in0 = bluetooth.parseInt();
    int in1 = bluetooth.parseInt();
    int in2 = bluetooth.parseInt();
//    int input[16] = {
//      0, 0, 0,
//      0, 0, 0,
//      0, 0, 0, 0,
//      0, 0, 0,
//      in0, in1, in2
//    };
//
//    rotate(input);
  }

  sensors_event_t event; 
  bno.getEvent(&event);
  
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");
  
  delay(100);
}
