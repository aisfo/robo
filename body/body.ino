#include "common.h"
#include "robot.h"


SoftwareSerial bluetooth(11, 10); // RX, TX
Adafruit_BNO055 bno = Adafruit_BNO055(55);
Robot robot = Robot();


void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  
  bno.begin();
  delay(500);
  bno.setExtCrystalUse(true);

  robot.begin();
}


void loop() {
  if (bluetooth.available()) {
    uint8_t command = bluetooth.parseInt();

    switch (command) {
      case MOVE_TO: {
        uint8_t jointId = bluetooth.parseInt();
        float value = bluetooth.parseFloat();
        robot.moveTo(jointId, value);
        break;
      }
      case MOVE_BY: {
        uint8_t jointId = bluetooth.parseInt();
        float value = bluetooth.parseFloat();
        robot.moveBy(jointId, value);
        break;
      }
      case RESET:
        robot.reset();
        break;
      case READ_ORIENTATION:
        sensors_event_t event; 
        bno.getEvent(&event);
        bluetooth.print("\x02"); // start of text
        bluetooth.print(event.orientation.x, 4);
        bluetooth.print("\x1f"); // value separator
        bluetooth.print(event.orientation.y, 4);
        bluetooth.print("\x1f"); // value separator
        bluetooth.print(event.orientation.z, 4);
        bluetooth.print("\x03"); // end of text
        break;
    }
  }

  delay(1);
}
