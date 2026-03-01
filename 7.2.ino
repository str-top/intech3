#include <Servo.h>

const int relayPin = 2;
const int servoPin = 8;
const int potPin   = A0;

const int threshold = 512;     // midpoint of 0–1023
const int servoLeft  = 30;     // adjust as needed
const int servoRight = 150;    // adjust as needed

Servo myServo;

bool relayActive = false;
unsigned long relayStartTime = 0;
const unsigned long relayDuration = 10000; // 10 seconds

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  
  myServo.attach(servoPin);
  myServo.write(servoLeft);
}

void loop() {
  int potValue = analogRead(potPin);
  unsigned long currentMillis = millis();

  if (potValue > threshold) {
    myServo.write(servoRight);

    if (!relayActive) {
      digitalWrite(relayPin, HIGH);
      relayStartTime = currentMillis;
      relayActive = true;
    }
  } else {
    myServo.write(servoLeft);
  }

  // Turn relay off after 10 seconds
  if (relayActive && (currentMillis - relayStartTime >= relayDuration)) {
    digitalWrite(relayPin, LOW);
    relayActive = false;
  }
}
