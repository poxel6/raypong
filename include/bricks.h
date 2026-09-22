#pragma once

#include "main.h"
#include "vendor/raylib.h"

#define MAX_BRICKS 255
#define BRICK_SIZE 50
#define OFFSET 6

typedef struct {
	int health;
	Color color;
	Vector2 position;
	Dimention dimentions;
} Brick;

typedef struct {
	Brick brick[MAX_BRICKS];
	int count;
} Bricks;

void draw_bricks(Bricks* bricks);
Brick new_brick();
Bricks new_bricks();
void add_brick(Bricks* bricks);
void addn_brick(Bricks* bricks, int number);
