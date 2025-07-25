#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

// --------------------------- DISPLAY ---------------------------------
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, /* reset = */ U8X8_PIN_NONE);

// --------------------------- PINS ------------------------------------
#define SW1_PIN  1   // GPIO1 / D0 / A0
#define SW2_PIN  2   // GPIO2 / D1 / A1
#define SW3_PIN  3   // GPIO3 / D2 / A2
#define SW4_PIN  4   // GPIO4 / D3 / A3

// Buttons are wired to GND in your schematic -> use INPUT_PULLUP (pressed = LOW)
#define PRESSED(state) ((state) == LOW)

// --------------------------- TIMING ----------------------------------
const uint32_t BTN_DEBOUNCE_MS  = 25;
const uint32_t SHOW_TIME_MS     = 3000;   // how long to show the final stopwatch time

// --------------------------- BITMAPS ---------------------------------
// Put your bitmaps here (generated arrays from your existing .ino).
// Each frame must be 128x64 monochrome XBM (1-bit per pixel).

// Example tiny dummy 16x16 icon just so the sketch compiles without your assets.
// DELETE these dummies and paste your real 128x64 frames.
static const unsigned char PROGMEM dummy16x16[] = {
  0xFF,0xFF,0x81,0x81,0xBD,0xBD,0xA5,0xA5,
  0xA5,0xA5,0xBD,0xBD,0x81,0x81,0xFF,0xFF
};

// --- Declare your frames like this -----------------------------------
// extern const unsigned char frame_idle_0[] PROGMEM;
// extern const unsigned char frame_idle_1[] PROGMEM;
// ...
// Then list them in arrays below.

// For now we'll just point to the dummy so the structure works:
const uint8_t* const idleFrames[] PROGMEM = {
  dummy16x16, dummy16x16
};
const uint8_t* const anim1Frames[] PROGMEM = {
  dummy16x16, dummy16x16, dummy16x16
};
const uint8_t* const anim2Frames[] PROGMEM = {
  dummy16x16, dummy16x16
};

// Frame counts & frame delays (tune to your liking)
const uint8_t  IDLE_COUNT   = sizeof(idleFrames)  / sizeof(idleFrames[0]);
const uint8_t  ANIM1_COUNT  = sizeof(anim1Frames) / sizeof(anim1Frames[0]);
const uint8_t  ANIM2_COUNT  = sizeof(anim2Frames) / sizeof(anim2Frames[0]);

const uint16_t IDLE_DELAY   = 80;   // ms between idle frames
const uint16_t ANIM1_DELAY  = 60;
const uint16_t ANIM2_DELAY  = 60;

// Your frames are 128x64. Change if you used something else.
const uint8_t  FRAME_W = 128;
const uint8_t  FRAME_H = 64;

// --------------------------- STATE MACHINE ---------------------------
enum Mode {
  MODE_IDLE,
  MODE_ANIM1,
  MODE_ANIM2,
  MODE_STOPWATCH_RUNNING,
  MODE_STOPWATCH_SHOW
};

Mode mode = MODE_IDLE;

// animation bookkeeping
uint8_t   frameIndex    = 0;
uint32_t  nextFrameTime = 0;

// stopwatch bookkeeping
bool      stopwatchRunning = false;
uint32_t  swStart          = 0;
uint32_t  swStop           = 0;
uint32_t  showUntil        = 0;

// --------------------------- BUTTON HANDLER --------------------------
struct Btn {
  uint8_t  pin;
  bool     lastStable;
  bool     lastRead;
  uint32_t lastChange;
};

Btn btn1{SW1_PIN, HIGH, HIGH, 0};
Btn btn2{SW2_PIN, HIGH, HIGH, 0};
Btn btn3{SW3_PIN, HIGH, HIGH, 0};
Btn btn4{SW4_PIN, HIGH, HIGH, 0};

bool readButton(Btn& b) {
  bool raw = digitalRead(b.pin);
  if (raw != b.lastRead) {
    b.lastRead = raw;
    b.lastChange = millis();
  }
  if (millis() - b.lastChange > BTN_DEBOUNCE_MS && raw != b.lastStable) {
    b.lastStable = raw;
    if (PRESSED(raw)) return true;  // rising "press" event
  }
  return false;
}

