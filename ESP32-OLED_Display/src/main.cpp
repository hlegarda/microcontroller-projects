#include <U8g2lib.h>
#include <Wire.h>

// ---------- OLED ----------
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(
  U8G2_R0,
  U8X8_PIN_NONE
);

// ---------- BLINK TIMING ----------
unsigned long lastBlink = 0;
unsigned long blinkStart = 0;

const unsigned long BLINK_INTERVAL = 3500;
const unsigned long BLINK_DURATION = 220;

bool blinking = false;

// ---------- IDLE FLOAT ----------
int eyeOffsetY = 0;
int floatDir = 1;

// ---------- DRAW ROUNDED RECT EYE ----------
void drawEye(int x, int y, int w, int h, bool blink) {
  if (blink) {
    // Closed eye (thin horizontal slit)
    u8g2.drawRBox(x, y + h / 2, w, 3, 2);
    return;
  }

  // Eye outline
  u8g2.drawRFrame(x, y, w, h, 4);

  // Inner glow (core)
  u8g2.drawRBox(x + 4, y + 6, w - 8, h - 12, 3);
}

// ---------- DRAW BOTH EYES ----------
void drawEyes(bool blink) {
  int eyeWidth  = 30;
  int eyeHeight = 20;

  int y = 6 + eyeOffsetY;

  int leftX  = 20;
  int rightX = 78;

  drawEye(leftX,  y, eyeWidth, eyeHeight, blink);
  drawEye(rightX, y, eyeWidth, eyeHeight, blink);
}

// ---------- BLINK LOGIC ----------
void updateBlink() {
  unsigned long now = millis();

  if (!blinking && now - lastBlink > BLINK_INTERVAL) {
    blinking = true;
    blinkStart = now;
  }

  if (blinking && now - blinkStart > BLINK_DURATION) {
    blinking = false;
    lastBlink = now;
  }
}

// ---------- IDLE FLOAT ----------
void updateFloat() {
  static unsigned long lastMove = 0;
  unsigned long now = millis();

  if (now - lastMove > 120) {
    eyeOffsetY += floatDir;
    if (eyeOffsetY > 1 || eyeOffsetY < -1) {
      floatDir *= -1;
    }
    lastMove = now;
  }
}

void setup() {
  Wire.begin(21, 22);
  u8g2.begin();
}

void loop() {
  updateBlink();
  updateFloat();

  u8g2.clearBuffer();
  drawEyes(blinking);
  u8g2.sendBuffer();

  delay(30);
}