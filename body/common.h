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
#define READ_ORIENTATION 4

