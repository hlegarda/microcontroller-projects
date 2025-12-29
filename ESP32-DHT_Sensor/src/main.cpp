#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

/* ================= DHT CONFIG ================= */
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/* ================= WIFI CONFIG ================= */
const char* ssid     = "XXXX";
const char* password = "XXXX";

/* ================= WEB SERVER ================= */
WebServer server(80);

/* ================= CORS HELPERS ================= */
void sendCORSHeaders() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "*");
}

/* ================= ROUTE HANDLERS ================= */
void handleTemperature() {
  float temperature = dht.readTemperature();

  sendCORSHeaders();

  if (isnan(temperature)) {
    server.send(500, "text/plain", "Failed to read temperature");
    return;
  }

  server.send(200, "text/plain", String(temperature));
}

void handleHumidity() {
  float humidity = dht.readHumidity();

  sendCORSHeaders();

  if (isnan(humidity)) {
    server.send(500, "text/plain", "Failed to read humidity");
    return;
  }

  server.send(200, "text/plain", String(humidity));
}

void handleOptions() {
  sendCORSHeaders();
  server.send(204); // No Content
}

/* ================= SETUP ================= */
void setup() {
  Serial.begin(9600);

  pinMode(DHTPIN, INPUT_PULLUP);
  dht.begin();

  /* ----- WiFi connect ----- */
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  /* ----- Routes ----- */
  server.on("/temperature", HTTP_GET, handleTemperature);
  server.on("/humidity", HTTP_GET, handleHumidity);

  /* Handle CORS preflight */
  server.onNotFound([]() {
    if (server.method() == HTTP_OPTIONS) {
      handleOptions();
    } else {
      sendCORSHeaders();
      server.send(404, "text/plain", "Not Found");
    }
  });

  server.begin();
  Serial.println("HTTP server started");
}

/* ================= LOOP ================= */
void loop() {
  server.handleClient();
}
