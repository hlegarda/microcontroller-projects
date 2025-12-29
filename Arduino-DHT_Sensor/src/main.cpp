#include <Arduino.h>

const int buttonPin = 2;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int state = digitalRead(buttonPin);
  Serial.println(state);
  delay(200);
}
/* #include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(DHTPIN, INPUT_PULLUP); // internal pull-up
  dht.begin();
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read DHT11");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" °C | Hum: ");
  Serial.print(h);
  Serial.println(" %");
}
 */