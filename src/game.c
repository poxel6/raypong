#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void draw_game_screen(GameContext* ctx) {
    DrawText("move the paddle with HJKL", 10, 10, 20, DARKGRAY);
    draw_ball(&ctx->ball);
    draw_paddle(&ctx->paddle);
    draw_bricks(&ctx->bricks);

    for (int i = 0; i < ctx->bricks.count; i++) {
        Brick brick = ctx->bricks.brick[i];
        Rectangle rect = brick_as_rectangle(&brick);
        if (CheckCollisionCircleRec(
                ctx->ball.position, ctx->ball.radius, rect)) {
            ctx->ball.verticalDirection = DOWN;
            brick_pop(&ctx->bricks, brick.id);
        }
    }
}

GameContext new_game() {
    Paddle paddle = new_paddle();
    Ball ball = new_ball(&paddle);
    Bricks bricks = new_bricks();
    addn_brick(&bricks, 10);

    // clang-format off
    return (GameContext) {
        .ball = ball,
		.paddle = paddle,
		.bricks = bricks,
		.state = PLAYING
	};
    // clang-format on
}

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

void game_tick(GameContext* ctx) {
    paddle_move(&ctx->paddle);

    if (ctx->ball.position.y > HEIGHT) {
        ctx->state = GAMEOVER;
    }

    checkWallCollision(&ctx->ball);
    switch (ctx->ball.verticalDirection) {
    case UP: {
        if (ctx->ball.position.y - ctx->ball.radius <= 0) {
            ctx->ball.verticalDirection = DOWN;
        }

        ctx->ball.position.y -= GetFrameTime() * 200;
        break;
    }

    case DOWN: {
        bool collisionWithPaddle =
            CheckCollisionCircleRec(ctx->ball.position,
                                    ctx->ball.radius,
                                    paddle_as_rectangle(&ctx->paddle));

        if (collisionWithPaddle) {
            ctx->ball.verticalDirection = UP;
            switch (ctx->paddle.direction) {
            case RIGHT:
                ctx->ball.sideDirection = LEFT;
                break;
            case LEFT:
                ctx->ball.sideDirection = RIGHT;
                break;
            }
        }

        ctx->ball.position.y += GetFrameTime() * 200;

        break;
    }
    }

    switch (ctx->ball.sideDirection) {
    case LEFT:
        ctx->ball.position.x += GetFrameTime() * (150 + (rand() % 50));
        break;
    case RIGHT:
        ctx->ball.position.x -= GetFrameTime() * (150 + (rand() % 50));
        break;
    }
}
