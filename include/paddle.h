#pragma once

#include "main.h"
#include "vendor/raylib.h"

typedef enum { LEFT, RIGHT } PaddleDirection;

typedef struct {
  Vector2 position;
  Color color;
  Dimention dimentions;
  PaddleDirection direction;
} Paddle;

void draw_paddle(Paddle *paddle);
