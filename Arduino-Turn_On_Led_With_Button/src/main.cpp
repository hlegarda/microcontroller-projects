#include <Arduino.h>

const int ledPin = 12; // Pin number for the built-in LED
const int buttonPin = 7; // Pin number for the push button

int value = 0; // Variable to store the analog value

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT);
    Serial.begin(9600);

void loop() {
  value = digitalRead(buttonPin);
  {
    digitalWrite(ledPin, HIGH);
    Serial.println("Button Pressed - LED ON");
    delay(6000);
  }
  else
  {
    digitalWrite(ledPin, LOW);
    Serial.println("Button Released - LED OFF");
  }
}
