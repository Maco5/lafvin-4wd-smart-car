/*
 * LAFVIN 4WD Smart Car - Obstacle Avoidance
 * Arduino sketch to drive a 4WD robot with ultrasonic distance sensor.
 * When an object is within the threshold distance, the robot stops,
 * reverses if necessary and then pivots to avoid the obstacle.
 */

// Pin definitions
const int trigPin = 12;    // ultrasonic trigger pin
const int echoPin = 13;    // ultrasonic echo pin
const int in1  = 2;        // left motor direction
const int pwmL = 5;        // left motor PWM speed
const int in3  = 4;        // right motor direction
const int pwmR = 6;        // right motor PWM speed

// Speed and distance thresholds
const float THRESHOLD  = 25.0; // centimetres to start avoidance
const int   SLOW_DIST  = 15;   // centimetres to trigger backup
const int   FWD_SPEED  = 100;  // forward speed (0-255)
const int   TURN_SPEED = 90;   // turning speed
const int   BACK_SPEED = 90;   // reverse speed

// Measure distance using HC-SR04
float checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration / 58.0;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(pwmL, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(pwmR, OUTPUT);
}

void loop() {
  float dist = checkDistance();
  if (dist > 0 && dist <= THRESHOLD) {
    Stop();
    delay(100);
    if (dist <= SLOW_DIST) {
      Move_Backward(BACK_SPEED);
      delay(600);
    } else {
      Rotate_Left(TURN_SPEED);
      delay(600);
    }
  } else {
    Move_Forward(FWD_SPEED);
  }
}

// Stop both motors
void Stop() {
  analogWrite(pwmL, 0);
  analogWrite(pwmR, 0);
}

// Move backward
void Move_Backward(int sp) {
  digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  analogWrite(pwmL, sp);
  analogWrite(pwmR, sp);
}

// Pivot left in place
void Rotate_Left(int sp) {
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  analogWrite(pwmL, sp);
  analogWrite(pwmR, sp);
}

// Move forward
void Move_Forward(int sp) {
  digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  analogWrite(pwmL, sp);
  analogWrite(pwmR, sp);
}
