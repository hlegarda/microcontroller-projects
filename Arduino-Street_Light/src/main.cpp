#include <Arduino.h>

int red = 5;
int yellow = 6;
int green = 7;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);    
  pinMode(green, OUTPUT);
}

void loop() {
  digitalWrite(green, HIGH);
  delay(6000);
  digitalWrite(green, LOW);
  
  digitalWrite(yellow, HIGH);
  delay(6000);
  digitalWrite(yellow, LOW);
  
  digitalWrite(red, HIGH);
  delay(6000);
  digitalWrite(red, LOW);
}
