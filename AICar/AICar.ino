#include <Servo.h>

// Motor Pins
const int L1 = 13; // Left Motor Forward
const int L2 = 12; // Left Motor Backward
const int R1 = 11; // Right Motor Forward
const int R2 = 10; // Right Motor Backward

// Ultrasonic Sensor Pins
const int trigPin = 3;
const int echoPin = 2;

// Buzzer Pin
const int buzzerPin = 4;

// Servo Pin
const int servoPin = 9;
Servo neckServo;

// Variables for ultrasonic sensor
long duration;
int distance;

void setup() {
  // Motor pins setup
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);

  // Ultrasonic sensor pins setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Buzzer pin setup
  pinMode(buzzerPin, OUTPUT);

  // Servo setup
  neckServo.attach(servoPin);
  neckServo.write(90); // Center the servo

  Serial.begin(9600);
}

void loop() {
  // Get distance from ultrasonic sensor
  distance = getDistance();

  if (distance > 20) {
    moveForward();
    neckServo.write(90); // Look straight ahead
  } else {
    stopMotors();
    delay(500);
    turnLeft();
    tone(buzzerPin, 1000); // Beep the buzzer
    delay(1000);
    noTone(buzzerPin); // Stop the buzzer
  }

  delay(100);
}

void moveForward() {
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
}

void stopMotors() {
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
}

void turnLeft() {
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  delay(500); // Adjust the delay to control the turning angle
  stopMotors();
}

int getDistance() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  return duration * 0.034 / 2; // Distance in cm
}
