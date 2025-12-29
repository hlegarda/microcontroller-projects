#include <Arduino.h>

int TOP_RIGHT = 2;
int TOP = 3;
int BOTTOM_RIGHT = 4;
int BOTTOM = 5;
int BOTTOM_LEFT = 6;
int CENTER = 7;
int TOP_LEFT = 8;

int speed = 1000;

void writeH();
void writeA();
void writeN();
void writeZ();
void writeE();
void writeL();
void writeY();
void writeR();
void writeI();

void setup() {
  // put your setup code here, to run once:
  pinMode(CENTER, OUTPUT);
  
  pinMode(TOP, OUTPUT);
  pinMode(TOP_LEFT, OUTPUT);
  pinMode(TOP_RIGHT, OUTPUT);
  
  pinMode(BOTTOM_LEFT, OUTPUT);
  pinMode(BOTTOM_RIGHT, OUTPUT); 
  pinMode(BOTTOM, OUTPUT);
}

void loop() {
  writeH();
  delay(speed);
  writeA();
  delay(speed);
  writeN();
  delay(speed);
  writeZ();
  delay(speed);
  writeE();
  delay(speed);
  writeL();
  delay(speed);
  writeY();
  delay(speed);
  writeA();
  delay(speed);
  writeR();
  delay(speed);
  writeE();
  delay(speed);
  writeL();
  delay(speed);
  writeI();
  delay(speed);
}

void writeH() {
  digitalWrite(TOP_LEFT, HIGH);
  digitalWrite(TOP_RIGHT, HIGH);
  digitalWrite(CENTER, HIGH);
  digitalWrite(BOTTOM_LEFT, HIGH);
  digitalWrite(BOTTOM_RIGHT, HIGH);
  digitalWrite(BOTTOM, LOW);
  digitalWrite(TOP, LOW);
}

void writeA() {
  digitalWrite(TOP_LEFT, HIGH);
  digitalWrite(TOP_RIGHT, HIGH);
  digitalWrite(TOP, HIGH);
  digitalWrite(CENTER, HIGH);
  digitalWrite(BOTTOM_LEFT, HIGH);
  digitalWrite(BOTTOM_RIGHT, HIGH);
  digitalWrite(BOTTOM, LOW);
}

void writeN() {
  digitalWrite(TOP_LEFT, HIGH);
  digitalWrite(TOP_RIGHT, HIGH);
  digitalWrite(BOTTOM_LEFT, HIGH);
  digitalWrite(BOTTOM_RIGHT, HIGH);
  digitalWrite(TOP, LOW);
  digitalWrite(CENTER, LOW);
  digitalWrite(BOTTOM, LOW);
}

void writeZ() {
  digitalWrite(TOP, HIGH);
  digitalWrite(TOP_RIGHT, HIGH);
  digitalWrite(CENTER, HIGH);
  digitalWrite(BOTTOM_LEFT, HIGH);
  digitalWrite(BOTTOM, HIGH);
  digitalWrite(TOP_LEFT, LOW);
  digitalWrite(BOTTOM_RIGHT, LOW);
}

void writeE() {
  digitalWrite(TOP, HIGH);
  digitalWrite(TOP_LEFT, HIGH);
  digitalWrite(CENTER, HIGH);
  digitalWrite(BOTTOM_LEFT, HIGH);
  digitalWrite(BOTTOM, HIGH);
  digitalWrite(TOP_RIGHT, LOW);
  digitalWrite(BOTTOM_RIGHT, LOW);
}

void writeL() {
  digitalWrite(TOP_LEFT, HIGH);
  digitalWrite(BOTTOM_LEFT, HIGH);
  digitalWrite(BOTTOM, HIGH);
  digitalWrite(TOP, LOW);
  digitalWrite(TOP_RIGHT, LOW);
  digitalWrite(CENTER, LOW);
  digitalWrite(BOTTOM_RIGHT, LOW);
}

void writeY() {
  digitalWrite(TOP_LEFT, HIGH);
  digitalWrite(TOP_RIGHT, HIGH);
  digitalWrite(CENTER, HIGH);
  digitalWrite(BOTTOM_RIGHT, HIGH);
  digitalWrite(BOTTOM_LEFT, LOW);
  digitalWrite(TOP, LOW);
  digitalWrite(BOTTOM, LOW);
}

void writeR() {
  digitalWrite(TOP_LEFT, HIGH);
  digitalWrite(TOP_RIGHT, HIGH);
  digitalWrite(TOP, HIGH);
  digitalWrite(CENTER, HIGH);
  digitalWrite(BOTTOM_LEFT, HIGH);
  digitalWrite(BOTTOM_RIGHT, HIGH);
  digitalWrite(BOTTOM, LOW);
}

void writeI() {
  digitalWrite(TOP_RIGHT, HIGH);
  digitalWrite(BOTTOM_RIGHT, HIGH);
  digitalWrite(TOP, LOW);
  digitalWrite(TOP_LEFT, LOW);
  digitalWrite(CENTER, LOW);
  digitalWrite(BOTTOM_LEFT, LOW);
  digitalWrite(BOTTOM, LOW);
}