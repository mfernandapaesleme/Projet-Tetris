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
    
    constexpr int screenWidth = 300;
    constexpr int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Tetris Game");
    SetTargetFPS(60);

    Game game = Game();

    while (!WindowShouldClose())
    {
        game.HandleInput();
        if (EventTriggered())
        {
            game.Update();
        }
        BeginDrawing();
            ClearBackground(darkBlue);
            game.Draw();
        EndDrawing();
    }
    
    CloseWindow();
}