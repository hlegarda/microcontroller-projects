#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// ===== USER CONFIG =====
const char* WIFI_SSID = "XXXX";
const char* WIFI_PASS = "XXXX";

// ===== PIN CONFIG =====
const int LED_PIN = 25;

// ===== WEB SERVER =====
WebServer server(56429);

void handleRoot() {
  String html = "<h1>ESP32 LED Control</h1>"
                "<p><a href=\"/on\">Turn LED ON</a></p>"
                "<p><a href=\"/off\">Turn LED OFF</a></p>";
  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(LED_PIN, HIGH);
  server.send(200, "text/plain", "LED ON");
}

void handleOff() {
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/plain", "LED OFF");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // Connect WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Web routes
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}