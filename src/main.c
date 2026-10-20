#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "vendor/raylib.h"

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
    GameContext ctx = new_game();

    while (!WindowShouldClose()) {
        switch (ctx.state) {
        case PLAYING:
            game_tick(&ctx);
            break;
        case WELCOME:
            break;
        case GAMEOVER:
            if (IsKeyPressed(KEY_Q)) {
                CloseWindow();
                exit(0);
            } else if (IsKeyPressed(KEY_R)) {
                ctx = new_game();
            }
            break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (ctx.state) {
        case WELCOME:
            break;
        case PLAYING:
            draw_game_screen(&ctx);
            break;
        case GAMEOVER:
            draw_gameover_screen();
            break;
        }
        EndDrawing();
    }
}
