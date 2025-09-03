#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Arduino_LSM6DSOX.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128
#define OLED_ADDR 0x3C

Adafruit_SH1107 display = Adafruit_SH1107(SCREEN_HEIGHT, SCREEN_WIDTH, &Wire);

struct Particle {
  float x;
  float y;
  float vx;
  float vy;
};

const int NUM_PARTICLES = 10;
Particle particles[NUM_PARTICLES];

const float gravityStrength = 0.5;
const float damping = 0.98;
const float radius = 3.0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!display.begin(OLED_ADDR, true)) {
    Serial.println("SH1107 allocation failed");
    while (1);
  }

  display.clearDisplay();
  display.display();

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  for (int i = 0; i < NUM_PARTICLES; i++) {
    particles[i].x = random(radius, SCREEN_WIDTH - radius);
    particles[i].y = random(radius, SCREEN_HEIGHT - radius);
    particles[i].vx = 0;
    particles[i].vy = 0;
  }
}

void loop() {
  if (!IMU.accelerationAvailable()) return;

  float Ax, Ay, Az;
  IMU.readAcceleration(Ax, Ay, Az);

  float gx = Ax;
  float gy = Ay;

  float mag = sqrt(gx * gx + gy * gy);
  if (mag > 0.01) {
    gx /= mag;
    gy /= mag;
  }

  display.clearDisplay();

  for (int i = 0; i < NUM_PARTICLES; i++) {
    particles[i].vx += gx * gravityStrength;
    particles[i].vy += gy * gravityStrength;

    particles[i].vx *= damping;
    particles[i].vy *= damping;

    particles[i].x += particles[i].vx;
    particles[i].y += particles[i].vy;

    if (particles[i].x < radius) {
      particles[i].x = radius;
      particles[i].vx *= -0.5;
    }
    if (particles[i].x > SCREEN_WIDTH - radius) {
      particles[i].x = SCREEN_WIDTH - radius;
      particles[i].vx *= -0.5;
    }
    if (particles[i].y < radius) {
      particles[i].y = radius;
      particles[i].vy *= -0.5;
    }
    if (particles[i].y > SCREEN_HEIGHT - radius) {
      particles[i].y = SCREEN_HEIGHT - radius;
      particles[i].vy *= -0.5;
    }
  }

  for (int i = 0; i < NUM_PARTICLES; i++) {
    for (int j = i + 1; j < NUM_PARTICLES; j++) {
      float dx = particles[j].x - particles[i].x;
      float dy = particles[j].y - particles[i].y;
      float dist = sqrt(dx * dx + dy * dy);
      if (dist < 2 * radius && dist > 0.0) {
        float overlap = 0.5 * (2 * radius - dist);
        float nx = dx / dist;
        float ny = dy / dist;

        particles[i].x -= nx * overlap;
        particles[i].y -= ny * overlap;
        particles[j].x += nx * overlap;
        particles[j].y += ny * overlap;

        float tempVx = particles[i].vx;
        float tempVy = particles[i].vy;
        particles[i].vx = particles[j].vx * 0.8;
        particles[i].vy = particles[j].vy * 0.8;
        particles[j].vx = tempVx * 0.8;
        particles[j].vy = tempVy * 0.8;
      }
    }
  }

  for (int i = 0; i < NUM_PARTICLES; i++)
    display.fillCircle((int)particles[i].x, (int)particles[i].y, radius, SH110X_WHITE);

  display.display();
}
