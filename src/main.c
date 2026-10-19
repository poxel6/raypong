// TODO: paddle collision is fucked up
// TODO: when ball collisides with bricks from sides it doesn't change side direction
// TODO: code is a fucking mess
#include "main.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "ball.h"
#include "bricks.h"
#include "paddle.h"
#include "vendor/raylib.h"

#define WIDTH 1200
#define HEIGHT 720

static void checkWallCollision(Ball* ball) {
    if (ball->position.x - ball->radius < 0 ||
        ball->position.x + ball->radius > WIDTH) {
        switch (ball->sideDirection) {
        case RIGHT:
            ball->sideDirection = LEFT;
            break;
        case LEFT:
            ball->sideDirection = RIGHT;
            break;
        }
    }
}

int main(void) {
    const int screenWidth = WIDTH;
    const int screenHeight = HEIGHT;
    const char* title = "Hello World";
    InitWindow(screenWidth, screenHeight, title);

    Paddle paddle = {
        // clang-format off
        .position = {
			.x = (screenWidth / 2) - 50, 
			.y = 600
		},
        .dimentions = {
			.x = 100,                   
			.y = 10
		},
        // clang-format on
        .color = RED,
    };

    Ball ball = {
        // clang-format off
        .position = {
			.x = screenWidth / 2,
			.y = screenHeight / 2,
		},
        // clang-format on
        .direction = DOWN,
        .radius = 10,
        .sideDirection = (SideDirection)paddle.direction
    };

    Bricks bricks = new_bricks();
    addn_brick(&bricks, 10);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_L)) {
            paddle.position.x += 500 * GetFrameTime();
            paddle.direction = RIGHT;
        }
        if (IsKeyDown(KEY_H)) {
            paddle.position.x -= 500 * GetFrameTime();
            paddle.direction = LEFT;
        }

        checkWallCollision(&ball);

        switch (ball.direction) {
        case UP: {
            if (ball.position.y - ball.radius <= 0) {
                ball.direction = DOWN;
            }

            ball.position.y -= GetFrameTime() * 200;
            break;
        }

        case DOWN: {
            float paddle_start = paddle.position.x - (paddle.dimentions.x / 2);
            float paddle_end = paddle.position.x + (paddle.dimentions.x / 2);
            bool collisionWithPaddle = ((ball.position.x >= paddle_start ||
                                         ball.position.x <= paddle_end)) &&
                                       ball.position.y + 10 >= 600;

            if (collisionWithPaddle) {
                ball.direction = UP;
            }

            ball.position.y += GetFrameTime() * 200;

            break;
        }
        }

        switch (ball.sideDirection) {
        case LEFT:
            ball.position.x += GetFrameTime() * 200;
            break;
        case RIGHT:
            ball.position.x -= GetFrameTime() * 200;
            break;
        }

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            DrawCircle(ball.position.x, ball.position.y, ball.radius, SKYBLUE);
            DrawText("move the paddle with HJKL", 10, 10, 20, DARKGRAY);
            for (int i = 0; i < bricks.count; i++) {
                Brick brick = bricks.brick[i];
                Rectangle rect = (Rectangle){.width = brick.dimentions.x,
                                             .height = brick.dimentions.y,
                                             .x = brick.position.x,
                                             .y = brick.position.y

                };
                if (CheckCollisionCircleRec(ball.position, ball.radius, rect)) {
                    ball.direction = DOWN;

                    DrawText("COLLISION", 10, 10, 50, DARKGRAY);
                    // TODO: it only check for collision with one of the
                    // rectangles
                    brick_pop(&bricks, brick.id);
                }
            }
            draw_paddle(&paddle);
            draw_bricks(&bricks);
        }
        EndDrawing();
    }

    return 0;
}