// --------------------------- HELPERS ---------------------------------
void drawFrame(const uint8_t* bmp) {
  display.clearBuffer();
  // If you use real 128x64 frames, use drawXBMP(0,0,128,64,bmp);
  // The dummy icon is only 16x16, so let's center it for the sample.
  if (FRAME_W == 128 && FRAME_H == 64 && bmp != dummy16x16) {
    display.drawXBMP(0, 0, FRAME_W, FRAME_H, bmp);
  } else {
    display.drawXBMP((128-16)/2, (64-16)/2, 16, 16, bmp);
  }
  display.sendBuffer();
}

void resetAnimation(uint8_t startIndex = 0) {
  frameIndex    = startIndex;
  nextFrameTime = millis();
}

void playAnimationStep(const uint8_t* const* frames, uint8_t count, uint16_t delayMs, bool loop, Mode nextModeIfDone) {
  uint32_t now = millis();
  if (now >= nextFrameTime) {
    // read pointer from PROGMEM
    const uint8_t* f = (const uint8_t*)pgm_read_ptr(&frames[frameIndex]);
    drawFrame(f);

    frameIndex++;
    if (frameIndex >= count) {
      if (loop) {
        frameIndex = 0;
      } else {
        mode = nextModeIfDone;
        resetAnimation();
        return;
      }
    }
    nextFrameTime = now + delayMs;
  }
}

void drawStopwatch(uint32_t elapsedMs) {
  uint32_t ms = elapsedMs % 1000;
  uint32_t s  = (elapsedMs / 1000) % 60;
  uint32_t m  = (elapsedMs / 60000);
  char buf[20];
  snprintf(buf, sizeof(buf), "%02lu:%02lu.%03lu", (unsigned long)m, (unsigned long)s, (unsigned long)ms);

  display.clearBuffer();
  display.setFont(u8g2_font_logisoso24_tr); // pick any u8g2 font you like
  uint16_t w = display.getStrWidth(buf);
  display.drawStr((128 - w) / 2, 42, buf);

  if (!stopwatchRunning) {
    display.setFont(u8g2_font_6x10_tf);
    const char* msg = "SW4 to reset";
    uint16_t w2 = display.getStrWidth(msg);
    display.drawStr((128 - w2) / 2, 62, msg);
  }
  display.sendBuffer();
}


void setup() {
  pinMode(SW1_PIN, INPUT_PULLUP);
  pinMode(SW2_PIN, INPUT_PULLUP);
  pinMode(SW3_PIN, INPUT_PULLUP);
  pinMode(SW4_PIN, INPUT_PULLUP);

  Wire.begin(); 
  display.begin();
  display.clearBuffer();
  display.sendBuffer();

  resetAnimation();
}

void loop() {
 
  bool sw1 = readButton(btn1);
  bool sw2 = readButton(btn2);
  bool sw3 = readButton(btn3);
  bool sw4 = readButton(btn4);

  
  if (sw1) { mode = MODE_ANIM1; resetAnimation(); }
  if (sw2) { mode = MODE_ANIM2; resetAnimation(); }
  if (sw3) {
    stopwatchRunning = true;
    swStart = millis();
    mode = MODE_STOPWATCH_RUNNING;
  }
  if (sw4 && mode == MODE_STOPWATCH_RUNNING) {
    stopwatchRunning = false;
    swStop = millis();
    showUntil = millis() + SHOW_TIME_MS;
    mode = MODE_STOPWATCH_SHOW;
  }

  switch (mode) {
    case MODE_IDLE:
      playAnimationStep(idleFrames, IDLE_COUNT, IDLE_DELAY, true, MODE_IDLE);
      break;

    case MODE_ANIM1:
      playAnimationStep(anim1Frames, ANIM1_COUNT, ANIM1_DELAY, false, MODE_IDLE);
      break;

    case MODE_ANIM2:
      playAnimationStep(anim2Frames, ANIM2_COUNT, ANIM2_DELAY, false, MODE_IDLE);
      break;

    case MODE_STOPWATCH_RUNNING: {
      uint32_t elapsed = millis() - swStart;
      drawStopwatch(elapsed);
      break;
    }

    case MODE_STOPWATCH_SHOW: {
      uint32_t total = swStop - swStart;
      drawStopwatch(total);
      if (millis() > showUntil) {
        mode = MODE_IDLE;
        resetAnimation();
      }
      break;
    }
  }
}



