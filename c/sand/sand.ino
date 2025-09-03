#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Arduino_LSM6DSOX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128
#define OLED_ADDR 0x3C

Adafruit_SH1107 display = Adafruit_SH1107(SCREEN_HEIGHT, SCREEN_WIDTH, &Wire);

struct Particle {
  int16_t x;
  int16_t y;
  int16_t vx;
  int16_t vy;
};

const int NUM_PARTICLES = 10;
Particle particles[NUM_PARTICLES];

const int16_t GRAVITY = 30;
const int16_t DAMPING = 98;
const int16_t RADIUS = 3;
const int16_t SCALE = 100;

unsigned long lastFrame = 0;
const int FRAME_TIME = 16;

void setup() {
  Serial.begin(115200);

  if (!display.begin(OLED_ADDR, true)) {
    Serial.println("SH1107 allocation failed");
    while (1);
  }

  display.setContrast(255);
  display.clearDisplay();
  display.display();

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  for (int i = 0; i < NUM_PARTICLES; i++) {
    particles[i].x = (random(RADIUS, SCREEN_WIDTH - RADIUS)) * SCALE;
    particles[i].y = (random(RADIUS, SCREEN_HEIGHT - RADIUS)) * SCALE;
    particles[i].vx = 0;
    particles[i].vy = 0;
  }
}

void loop() {
  if (millis() - lastFrame < FRAME_TIME) return;
  lastFrame = millis();

  if (!IMU.accelerationAvailable()) return;

  float Ax, Ay, Az;
  IMU.readAcceleration(Ax, Ay, Az);

  int16_t gx = (int16_t)(Ax * SCALE);
  int16_t gy = (int16_t)(Ay * SCALE);

  long mag2 = (long)gx * gx + (long)gy * gy;
  if (mag2 > (SCALE / 100) * (SCALE / 100)) {
    long invMag = 1000000L / (long)sqrt((float)mag2);
    gx = (gx * invMag) / 1000;
    gy = (gy * invMag) / 1000;
  }

  display.clearDisplay();

  for (int i = 0; i < NUM_PARTICLES; i++) {
    particles[i].vx += (gx * GRAVITY) / SCALE;
    particles[i].vy += (gy * GRAVITY) / SCALE;

    particles[i].vx = (particles[i].vx * DAMPING) / 100;
    particles[i].vy = (particles[i].vy * DAMPING) / 100;

    particles[i].x += particles[i].vx;
    particles[i].y += particles[i].vy;

    if (particles[i].x < RADIUS * SCALE) {
      particles[i].x = RADIUS * SCALE;
      particles[i].vx = -(particles[i].vx / 2);
    }
    if (particles[i].x > (SCREEN_WIDTH - RADIUS) * SCALE) {
      particles[i].x = (SCREEN_WIDTH - RADIUS) * SCALE;
      particles[i].vx = -(particles[i].vx / 2);
    }
    if (particles[i].y < RADIUS * SCALE) {
      particles[i].y = RADIUS * SCALE;
      particles[i].vy = -(particles[i].vy / 2);
    }
    if (particles[i].y > (SCREEN_HEIGHT - RADIUS) * SCALE) {
      particles[i].y = (SCREEN_HEIGHT - RADIUS) * SCALE;
      particles[i].vy = -(particles[i].vy / 2);
    }
  }

  for (int i = 0; i < NUM_PARTICLES; i++) {
    for (int j = i + 1; j < NUM_PARTICLES; j++) {
      long dx = particles[j].x - particles[i].x;
      long dy = particles[j].y - particles[i].y;
      long dist2 = dx * dx + dy * dy;
      long minDist = 2 * RADIUS * SCALE;

      if (dist2 < (long)minDist * minDist && dist2 > 0) {
        long dist = sqrt((float)dist2);
        long overlap = (minDist - dist) / 2;

        int16_t nx = (dx * SCALE) / dist;
        int16_t ny = (dy * SCALE) / dist;

        particles[i].x -= (nx * overlap) / SCALE;
        particles[i].y -= (ny * overlap) / SCALE;
        particles[j].x += (nx * overlap) / SCALE;
        particles[j].y += (ny * overlap) / SCALE;

        int16_t tmpVx = particles[i].vx;
        int16_t tmpVy = particles[i].vy;
        particles[i].vx = (particles[j].vx * 8) / 10;
        particles[i].vy = (particles[j].vy * 8) / 10;
        particles[j].vx = (tmpVx * 8) / 10;
        particles[j].vy = (tmpVy * 8) / 10;
      }
    }
  }

  for (int i = 0; i < NUM_PARTICLES; i++)
    display.fillCircle(
      particles[i].x / SCALE,
      particles[i].y / SCALE,
      RADIUS,
      SH110X_WHITE
    );

  display.display();
}
