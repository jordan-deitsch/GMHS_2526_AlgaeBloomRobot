#include "src/tb6612/SparkFun_TB6612.h"

// Motor driver digital pins (UPDATE FOR YOUR DESIGN)
#define AIN1 (4)
#define AIN2 (5)
#define PWMA (6)	// Must be a PWM supported pin (~)
#define BIN1 (7)
#define BIN2 (8)
#define PWMB (9)	// Must be a PWM supported pin (~)
#define STBY (10)

// Ultrsound sensor digital pins (UPDATE FOR YOUR DESIGN)
#define TRIG (11)
#define ECHO (12)

// TODO: Add more sensor definitions as needed (temperature, humidity, etc.)

// Constants for motor operation (UPDATE FOR YOUR DESIGN)
const int MOTOR_SPEED 					= 100;		// Default speed of motor, between [0, 255]
const int MOTOR_ON_TIME_SEC 		= 1;			// Deafult ON time of motor when activated (seconds)
const int MOTOR_MAX_TIME_SEC 		= 100;  	// Maximum time the motor can spin before screw is fully extended (seconds)

// Change to set default direction of motor (CW or CCW) instead of switching wires. Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

// Constants for ultrasound range finder
const unsigned int MAX_DIST = 23200;  // Maximum range of ultrasounic range finder [m]
const float SPEED_OF_SOUND = 343;     // Speed of sound in air [m/sec]

// Variables for ultrasound range finder
unsigned long t1, t2, pulse_width;
float distance;

// Create a new motor object
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

// Functions
void runMotor();
void checkRange();

void setup()
{
	Serial.begin(115200);		// Start serial port to print actions
	motor1.standby();				// Start motor in standy condition
  motor2.standby();

  // Setup ultrasound range finder pins
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);

	// TODO: Setup for any other I/O pins: lights? Other controls?
}

void loop()
{
	runMotor();

	// Wait 1 sec before repeating loop
	delay(1000);
}

void runMotor()
{
  Serial.println("--> RUNNING MOTOR");
  motor1.drive(MOTOR_SPEED, 1000*MOTOR_ON_TIME_SEC);
  motor1.brake();
}

void checkRange()
{
  // Trigger ultrsound pulse with 10 usec pulse
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Wait for echo pulse to begin
  while(digitalRead(ECHO) == 0);

  // Measure pulse time of echo pulse
  t1 = millis();
  while(digitalRead(ECHO) == 1);
  t2 = millis();
  pulse_width = t2 - t1;
}
