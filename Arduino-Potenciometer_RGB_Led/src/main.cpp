#include <Arduino.h>

int red = 3;
int blue = 5;
int green = 6;

int poteciometerPin1 = A0;
int poteciometerPin2 = A1;
int poteciometerPin3 = A2;

int intensity1 = 0;
int intensity2 = 0; 
int intensity3 = 0;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(poteciometerPin1, INPUT);
  pinMode(poteciometerPin2, INPUT); 
  pinMode(poteciometerPin3, INPUT);
  Serial.begin(9600);
}

void loop() {
  intensity1 = analogRead(poteciometerPin1) / 4;
  intensity2 = analogRead(poteciometerPin2) / 4;
  intensity3 = analogRead(poteciometerPin3) / 4;

  analogWrite(red, intensity1);
  analogWrite(blue, intensity2);
  analogWrite(green, intensity3);

  Serial.print("Red Intensity: ");
  Serial.print(intensity1); 
  Serial.print(" | Blue Intensity: ");
  Serial.print(intensity2);
  Serial.print(" | Green Intensity: ");
  Serial.println(intensity3);
  delay(500);

}
