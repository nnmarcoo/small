#pragma once
#include <Adafruit_SH110X.h>
#include <Arduino_LSM6DSOX.h>

struct Particle {
  int16_t x;
  int16_t y;
  int16_t vx;
  int16_t vy;
};

struct SandSimConfig {
  int numParticles;
  int16_t gravity;
  int16_t damping;
  int16_t radius;
  int16_t scale;
  bool collisionsEnabled;
};

enum Shape {
  Circle,
  Square,
  RoundSquare,
  Triangle,
  Char,
};

class SandSim {
public:
  SandSim(Adafruit_SH1107* display, const SandSimConfig& config);

  void begin();
  void update();
  void draw();

private:
  Particle* particles;
  int numParticles;

  int16_t gravity;
  int16_t damping;
  int16_t radius;
  int16_t scale;
  bool collisionsEnabled;
  Shape shape;

  Adafruit_SH1107* display;

  void handleBoundaries(Particle& p);
  void handleCollisions();
};
