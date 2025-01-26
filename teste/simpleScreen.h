#include "raylib.h"
#include <iostream>
#include "window.h"  
#include "State.h"

class SimpleScreen {
private:
    Font font;          // Usando a Font do Raylib
    std::string text;   // Texto a ser exibido
    Vector2 position;   // Posição do texto na tela

public:
    SimpleScreen(std::string text, WindowManager &windowManager) {
        this->text = text;

        // Carregar a fonte
        font = LoadFont("Fonts/arial.ttf"); // Use o caminho adequado para a fonte

        // Obter o tamanho da janela
        Vector2 windowSize = windowManager.getWindowSize();

        // Calcular a posição do texto para centralizar na tela
        position.x = windowSize.x / 2 - MeasureTextEx(font, this->text.c_str(), 24, 1).x / 2;
        position.y = windowSize.y / 2 - 24 / 2; // 24 é o tamanho da fonte
    }

    ~SimpleScreen() {
        UnloadFont(font); // Liberar recursos da fonte
    }

    void render(WindowManager &windowManager) {
        // Limpar a tela e desenhar o texto
        ClearBackground(BLACK);  // Limpa a tela com a cor preta
        DrawTextEx(font, text.c_str(), position, 24, 1, WHITE);  // Desenha o texto
        // Note que em Raylib, você não precisa de display como em SFML
    }

    GameState update(WindowManager &windowManager) {
        // Detectar evento de tecla (Escape)
        if (IsKeyPressed(KEY_ESCAPE)) {
            return GameState::START_SCREEN; // Mude para o estado da tela inicial
        }
        return GameState::NO_CHANGE;
    }
};
