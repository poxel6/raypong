#pragma once

#include "bricks.h"
#include "main.h"
#include "vendor/raylib.h"
#include <stdint.h>

typedef enum : bool { UP, DOWN } BallDirection;

typedef struct {
  uint8_t radius;
  Vector2 position;
  float velocity;
  BallDirection direction;
  SideDirection sideDirection;
} Ball;
