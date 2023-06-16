#include <Servo.h>

// Constants
const int SERVO_PIN = 2;
const int TRIGGER_PIN = 8;
const int ECHO_PIN = 9;
const int SERVO_OFF_POSITION = 180;
const int SERVO_ON_POSITION = 0;
const unsigned long DELAY_TIME = 3000;
const int MIN_DISTANCE = 5;
const int MAX_DISTANCE = 40;

// Servo
Servo servoMain;

// Distance
float distance;

// Servo controls
unsigned long previousMillis = 0;
unsigned long offTimerStart = 0;
bool offTimerRunning = false;
int servoPosition = SERVO_OFF_POSITION;
bool isServoOn = false;

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
  if (distance < MIN_DISTANCE) {
    if (!offTimerRunning) {
      offTimerStart = millis();
      offTimerRunning = true;
    } else if (millis() - offTimerStart >= DELAY_TIME) {
      servoPosition = SERVO_OFF_POSITION;
      isServoOn = false;
      offTimerRunning = false;
      Serial.println("Servo turned off");
    }
  } else {
    offTimerRunning = false;
    if (distance <= MAX_DISTANCE) {
      adjustServoPosition();
    }
  }
  servoMain.write(servoPosition);
}

void handleServoOff() {
  if (distance >= MIN_DISTANCE && distance <= MAX_DISTANCE) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= DELAY_TIME) {
      adjustServoPosition();
      isServoOn = true;
      Serial.println("Servo turned on");
    }
  }
 }

void adjustServoPosition() {
  distance = constrain(distance, MIN_DISTANCE, MAX_DISTANCE);
  servoPosition = map(distance, MIN_DISTANCE, MAX_DISTANCE, SERVO_ON_POSITION, SERVO_OFF_POSITION);
}
