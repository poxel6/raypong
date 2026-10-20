#include "ball.h"

#include "main.h"
#include "vendor/raylib.h"

void draw_ball(Ball* ball) {
    DrawCircle(ball->position.x, ball->position.y, ball->radius, SKYBLUE);
}

void ball_flip_side_direction(Ball* ball) {
    switch (ball->sideDirection) {
    case RIGHT:
        ball->sideDirection = LEFT;
        break;
    case LEFT:
        ball->sideDirection = RIGHT;
        break;
    }
}

void ball_flip_vertical_direction(Ball* ball) {
    switch (ball->verticalDirection) {
    case UP:
        ball->verticalDirection = DOWN;
        break;
    case DOWN:
        ball->verticalDirection = UP;
        break;
    }
}

Ball new_ball(Paddle* paddle) {
    return (Ball){
        // clang-format off
        .position = {
			.x = (WIDTH) / 2,
			.y = (HEIGHT) / 2,
		},
        // clang-format on
        .verticalDirection = DOWN,
        .radius = 10,
        .sideDirection = (HorizontalDirection)paddle->direction
    };
}
