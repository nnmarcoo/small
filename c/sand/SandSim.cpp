#include "SandSim.h"

SandSim::SandSim(Adafruit_SH1107* d, const SandSimConfig& config)
  : numParticles(config.numParticles),
    gravity(config.gravity),
    damping(config.damping),
    radius(config.radius),
    scale(config.scale),
    collisionsEnabled(config.collisionsEnabled),
    display(d) {
  particles = new Particle[numParticles];

  shape = (Shape)random(0, 5);
}

void SandSim::begin() {
  if (!IMU.begin())
    while (1);

  for (int i = 0; i < numParticles; i++) {
    particles[i].x = (random(radius, display->width() - radius)) * scale;
    particles[i].y = (random(radius, display->height() - radius)) * scale;
    particles[i].vx = 0;
    particles[i].vy = 0;
  }
}

void SandSim::update() {
  if (!IMU.accelerationAvailable()) return;

  float Ax, Ay, Az;
  IMU.readAcceleration(Ax, Ay, Az);

  int16_t gx = (int16_t)(Ax * scale);
  int16_t gy = (int16_t)(Ay * scale);

  long mag2 = (long)gx * gx + (long)gy * gy;
  if (mag2 > (scale / 100) * (scale / 100)) {
    long invMag = 1000000L / (long)sqrt((float)mag2);
    gx = (gx * invMag) / 1000;
    gy = (gy * invMag) / 1000;
  }

  for (int i = 0; i < numParticles; i++) {
    particles[i].vx += (gx * gravity) / scale;
    particles[i].vy += (gy * gravity) / scale;

    particles[i].vx = (particles[i].vx * damping) / 100;
    particles[i].vy = (particles[i].vy * damping) / 100;

    particles[i].x += particles[i].vx;
    particles[i].y += particles[i].vy;

    if (!collisionsEnabled) {
      particles[i].vx += random(-100, 100);
      particles[i].vy += random(-100, 100);
    }

    handleBoundaries(particles[i]);
  }

  if (collisionsEnabled)
    handleCollisions();
}

void SandSim::handleBoundaries(Particle& p) {
  if (p.x < radius * scale) {
    p.x = radius * scale;
    p.vx = -(p.vx / 2);
  }
  if (p.x > (display->width() - radius) * scale) {
    p.x = (display->width() - radius) * scale;
    p.vx = -(p.vx / 2);
  }
  if (p.y < radius * scale) {
    p.y = radius * scale;
    p.vy = -(p.vy / 2);
  }
  if (p.y > (display->height() - radius) * scale) {
    p.y = (display->height() - radius) * scale;
    p.vy = -(p.vy / 2);
  }
}

void SandSim::handleCollisions() {
  for (int i = 0; i < numParticles; i++) {
    for (int j = i + 1; j < numParticles; j++) {
      long dx = particles[j].x - particles[i].x;
      long dy = particles[j].y - particles[i].y;
      long dist2 = dx * dx + dy * dy;
      long minDist = 2 * radius * scale;

      if (dist2 < (long)minDist * minDist && dist2 > 0) {
        long dist = sqrt((float)dist2);
        long overlap = (minDist - dist) / 2;

        int16_t nx = (dx * scale) / dist;
        int16_t ny = (dy * scale) / dist;

        particles[i].x -= (nx * overlap) / scale;
        particles[i].y -= (ny * overlap) / scale;
        particles[j].x += (nx * overlap) / scale;
        particles[j].y += (ny * overlap) / scale;

        int16_t tmpVx = particles[i].vx;
        int16_t tmpVy = particles[i].vy;
        particles[i].vx = (particles[j].vx * 8) / 10;
        particles[i].vy = (particles[j].vy * 8) / 10;
        particles[j].vx = (tmpVx * 8) / 10;
        particles[j].vy = (tmpVy * 8) / 10;
      }
    }
  }
}

void SandSim::draw() {
  display->clearDisplay();

  for (int i = 0; i < numParticles; i++) {
    int16_t px = particles[i].x / scale;
    int16_t py = particles[i].y / scale;

    switch (shape) {
      case Circle:
        display->fillCircle(px, py, radius, SH110X_WHITE);
        break;

      case Square:
        display->fillRect(px - radius, py - radius,
                          radius * 2, radius * 2, SH110X_WHITE);
        break;

      case RoundSquare:
        display->fillRoundRect(px - radius, py - radius,
                               radius * 2, radius * 2,
                               radius / 2, SH110X_WHITE);
        break;

      case Triangle:
        display->fillTriangle(px, py - radius,
                              px - radius, py + radius,
                              px + radius, py + radius,
                              SH110X_WHITE);
        break;

      case Char:
        display->setCursor(px, py);
        display->print("<3");
        break;
    }
  }

  display->display();
}
