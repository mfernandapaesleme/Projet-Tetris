#include <raylib.h>
#include "grid.h"
#include "blocks.cpp"

int main() 
{
    const Color darkBlue = {44, 44, 127, 255};
    
    constexpr int screenWidth = 300;
    constexpr int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Tetris Game");
    SetTargetFPS(60);

    Grid grid = Grid();
    grid.Print();

    LBlock block = LBlock();
    block.Move(0, 3);

    TBlock block2 = TBlock();
    block2.Move(2, 3);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(darkBlue);
            grid.Draw();
            block.Draw();
            block2.Draw();
        EndDrawing();
    }
    
    CloseWindow();
}