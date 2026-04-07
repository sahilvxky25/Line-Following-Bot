// ============================================================
//  Line Following Robot — 3 IR Sensors + L293D Motor Driver
// ============================================================
// Progammer Names - Sahil Ku Patra, Somya Ranjan Suar

// --- IR Sensor Pins (active LOW: 0 = line detected) ---
const int IR_LEFT   = 2;
const int IR_CENTER = 3;
const int IR_RIGHT  = 4;

// --- L293D Motor Driver Pins ---
// Left Motor
const int ENA  = 5;   // PWM speed control (left)
const int IN1  = 6;   // Left motor direction A
const int IN2  = 7;   // Left motor direction B

// Right Motor
const int ENB  = 8;   // PWM speed control (right)  ← use PWM pin (e.g. 9)
const int IN3  = 9;   // Right motor direction A      ← adjust pins to your wiring
const int IN4  = 10;  // Right motor direction B

// --- Speed Settings ---
const int BASE_SPEED  = 180;  // 0–255 (normal forward speed)
const int TURN_SPEED  = 220;  // faster side during a turn
const int SLOW_SPEED  = 80;   // slower side during a turn

// ============================================================
void setup() {
  // Sensor inputs
  pinMode(IR_LEFT,   INPUT);
  pinMode(IR_CENTER, INPUT);
  pinMode(IR_RIGHT,  INPUT);

  // Motor driver outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();   // start safe
  Serial.begin(9600);
}

// ============================================================
void loop() {
  // Read sensors (LOW = on the black line, HIGH = white surface)
  bool l = (digitalRead(IR_LEFT)   == LOW);
  bool c = (digitalRead(IR_CENTER) == LOW);
  bool r = (digitalRead(IR_RIGHT)  == LOW);

  Serial.print("L:"); Serial.print(l);
  Serial.print(" C:"); Serial.print(c);
  Serial.print(" R:"); Serial.println(r);

  // --- Decision Logic ---
  if (!l && c && !r) {
    // Centre only → go straight
    moveForward(BASE_SPEED, BASE_SPEED);
  }
  else if (!l && !c && r) {
    // Right sensor on line → turn right
    moveForward(TURN_SPEED, SLOW_SPEED);
  }
  else if (l && !c && !r) {
    // Left sensor on line → turn left
    moveForward(SLOW_SPEED, TURN_SPEED);
  }
  else if (l && c && !r) {
    // Left + Centre → gentle left
    moveForward(SLOW_SPEED, BASE_SPEED);
  }
  else if (!l && c && r) {
    // Centre + Right → gentle right
    moveForward(BASE_SPEED, SLOW_SPEED);
  }
  else if (l && c && r) {
    // All on → T-junction or wide line, keep going straight
    moveForward(BASE_SPEED, BASE_SPEED);
  }
  else {
    // All off → lost the line, stop
    stopMotors();
  }
}

// ============================================================
//  Motor Control Helpers
// ============================================================

// leftSpeed / rightSpeed: 0–255
void moveForward(int leftSpeed, int rightSpeed) {
  // Left motor — forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, leftSpeed);

  // Right motor — forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, rightSpeed);
}

void moveBackward(int leftSpeed, int rightSpeed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, leftSpeed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, rightSpeed);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}
