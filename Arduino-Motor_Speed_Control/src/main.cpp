#include <Arduino.h>

const int motor = 6;
const int potentiometer = A0;

int portValue;
int speed;

void setup() {
  pinMode(motor, OUTPUT);
  pinMode(potentiometer, INPUT);
  Serial.begin(9800);
}

void loop() {
  portValue = analogRead(potentiometer);
  Serial.println(portValue);

  speed = map(portValue, 0, 1023, 0, 255);
  analogWrite(motor, speed);
}