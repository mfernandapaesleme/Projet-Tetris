#pragma once

#include "State.h"
#include "game.h"
#include "menu.h"
#include "simpleScreen.h"
#include "Network.h" // Inclua o NetworkManager se necessário

class StateManager {
private:
    GameState state;
    NetworkManager networkManager;
    Game *game;
    Menu menu;
    SimpleScreen host = SimpleScreen("Waiting for connection");
    SimpleScreen join = SimpleScreen("Searching for server");
    SimpleScreen gameover = SimpleScreen("Game Over");
    SimpleScreen youWon = SimpleScreen("You Won");

public:
    StateManager() : state(GameState::START_SCREEN) {}

    GameState getCurrentState() const { return state; }

    // Função que muda o estado
    void changeState(GameState newState);

    // Função para verificar se o jogo está rodando (diferente do SFML)
    bool isRunning() {
        return !WindowShouldClose();
    }

    // Atualiza o estado do jogo (similar ao SFML)
    void update() {
        switch (state) {
            case GameState::START_SCREEN:
                changeState(menu.update());
                break;
            case GameState::PLAYING:
                if (!game) game = new Game();
                changeState(game->update());
                break;
            case GameState::GAME_OVER:
                changeState(gameover.update());
                break;
            case GameState::WAITING_FOR_CONNECTION:
                changeState(host.update());
                networkManager.listen();
                if (networkManager.getConnectionStatus() == NetworkManager::ConnectionStatus::Connected) {
                    changeState(GameState::PLAYING);
                }
                break;
            case GameState::SEARCHING_FOR_SERVER:
                changeState(join.update());
                if (networkManager.connectToServer(menu.getIp()) == 0) {
                    changeState(GameState::PLAYING);
                }
                break;
            case GameState::YOU_WON:
                changeState(youWon.update());
                break;
            default:
                break;
        }
    }

    // Renderiza a tela (similar ao SFML)
    void render() {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (state) {
            case GameState::START_SCREEN:
                menu.render();
                break;
            case GameState::PLAYING:
                game->render();
                break;
            case GameState::GAME_OVER:
                gameover.render();
                break;
            case GameState::WAITING_FOR_CONNECTION:
                host.render();
                break;
            case GameState::SEARCHING_FOR_SERVER:
                join.render();
                break;
            case GameState::YOU_WON:
                youWon.render();
                break;
            default:
                break;
        }

        EndDrawing();
    }
};
