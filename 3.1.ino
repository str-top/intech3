#include <Servo.h>

const int buttonPin = 3;
const int servoPin  = 4;

Servo myServo;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  myServo.attach(servoPin);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    // Кнопка нажата
    myServo.write(0);      // Поворот в одну сторону
  } else {
    // Кнопка отпущена
    myServo.write(180);    // Поворот в другую сторону
  }

  delay(10); // небольшая стабилизация
}
