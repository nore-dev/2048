
#include "raylib.h"
#include "game.hpp"

int main(void)
{
    const int screenWidth = 480;
    const int screenHeight = 640;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Game game = Game();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("2048", 100, 60, 60, GRAY);
        DrawText(TextFormat("Score: %d", game.getScore()), 300, 60, 40, GRAY);

        game.drawGrid(120);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}