#include "main.h"

#include <stdlib.h>
#include <time.h>

#include "ball.h"
#include "bricks.h"
#include "paddle.h"
#include "vendor/raylib.h"

typedef struct {
    int width, height;

    Ball ball;
    Paddle paddle;
    Bricks bricks;

    GameState state;

} GameContext;

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


static void draw_gameover_screen() {
    int fontsize = 72;
    int centerY = ((HEIGHT) / 2) - 50;
    int centerX = ((WIDTH) / 2) - (fontsize * 3);

    DrawText("GAME OVER", centerX, centerY, fontsize, RED);
}

int main(void) {
    srand(time(NULL));
    const char* title = "Hello World";
    InitWindow(WIDTH, HEIGHT, title);
	bool gameover = false;
	GameState state = PLAYING;

    Paddle paddle = new_paddle();
    Ball ball = new_ball(&paddle);
    Bricks bricks = new_bricks();
    addn_brick(&bricks, 10);


    while (!WindowShouldClose()) {
        paddle_move(&paddle);

        checkWallCollision(&ball);

        if (ball.position.y > HEIGHT) {
            gameover = true;
			state = GAMEOVER;
        }

        switch (ball.verticalDirection) {
        case UP: {
            if (ball.position.y - ball.radius <= 0) {
                ball.verticalDirection = DOWN;
            }

            ball.position.y -= GetFrameTime() * 200;
            break;
        }

        case DOWN: {
            bool collisionWithPaddle = CheckCollisionCircleRec(
                ball.position, ball.radius, paddle_as_rectangle(&paddle));

            if (collisionWithPaddle) {
                ball.verticalDirection = UP;
                switch (paddle.direction) {
                case RIGHT:
                    ball.sideDirection = LEFT;
                    break;
                case LEFT:
                    ball.sideDirection = RIGHT;
                    break;
                }
            }

            ball.position.y += GetFrameTime() * 200;

            break;
        }
        }

        switch (ball.sideDirection) {
        case LEFT:
            ball.position.x += GetFrameTime() * (150 + (rand() % 50));
            break;
        case RIGHT:
            ball.position.x -= GetFrameTime() * (150 + (rand() % 50));
            break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (gameover) {
            draw_gameover_screen();
        } else {
            DrawText("move the paddle with HJKL", 10, 10, 20, DARKGRAY);

            draw_ball(&ball);
            for (int i = 0; i < bricks.count; i++) {
                Brick brick = bricks.brick[i];
                Rectangle rect = brick_as_rectangle(&brick);
                if (CheckCollisionCircleRec(ball.position, ball.radius, rect)) {
                    ball.verticalDirection = DOWN;
                    DrawText("COLLISION", 10, 10, 50, DARKGRAY);
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
