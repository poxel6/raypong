#include "paddle.h"

#include "main.h"
#include "vendor/raylib.h"

Rectangle paddle_as_rectangle(Paddle* paddle) {
    return (Rectangle){
        .x = paddle->position.x,
        .y = paddle->position.y,
        .width = paddle->dimentions.x,
        .height = paddle->dimentions.y,
    };
}

void draw_paddle(Paddle* paddle) {
    DrawRectangleRec(paddle_as_rectangle(paddle), paddle->color);
}

Paddle new_paddle() {
    return (Paddle){
        // clang-format off
        .position = {
			.x = ((WIDTH) / 2) - 50, 
			.y = 600
		},
        .dimentions = {
			.x = 100,                   
			.y = 10
		},
        // clang-format on
        .color = RED,
    };
}
void paddle_move(Paddle* paddle) {
    if (IsKeyDown(KEY_L)) {
        paddle->position.x += 500 * GetFrameTime();
        paddle->direction = RIGHT;
    }

    if (IsKeyDown(KEY_H)) {
        paddle->position.x -= 500 * GetFrameTime();
        paddle->direction = LEFT;
    }
}
