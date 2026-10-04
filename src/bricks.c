#include "bricks.h"

#include "vendor/raylib.h"
#include <stdint.h>

static int brick_count = 0;
static uint8_t id_counter = 0;

static void draw_brick(Brick* brick) {
    DrawRectangle((int)brick->position.x,
                  (int)brick->position.y,
                  brick->dimentions.x,
                  brick->dimentions.y,
                  brick->color);
}

void draw_bricks(Bricks* bricks) {
    for (int i = 0; i < bricks->count; i++) {
		if (bricks->brick[i].id == -1) {
			continue;
		}
        draw_brick(&bricks->brick[i]);
    }
}

Brick new_brick() {
    Brick brick = {
		.id = id_counter++,
        // clang-format off
    	.position = {
			.x = (float) (BRICK_SIZE * (OFFSET + brick_count )),
			.y = 100
			// .y = (float) (BRICK_SIZE * brick_count),
	   	},
        // clang-format on
        .dimentions = {BRICK_SIZE - 1, BRICK_SIZE - 1},
        .color = RED,
        .health = 1,
    };

    return brick;
}

Bricks new_bricks() {
    Bricks bricks = {
        .brick = new_brick(),
        .count = brick_count += 1,
    };

    return bricks;
}

void add_brick(Bricks* bricks) {
    bricks->brick[bricks->count] = new_brick();
    bricks->count += 1;
    brick_count += 1;
}

void addn_brick(Bricks* bricks, int number) {
    for (int i = 0; i < number; i++) {
        add_brick(bricks);
    }
}

Brick brick_pop(Bricks* bricks, int id) {
	for (int i = 0; i < bricks->count; i++) {
		if (bricks->brick[i].id == id) {
			bricks->brick[i].id = -1;
		}
	}
}
