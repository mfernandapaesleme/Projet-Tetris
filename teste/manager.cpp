#include "manager.h"
#include "NetworkManager.hpp"  // Adicione isso se necessário

// Função que verifica se a janela deve ser fechada
bool StateManager::isRunning() {
    return !WindowShouldClose();  // Em Raylib, isso verifica se a janela deve ser fechada
}

// Função que altera o estado do jogo
void StateManager::changeState(GameState newState) {
    if (newState == GameState::NO_CHANGE) return;

    state = newState;
    if (state == GameState::PLAYING) {
        game = new Game();
    } else if (state == GameState::WAITING_FOR_CONNECTION) {
        if (networkManager.listen() == -1) {
            changeState(GameState::START_SCREEN);
        }
    }
}

// Função que atualiza o estado do jogo
void StateManager::update() {
    switch (state) {
        case GameState::START_SCREEN:
            networkManager.disconnect();
            changeState(menu.update());  // Atualiza o menu, sem a necessidade de windowManager
            break;
        case GameState::PLAYING:
            changeState(game->update(networkManager));  // Atualiza o jogo
            break;
        case GameState::GAME_OVER:
            networkManager.disconnect();
            changeState(gameover.update());  // Atualiza a tela de game over
            break;
        case GameState::WAITING_FOR_CONNECTION:
            changeState(host.update());  // Atualiza a tela de espera de conexão
            networkManager.accept();
            if (networkManager.getConnectionStatus() == NetworkManager::ConnectionStatus::Done) {
                changeState(GameState::PLAYING);
            }
            break;
        case GameState::SEARCHING_FOR_SERVER:
            changeState(join.update());  // Atualiza a tela de busca por servidor
            if (networkManager.connectToServer(menu.getIp()) == 0) {
                changeState(GameState::PLAYING);
            }
            break;
        case GameState::YOU_WON:
            networkManager.disconnect();
            changeState(youWon.update());  // Atualiza a tela de vitória
            break;
    }
}

// Função que renderiza o conteúdo da tela, dependendo do estado
void StateManager::render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);  // Limpa o fundo

    switch (state) {
        case GameState::START_SCREEN:
            menu.render();  // Renderiza o menu
            break;
        case GameState::PLAYING:
            game->render();  // Renderiza o jogo
            break;
        case GameState::GAME_OVER:
            gameover.render();  // Renderiza a tela de game over
            break;
        case GameState::WAITING_FOR_CONNECTION:
            host.render();  // Renderiza a tela de espera de conexão
            break;
        case GameState::SEARCHING_FOR_SERVER:
            join.render();  // Renderiza a tela de busca por servidor
            break;
        case GameState::YOU_WON:
            youWon.render();  // Renderiza a tela de vitória
            break;
    }

    EndDrawing();  // Finaliza o desenho na tela
}
