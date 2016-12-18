#include <SoftwareSerial.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>


/* math constants */
#define SERVOMIN 150
#define SERVOMAX 570
#define FREQUENCY 60
#define DEGTOSEC 0.0088

/* joint ids */
#define NE0 0
#define NE1 1
#define NE2 2
#define SE0 3
#define SE1 4
#define SE2 5
#define SW0 6
#define SW1 7
#define SW2 8
#define NW0 9
#define NW1 10
#define NW2 11

/* additional pins */
#define RX_PIN 11
#define TX_PIN 10

/* command codes */
#define RESET 1
#define MOVE_TO 2
#define MOVE_BY 3
#define READ_ORIENTATION 4

