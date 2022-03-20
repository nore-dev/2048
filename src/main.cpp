
#include "raylib.h"
#include "game.hpp"

int main(void)
{
    const int screenWidth = 480;
    const int screenHeight = 640;

    InitWindow(screenWidth, screenHeight, "2048");

    Game game = Game();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_A))
            game.slide(COLUMN);

        if (IsKeyPressed(KEY_D))
            game.slide(COLUMN, true);

        if (IsKeyPressed(KEY_S))
            game.slide(ROW, true);

        if (IsKeyPressed(KEY_W))
            game.slide(ROW);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("2048", 30, 60, 60, GRAY);

        const char *text = TextFormat("Score: %d", game.getScore());

        if (game.isGameOver())
            text = "Game Over!";

        DrawText(text, 200, 70, 40, GRAY);

        game.drawGrid(100);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}