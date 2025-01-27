#include <raylib.h>
#include "network/networkManager.hpp"
#include "game.h"
#include "menu.h"
#include "gamestate.hpp"
#include "blocks.cpp"
#include <stdio.h>
#include <iostream>

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

    const int screenWidth = 500;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Tetris Game");
    SetTargetFPS(60);

    Game game;
    Menu menu;
    GameState currentState = GameState::MENU;

    // Inicia o servidor na porta 4545
    NetworkManager server(0, "", 4545);
    server.start();

    // Aguarda e recebe a mensagem do cliente
    std::string message = server.receive();
    std::cout << "Mensagem recebida do cliente: " << message << std::endl;

    // Envia uma resposta para o cliente
    server.send("Olá, Cliente!");

    // Fecha o servidor
    return 0;

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
            break;
        case GameState::SEARCHING_FOR_SERVER:
            break;
        default:
            break;
        }

        EndDrawing();
    }
    CloseWindow(); // Fechar a janela
    return 0;
}