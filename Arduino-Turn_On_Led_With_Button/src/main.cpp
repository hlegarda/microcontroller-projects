#include <Arduino.h>

const int ledPin = 12; // Pin number for the built-in LED
const int buttonPin = 7; // Pin number for the push button

int value = 0; // Variable to store the analog value

void setup() {
    pinMode(ledPin, OUTPUT); // Set the LED pin as an output
    pinMode(buttonPin, INPUT); // Set the button pin as an input
    Serial.begin(9600); // Start serial communication at 9600 baud rate
}

void loop() {
  value = digitalRead(buttonPin); // Read the state of the button
  if (value == HIGH)
  {
    digitalWrite(ledPin, HIGH); // Turn the LED on
    Serial.println("Button Pressed - LED ON");
    delay(6000); // Wait for half a second
  }
  else
  {
    digitalWrite(ledPin, LOW); // Turn the LED off
    Serial.println("Button Released - LED OFF");
  }
}
