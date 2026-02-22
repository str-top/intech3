const int mq2Pin = A0;
const int buzzerPin = 8;

int threshold = 400;   // Adjust after calibration

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(mq2Pin);

  Serial.print("MQ2 value: ");
  Serial.println(sensorValue);

  if (sensorValue > threshold) {
    digitalWrite(buzzerPin, HIGH);  // Smoke detected
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  delay(200);
}
