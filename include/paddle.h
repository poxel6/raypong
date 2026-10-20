#pragma once

#include "main.h"
#include "vendor/raylib.h"

typedef struct {
  Vector2 position;
  Color color;
  Dimention dimentions;
  HorizontalDirection direction;
} Paddle;

void draw_paddle(Paddle *paddle);
Paddle new_paddle();
Rectangle paddle_as_rectangle(Paddle* paddle);
void paddle_move(Paddle* paddle);
