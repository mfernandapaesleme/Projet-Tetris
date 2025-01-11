#include <raylib.h>
#include "game.h"
#include "blocks.cpp"

int main() 
{
    const Color darkBlue = {44, 44, 127, 255};
    
    constexpr int screenWidth = 300;
    constexpr int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Tetris Game");
    SetTargetFPS(60);

    Game game = Game();

/*     IBlock iBlock = IBlock(); */
/*     JBlock jBlock = JBlock();
    LBlock lBlock = LBlock();   
    OBlock oBlock = OBlock();   
    SBlock sBlock = SBlock();
    TBlock tBlock = TBlock();
    ZBlock zBlock = ZBlock(); */
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(darkBlue);
            game.Draw();
            //iBlock.Draw();
            //jBlock.Draw();
           // lBlock.Draw();
            //oBlock.Draw();
           // sBlock.Draw();
          //  tBlock.Draw();
          //  zBlock.Draw();

        EndDrawing();
    }
    
    CloseWindow();
}