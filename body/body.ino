#include "common.h"
#include "robot.h"


SoftwareSerial bluetooth(RX_PIN, TX_PIN);
Adafruit_BNO055 bno = Adafruit_BNO055(55);
Robot robot = Robot();


void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  //flush input
  while(bluetooth.available()) {
    bluetooth.read();
  }
  
  bno.begin();
  delay(500);
  bno.setExtCrystalUse(true);

  robot.begin();
}



void loop() {

  if (!bluetooth.available())  {
     delay(1);
     return;
  }

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
    case RESET: {
      robot.reset();
      break;
    }
    case READ_ORIENTATION: {
      sensors_event_t event; 
      bno.getEvent(&event);
      bluetooth.print(event.orientation.x, 4);  // -90 <= roll <= 90
      bluetooth.print(" "); // value separator
      bluetooth.print(event.orientation.y, 4);  // -180 <= pitch <= 180
      bluetooth.print(" "); // value separator 
      bluetooth.print(event.orientation.z, 4);  // 0 <= yaw/heading <= 359, magnetic north
      bluetooth.print("\n"); // end of text
      break;
    }
  }

}
