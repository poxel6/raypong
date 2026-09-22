#include "paddle.h"

#include "vendor/raylib.h"

void draw_paddle(Paddle* paddle) {
    DrawRectangle((int) paddle->position.x,
                  (int) paddle->position.y,
                  paddle->dimentions.x,
                  paddle->dimentions.y,
                  paddle->color);
}
