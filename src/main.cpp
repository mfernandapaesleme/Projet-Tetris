//#include "network/networkManager.hpp"
#include <raylib.h>
#include "game.h"
#include "menu.h"
#include "gamestate.hpp"
#include "blocks.cpp"
#include <stdio.h>

double lastUpdateTime = 0;
bool EventTriggered(){
    double currentTime = GetTime();

    if ((currentTime - lastUpdateTime) >= 1){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
    }

int main() {

    const Color darkBlue = {44, 44, 127, 255};

   /*  NetworkManager server(0, "127.0.0.1", 12345);
    server.start();

    NetworkManager client(1, "127.0.0.1", 12345);
    client.start(); */


    const int screenWidth = 500;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Tetris Game");
    SetTargetFPS(60);

    Game game;
    Menu menu;
    //NetworkManager networkManager;
    GameState currentState = GameState::MENU;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(darkBlue);

        switch (currentState)
        {
        case GameState::MENU:
            menu.Update();
            menu.Render();
            if (menu.isSinglePlayer) {
                currentState = GameState::SINGLE_PLAYER;
            }
            if (menu.isMultiplayer) {
                currentState = GameState::CHOICE;
            }
            break;
        
        case GameState::SINGLE_PLAYER:
            game.HandleInput();
            if (EventTriggered() && !game.gameOver)
            {
                game.Update();
            }
          
            menu.SinglePlayer(game.score, game.gameOver);
            game.Draw();
            /* if (game.gameOver) {
                currentState = GameState::MENU;
                game.Reset();
            } */
            break;
        case GameState::CHOICE:
            menu.Choice();
            menu.Update2();
            if (menu.isHost) {
                currentState = GameState::WAITING_FOR_CONNECTION;
            }
            else {
                currentState = GameState::SEARCHING_FOR_SERVER;
            }
            break;
        case GameState::WAITING_FOR_CONNECTION:
            //networkManager.startServer(54000);
            //networkManager.waitForClients();
            break;
        case GameState::SEARCHING_FOR_SERVER:
            //networkManager.connectToServer("  
            break;
        default:
            break;
        }

        EndDrawing();
    }
    CloseWindow(); // Fechar a janela
    return 0;
}
