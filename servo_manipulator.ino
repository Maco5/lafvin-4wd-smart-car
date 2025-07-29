#include <Servo.h>

Servo clawServo;
Servo armServo;
Servo baseServo;

const int CLAW_CLOSED = 180;  // degrees to grip
const int CLAW_OPEN   = 10;   // degrees to release
const int ARM_UP      = 60;   // raised arm
const int ARM_DOWN    = 140;  // lowered arm
const int BASE_HOME   = 90;   // forward
const int BASE_TURN   = 180;  // right drop zone
const int MOVE_DELAY  = 1000; // 1 second between each step

void setup() {
  clawServo.attach(9);
  delay(50);
  armServo.attach(10);
  delay(50);
  baseServo.attach(11);
  delay(50);
  // Initialize at power-on position (home position)
  baseServo.write(BASE_HOME);
  armServo.write(ARM_UP);
  clawServo.write(CLAW_OPEN);
  delay(MOVE_DELAY);
}

void loop() {
  // 1) Lower arm
  armServo.write(ARM_DOWN);
  delay(MOVE_DELAY);
  // 2) Close claw
  clawServo.write(CLAW_CLOSED);
  delay(MOVE_DELAY);
  // 3) Raise the arm with object
  armServo.write(ARM_UP);
  delay(MOVE_DELAY);
  // 4) Rotate base to drop zone
  baseServo.write(BASE_TURN);
  delay(MOVE_DELAY);
  // 5) Lower arm
  armServo.write(ARM_DOWN);
  delay(MOVE_DELAY);
  // 6) Open claw to release
  clawServo.write(CLAW_OPEN);
  delay(MOVE_DELAY);
  // 7) Raise arm
  armServo.write(ARM_UP);
  delay(MOVE_DELAY);
  // 8) Return base to home position
  baseServo.write(BASE_HOME);
  delay(MOVE_DELAY);
  // Loop will repeat automatically
}
