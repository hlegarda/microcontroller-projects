/* #include <U8g2lib.h>
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
 */


/* #include <U8g2lib.h>
#include <Wire.h>

// ---------- OLED ----------
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(
  U8G2_R0,
  U8X8_PIN_NONE
);

// ---------- JOYSTICK PINS ----------
#define JOY_X 34
#define JOY_Y 35
#define JOY_BTN 32

// ---------- JOYSTICK STATE ----------
int joyX = 2048;
int joyY = 2048;
bool joyPressed = false;

// ---------- MASCOT POSITION ----------
int mascotX = 40;
int mascotBaseY = 4;

// ---------- MASCOT DRAWING ----------
void drawMascot(int x, int y) {
  u8g2.drawCircle(x + 8, y + 10, 8);

  u8g2.drawPixel(x + 5, y + 9);
  u8g2.drawPixel(x + 11, y + 9);
  u8g2.drawPixel(x + 8, y + 12);

  u8g2.drawBox(x + 4, y + 18, 3, 2);
  u8g2.drawBox(x + 9, y + 18, 3, 2);

  u8g2.drawPixel(x + 1, y + 11);
  u8g2.drawPixel(x + 15, y + 11);
}

// ---------- IDLE JUMP ----------
void idleJump(int x) {
  static int jumpOffset = 0;
  static int jumpDir = 1;

  jumpOffset += jumpDir;
  if (jumpOffset >= 3) jumpDir = -1;
  if (jumpOffset <= 0) jumpDir = 1;

  drawMascot(x, mascotBaseY - jumpOffset);
}

// ---------- COLD SHAKE ----------
void coldShake(int x) {
  static int frame = 0;
  int dx[4] = {0, -1, 1, 0};
  int dy[4] = {0, 1, 0, -1};

  drawMascot(x + dx[frame], mascotBaseY + dy[frame]);

  frame = (frame + 1) % 4;
}

// ---------- READ JOYSTICK ----------
void readJoystick() {
  joyX = analogRead(JOY_X);
  joyY = analogRead(JOY_Y);
  joyPressed = (digitalRead(JOY_BTN) == LOW);
}

void setup() {
  Wire.begin(21, 22);
  u8g2.begin();

  pinMode(JOY_BTN, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  readJoystick();

  // ---------- HORIZONTAL MOVEMENT ----------
  if (joyX < 1500) mascotX -= 1;     // left
  if (joyX > 2600) mascotX += 1;     // right

  // Keep mascot on screen
  mascotX = constrain(mascotX, 0, 112);

  // ---------- JUMP HEIGHT CONTROL ----------
  if (joyY < 1500) mascotBaseY = 2;   // up
  else if (joyY > 2600) mascotBaseY = 6; // down
  else mascotBaseY = 4;

  // ---------- DRAW ----------
  u8g2.clearBuffer();

  if (joyPressed) {
    coldShake(mascotX);
  } else {
    idleJump(mascotX);
  }

  u8g2.sendBuffer();
  delay(80);
} */


/* #include <U8g2lib.h>
#include <Wire.h>
#include <DHT.h>

// ---------- DHT SETUP ----------
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// ---------- OLED ----------
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(
  U8G2_R0,
  U8X8_PIN_NONE
);

// ---------- GLOBAL STATE ----------
unsigned long lastDHTRead = 0;
const unsigned long DHT_INTERVAL = 2000;

float lastTemp = NAN;
bool coldState = false;

// ---------- MASCOT DRAWING ----------
void drawMascot(int x, int y) {
  // BODY
  u8g2.drawCircle(x + 8, y + 10, 8);

  // FACE
  u8g2.drawPixel(x + 5, y + 9);
  u8g2.drawPixel(x + 11, y + 9);
  u8g2.drawPixel(x + 8, y + 12);

  // FEET
  u8g2.drawBox(x + 4, y + 18, 3, 2);
  u8g2.drawBox(x + 9, y + 18, 3, 2);

  // ARMS
  u8g2.drawPixel(x + 1, y + 11);
  u8g2.drawPixel(x + 15, y + 11);
}

// ---------- IDLE JUMP ----------
void idleJump() {
  static int jumpOffset = 0;
  static int jumpDir = 1;

  jumpOffset += jumpDir;
  if (jumpOffset >= 3) jumpDir = -1;
  if (jumpOffset <= 0) jumpDir = 1;

  drawMascot(40, 4 - jumpOffset);
}

// ---------- COLD SHAKE ----------
void coldShake() {
  static int shakeFrame = 0;

  int shakeX[4] = {0, -1, 1, 0};
  int shakeY[4] = {0, 1, 0, -1};

  drawMascot(40 + shakeX[shakeFrame], 4 + shakeY[shakeFrame]);

  shakeFrame++;
  if (shakeFrame >= 4) shakeFrame = 0;
}

// ---------- NON-BLOCKING DHT UPDATE ----------
void updateTemperature() {
  unsigned long now = millis();

  if (now - lastDHTRead >= DHT_INTERVAL) {
    lastDHTRead = now;

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("DHT read failed");
      return;
    }

    lastTemp = t;
    coldState = (t < 26.0);

    Serial.print("Temp: ");
    Serial.print(t);
    Serial.println(" °C");
  }
}

void setup() {
  Wire.begin(21, 22);
  u8g2.begin();

  pinMode(DHTPIN, INPUT_PULLUP);
  dht.begin();

  Serial.begin(9600);
}

void loop() {
  updateTemperature();

  u8g2.clearBuffer();

  if (coldState) {
    coldShake();
  } else {
    idleJump();
  }

  // ---------- TEMPERATURE DISPLAY ----------
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setCursor(70, 18);

  if (!isnan(lastTemp)) {
    u8g2.print((int)lastTemp);
    u8g2.print("C");
  } else {
    u8g2.print("--C");
  }

  u8g2.sendBuffer();

  delay(coldState ? 80 : 140);
}


 */





#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define OLED_ADDR 0x3C   // try 0x3D if needed

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int x = SCREEN_WIDTH;  // start off-screen
int y = 8;             // PERFECT vertical position for size 2 on 32px height

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);
  Wire.setClock(100000);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (true); // OLED not found
  }

  display.clearDisplay();
  display.setTextSize(2);        // BIG text
  display.setTextColor(SSD1306_WHITE);
  display.setTextWrap(false);    // 🔑 prevents new line
}

void loop() {
  Serial.println("Starting loop");
  display.clearDisplay();

  display.setCursor(x, y);
  display.print("puto el que lo lea");

  display.display();

  x -= 2;               // scroll speed
  if (x < -160) {       // reset when text is fully gone
    x = SCREEN_WIDTH;
  }

  delay(30);
  Serial.println("Loop done");
}
