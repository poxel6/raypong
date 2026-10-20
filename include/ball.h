#pragma once

#include "bricks.h"
#include "main.h"
#include "paddle.h"
#include "vendor/raylib.h"
#include <stdint.h>

typedef struct Ball {
  uint8_t radius;
  Vector2 position;
  float velocity;
  VerticalDirection verticalDirection;
  HorizontalDirection sideDirection;
} Ball;

void draw_ball(Ball *ball);
void ball_flip_side_direction(Ball *ball);
void ball_flip_vertical_direction(Ball *ball);
Ball new_ball(Paddle *paddle);
