
#include "raylib.h"
#include "game.hpp"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main(void)
{
    const int screenWidth = 480;
    const int screenHeight = 640;

    InitWindow(screenWidth, screenHeight, "2048");

    SetGesturesEnabled(GESTURE_SWIPE_DOWN | GESTURE_SWIPE_LEFT | GESTURE_SWIPE_RIGHT | GESTURE_SWIPE_UP);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);

    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, ColorToInt(GRAY));
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(LIGHTGRAY));

    GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, ColorToInt(DARKGRAY));
    GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(GRAY));

    // GuiSetStyle(DEFAULT, BACKGROUND_COLOR, );
    Game game = Game();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_A) || IsGestureDetected(GESTURE_SWIPE_LEFT))
            game.slide(COLUMN);

        if (IsKeyPressed(KEY_D) || IsGestureDetected(GESTURE_SWIPE_RIGHT))
            game.slide(COLUMN, true);

        if (IsKeyPressed(KEY_S) || IsGestureDetected(GESTURE_SWIPE_DOWN))
            game.slide(ROW, true);

        if (IsKeyPressed(KEY_W) || IsGestureDetected(GESTURE_SWIPE_UP))
            game.slide(ROW);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("2048", 30, 60, 60, GRAY);

        DrawText(TextFormat("Score: %d", game.getScore()), 200, 70, 40, GRAY);

        if (game.isGameOver())
        {
            game.drawGrid(100, 100);

            const char *text = "Game Over!";
            int width = MeasureText(text, 70);
            DrawText(text, (GetScreenWidth() - width) / 2, 240, 70, DARKGRAY);

            if (GuiButton({(float)(GetScreenWidth() - 160) / 2, 300, 160, 60}, "Try Again"))
                game.reset();
        }
        else
            game.drawGrid(100, 255);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}