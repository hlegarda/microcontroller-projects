#include <Arduino.h>

int red = 5;
int yellow = 6;
int green = 7;
int lightDuration = 6000;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);    
  pinMode(green, OUTPUT);
}

void loop() {
  digitalWrite(green, HIGH);
  delay(lightDuration);
  digitalWrite(green, LOW);
  
  digitalWrite(yellow, HIGH);
  delay(lightDuration);
  digitalWrite(yellow, LOW);
  
  digitalWrite(red, HIGH);
  delay(lightDuration);
  digitalWrite(red, LOW);
}
