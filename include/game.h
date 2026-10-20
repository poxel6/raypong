#pragma once

#include "vendor/raylib.h"

#include "ball.h"
#include "bricks.h"
#include "main.h"
#include "paddle.h"

typedef struct {
  Ball ball;
  Paddle paddle;
  Bricks bricks;

  GameState state;

} GameContext;

void draw_game_screen(GameContext *ctx);
GameContext new_game();
