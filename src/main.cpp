#include <raylib.h>
#include "game.h"
#include "blocks.cpp"
#include <stdio.h>

double lastUpdateTime = 0;

bool EventTriggered()
{
    double currentTime = GetTime();

    if ((currentTime - lastUpdateTime) >= 1)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main() 
{
    const Color darkBlue = {44, 44, 127, 255};
    const Color lightBlue = {59, 85, 162, 255};
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    constexpr int screenWidth = 500;
    constexpr int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Tetris Game");
    SetTargetFPS(60);

    // Menu state
    bool isMenu = true;
    bool isGameRunning = false;

    Game game = Game();

    while (!WindowShouldClose())
    {
        // Menu Logic
        if (isMenu)
        {
            BeginDrawing();
            ClearBackground(darkBlue);

            DrawTextEx(font, "TETRIS", {160, 150}, 64, 2, WHITE);
            DrawTextEx(font, "Press [ENTER] to Start", {100, 250}, 38, 2, WHITE);
            DrawTextEx(font, "Press [ESC] to Exit", {100, 300}, 38, 2, WHITE);

            if (IsKeyPressed(KEY_ENTER))
            {
                isMenu = false; // Start the game
                isGameRunning = true;
            }
            if (IsKeyPressed(KEY_ESCAPE))
            {
                break; // Exit the game
            }

            EndDrawing();
        }
        // Game Logic
        else if (isGameRunning)
        {
            game.HandleInput();
            if (EventTriggered() && !game.gameOver)
            {
                game.Update();
            }

            BeginDrawing();
            ClearBackground(darkBlue);
            DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
            DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);

            if (game.gameOver)
            {
                DrawTextEx(font, "GAME OVER", {320, 450}, 28, 2, WHITE);
            }

            DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

            DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
            DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

            game.Draw();

            EndDrawing();
        }
    }

    CloseWindow(); // Close window and OpenGL context
}