#include <Arduino.h>

void amazingLightShow();

int redLed1 = 5;
int redLed2 = 6;
int redLed3 = 7;
int yellowLed = 8;
int greenLed = 9;
int buttonPin = 2;
int delayTime = 40;

void setup() {
  pinMode(redLed1, OUTPUT);
  pinMode(redLed2, OUTPUT); 
  pinMode(redLed3, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buttonPin, INPUT);
}



void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    amazingLightShow();
  }
}


void amazingLightShow() {
  digitalWrite(redLed1, HIGH);
  delay(delayTime);
  digitalWrite(redLed1, LOW);
  delay(delayTime);

  digitalWrite(redLed2, HIGH);
  delay(delayTime);
  digitalWrite(redLed2, LOW);
  delay(delayTime);

  digitalWrite(redLed3, HIGH);
  delay(delayTime);
  digitalWrite(redLed3, LOW);
  delay(delayTime);

  digitalWrite(yellowLed, HIGH);
  delay(delayTime);
  digitalWrite(yellowLed, LOW);
  delay(delayTime);

  digitalWrite(greenLed, HIGH);
  delay(delayTime);
  digitalWrite(greenLed, LOW);
  delay(delayTime);

  digitalWrite(yellowLed, HIGH);
  delay(delayTime);
  digitalWrite(yellowLed, LOW);
  delay(delayTime);

  digitalWrite(redLed3, HIGH);
  delay(delayTime);
  digitalWrite(redLed3, LOW);
  delay(delayTime);

  digitalWrite(redLed2, HIGH);
  delay(delayTime);
  digitalWrite(redLed2, LOW);
  delay(delayTime);

  digitalWrite(redLed1, HIGH);
  delay(delayTime);
  digitalWrite(redLed1, LOW);
}
