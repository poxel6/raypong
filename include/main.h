#pragma once

#include "vendor/raylib.h"
#include <stdint.h>

#define WIDTH 1200
#define HEIGHT 720

typedef enum : bool { RIGHT, LEFT } HorizontalDirection;
typedef enum : bool { UP, DOWN } VerticalDirection;
typedef enum { WELCOME, PLAYING, GAMEOVER } GameState;

typedef struct {
  int32_t x, y;
} IntVector2;

typedef IntVector2 Position;
typedef IntVector2 Dimention;
