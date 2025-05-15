#include <AFMotor.h>

AF_DCMotor motor_L(1);
AF_DCMotor motor_R(2);


// Ultrasonic sensor pins
#define TRIG_FRONT 28
#define ECHO_FRONT 29
#define TRIG_LEFT  24
#define ECHO_LEFT  25
#define TRIG_BACK  22
#define ECHO_BACK  23
#define TRIG_RIGHT 26
#define ECHO_RIGHT 27

// === Configuration Constants ===
// Distance thresholds (all in cm)
const int THRESHOLD_FRONT = 20;  // if < this, forward is blocked
const int THRESHOLD_SIDE  = 15;  // if < this, side is too close during turn
const int THRESHOLD_BACK  = 20;  // if < this, don’t reverse further

// Speeds for automatic maneuvers
const int BASE_SPEED = 150;  // used when reversing out of a corner
const int TURN_SPEED = 120;  // used for in-place pivots

// === State Variables ===
long frontDistance, leftDistance, rightDistance, backDistance;
int  cmdLeftSpeed  = 0;  // from your tilt‑remote
int  cmdRightSpeed = 0;

// === readUltrasonicCM ===
// Trigger the HC‑SR04 and return the distance in cm.
// If no echo within 30ms (~5m), returns 500 as “no obstacle.”
long readUltrasonicCM(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long dur = pulseIn(echoPin, HIGH, 30000);
  return dur ? (dur / 58) : 500;
}

void setup() {
  
  Serial.begin(9600);  // for reading tilt‑remote data
  Serial1.begin(9600);
  // — Motor pins
  //Set initial speed of the motor & stop
 
  
  
  // — Sonar pins
  pinMode(TRIG_FRONT, OUTPUT);  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_LEFT,  OUTPUT);  pinMode(ECHO_LEFT,  INPUT);
  pinMode(TRIG_BACK,  OUTPUT);  pinMode(ECHO_BACK,  INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);  pinMode(ECHO_RIGHT, INPUT);

  // Ensure all triggers start LOW
  digitalWrite(TRIG_FRONT, LOW);
  digitalWrite(TRIG_LEFT,  LOW);
  digitalWrite(TRIG_BACK,  LOW);
  digitalWrite(TRIG_RIGHT, LOW);

  motor_L.run(FORWARD);
  motor_L.setSpeed(0);

  motor_R.run(FORWARD);
  motor_R.setSpeed(0);
}

void loop() {
  // --- 1) Read all four sensors sequentially ---
  frontDistance = readUltrasonicCM(TRIG_FRONT, ECHO_FRONT);
  leftDistance  = readUltrasonicCM(TRIG_LEFT,  ECHO_LEFT);
  rightDistance = readUltrasonicCM(TRIG_RIGHT, ECHO_RIGHT);
  backDistance  = readUltrasonicCM(TRIG_BACK,  ECHO_BACK);

  // --- 2) Fetch remote’s tilt‑based motor commands ---
  // Expect two integers: leftSpeed and rightSpeed (–255 to +255)
  if (Serial1.available() > 0) {
    cmdLeftSpeed  = Serial1.parseInt();
    cmdRightSpeed = Serial1.parseInt();

    // Echo to USB-Serial so you can watch in the Serial Monitor
    
  }
  int L = cmdLeftSpeed;
  int R = cmdRightSpeed;

  

  // // // --- 3) Smart Obstacle Avoidance Logic ---
  if (frontDistance < THRESHOLD_FRONT) {
    // Forward path blocked → choose a detour or back up
    if (leftDistance > THRESHOLD_SIDE || rightDistance > THRESHOLD_SIDE) {
      // At least one side is clear
      if (leftDistance >= rightDistance) {
        // Pivot left in place
        L = -TURN_SPEED;
        R =  TURN_SPEED;
      } else {
        // Pivot right in place
        L =  TURN_SPEED;
        R = -TURN_SPEED;
      }
    } else {
      // Both sides are blocked → reverse out
      L = R = -BASE_SPEED;
      // If even the back is blocked, spin as last resort
      if (backDistance < THRESHOLD_BACK) {
        L = -TURN_SPEED;
        R =  TURN_SPEED;
      }
    }
  } else {
    // Forward is clear → obey remote but guard sides & back

    // — Side‑avoidance during arcs —
    // If turning toward a too‑close side, reduce or cancel that turn:
    if (leftDistance < THRESHOLD_SIDE && R > L) {
      // Robot is arcing left (right wheel faster) but left is too close
      if (L >= 0 && R >= 0) {
        // Straighten: match right to left
        R = L;
      } else if (L < 0 && R > 0) {
        // Pivot the other way instead
        L =  TURN_SPEED;
        R = -TURN_SPEED;
      }
    }
    if (rightDistance < THRESHOLD_SIDE && L > R) {
      // Arcing right but right side is too close
      if (L >= 0 && R >= 0) {
        // Straighten: match left to right
        L = R;
      } else if (L > 0 && R < 0) {
        // Pivot left instead
        L = -TURN_SPEED;
        R =  TURN_SPEED;
      }
    }
    // — Back‑avoidance —
    // Prevent reverse into obstacles
    if (backDistance < THRESHOLD_BACK && L < 0 && R < 0) {
      L = R = 0;
    }
  }

  // --- 4) Drive the motors with final L/R speeds ---

  // Left motor logic
  if (L >= 0) {
    motor_L.run(FORWARD);
    motor_L.setSpeed(L);
  } else {
    motor_L.run(BACKWARD);
    motor_L.setSpeed(abs(L));
  } 

  // Right motor logic
  if (R >= 0) {
    motor_R.run(FORWARD);
    motor_R.setSpeed(R);
  } else {
    motor_R.run(BACKWARD);
    motor_R.setSpeed(abs(R));
  } 

  Serial.print(L);
  Serial.print(" ");
  Serial.print(R);
  Serial.print(" ");
  Serial.print(frontDistance);
  Serial.print(" ");
  Serial.print(leftDistance);
  Serial.print(" ");
  Serial.print(backDistance);
  Serial.print(" ");
  Serial.println(rightDistance);
  // --- 5) Loop timing ---
  delay(5);  // ~100 Hz main loop
}
