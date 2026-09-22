#pragma once

#include "main.h"
#include "vendor/raylib.h"

typedef struct {
	Vector2 position;
	Color color;
	Dimention dimentions;
} Paddle;

void draw_paddle(Paddle* paddle);
