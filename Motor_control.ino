#include <Servo.h>

// Constants
const int SERVO_PIN = 2;
const int TRIGGER_PIN = 8;
const int ECHO_PIN = 9;
const int SERVO_OFF_POSITION = 180;
const int SERVO_ON_POSITION = 0;
const unsigned long DELAY_TIME = 3000;
const int MIN_DISTANCE = 10;
const int MAX_DISTANCE = 40;
const int DISTANCE_1 = 40;
const int DISTANCE_2 = 30;
const int DISTANCE_3 = 22;
const int DISTANCE_4 = 15;
const int DISTANCE_5 = 8;
const int DISTANCE_OFF = 5;
const int DISTANCE_ON = 2;

// Servo Control 
Servo servoMain;

float distance;
unsigned long previousMillis = 0;
int servoPosition = SERVO_OFF_POSITION;
bool isServoOn = false;
bool handInRange = false;
unsigned long handInRangeStartMillis = 0;

void setup() {
  Serial.begin(9600);
  servoMain.attach(SERVO_PIN); 
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  servoMain.write(servoPosition);
}

void loop() {
  distance = readDistance();
  
  if (isServoOn) {
    handleServoOn();
  } else {
    handleServoOff();
  }
}

float readDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);  
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);  
  digitalWrite(TRIGGER_PIN, LOW);  
  float duration = pulseIn(ECHO_PIN, HIGH);  
  return duration / 58.82;
}

void handleServoOn() {
  if (distance < DISTANCE_OFF && distance > DISTANCE_ON) {
    if (!handInRange) {
      handInRange = true;
      handInRangeStartMillis = millis();
    } else if (millis() - handInRangeStartMillis >= DELAY_TIME) {
      servoPosition = SERVO_OFF_POSITION;
      isServoOn = false;
      handInRange = false;
      Serial.println("Servo turned off");
    }
  } else {
    handInRange = false;
    adjustServoPosition();
  }
  
  servoMain.write(servoPosition);
}

void handleServoOff() {
  if (distance < MAX_DISTANCE && distance > MIN_DISTANCE) {
    if (!handInRange) {
      handInRange = true;
      handInRangeStartMillis = millis();
    } else if (millis() - handInRangeStartMillis >= DELAY_TIME) {
      servoPosition = SERVO_ON_POSITION;
      servoMain.write(servoPosition);
      isServoOn = true;
      handInRange = false;
      Serial.println("Servo turned on");
    }
  } else {
    handInRange = false;
  }
}

void adjustServoPosition() {
  if (distance < DISTANCE_1 && distance > DISTANCE_2) {
    servoPosition = 0;
  } else if (distance < DISTANCE_2 && distance > DISTANCE_3) {
    servoPosition = 80;
  } else if (distance < DISTANCE_3 && distance > DISTANCE_4) {
    servoPosition = 120;
  } else if (distance < DISTANCE_4 && distance > DISTANCE_5) {
    servoPosition = 150;
  }
}
