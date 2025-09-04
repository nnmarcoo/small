#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "SimPresets.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128
#define OLED_ADDR 0x3C

Adafruit_SH1107 display = Adafruit_SH1107(SCREEN_HEIGHT, SCREEN_WIDTH, &Wire);

SandSim sandSim(&display, presets[random(0, sizeof(presets)/sizeof(presets[0]))]);

void setup() {
  if (!display.begin(OLED_ADDR, true))
    while (1);

  display.setContrast(255);
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(0.5);
  display.clearDisplay();
  display.display();

  sandSim.begin();
}

void loop() {
  sandSim.update();
  sandSim.draw();
}
