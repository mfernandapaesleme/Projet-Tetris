#pragma once

#include "raylib.h"
#include <string>
#include <vector>



class WindowManager {
private:
    const int WINDOW_WIDTH = 1080;
    const int WINDOW_HEIGHT = 720;
    const char* WINDOW_TITLE = "Tetris";

    Texture2D backgroundTexture;

public:
    WindowManager() {
        // Inicializa a janela
        InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
        SetTargetFPS(60);

        // Carrega a textura de fundo
        backgroundTexture = LoadTexture("src/tetris.png");
    }

    ~WindowManager() {
        // Libera os recursos e fecha a janela
        UnloadTexture(backgroundTexture);
        CloseWindow();
    }

    void clear() {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenha o fundo
        DrawTexture(backgroundTexture, 0, 0, WHITE);
    }

    void display() {
        EndDrawing();
    }

    std::vector<KeyboardKey> updateInput();

    Vector2 getWindowSize() const {
        return Vector2{static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT)};
    }

    bool isWindowOpen() const {
        return !WindowShouldClose(); // Verifica se a janela deve ser fechada
    }
};
