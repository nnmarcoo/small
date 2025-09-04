#pragma once
#include "SandSim.h"

SandSimConfig largeBalls = {
  .numParticles = random(1, 5),
  .gravity = 30,
  .damping = 105,
  .radius = 8,
  .scale = 100,
  .collisionsEnabled = true,
};

SandSimConfig denseSandCollisions = {
  .numParticles = 200,
  .gravity = 30,
  .damping = 98,
  .radius = 1,
  .scale = 100,
  .collisionsEnabled = true,
};

SandSimConfig denseSand = {
  .numParticles = 500,
  .gravity = 30,
  .damping = 100,
  .radius = 1,
  .scale = 100,
  .collisionsEnabled = false,
};

SandSimConfig randomSandCollision = {
  .numParticles = random(10, 35),
  .gravity = random(30, 41),
  .damping = random(95, 101),
  .radius = random(1, 8),
  .scale = 100,
  .collisionsEnabled = true,
};

SandSimConfig randomSand = {
  .numParticles = random(10, 100),
  .gravity = random(30, 41),
  .damping = random(95, 101),
  .radius = random(1, 8),
  .scale = 100,
  .collisionsEnabled = false,
};

SandSimConfig presets[] = {
  largeBalls,
  denseSandCollisions,
  denseSand,
  randomSandCollision,
  randomSand
};