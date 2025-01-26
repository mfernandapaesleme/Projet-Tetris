#include "window.h"
#include <iostream>
#include <vector>

std::vector<KeyboardKey> WindowManager::updateInput() {
    std::vector<KeyboardKey> keysPressed;

    // Verifica se a janela deve ser fechada
    if (WindowShouldClose()) {
        CloseWindow(); // Fecha a janela
    }

    // Captura todas as teclas pressionadas no frame
    for (int key = KEY_SPACE; key <= KEY_KP_EQUAL; ++key) {
        if (IsKeyPressed(static_cast<KeyboardKey>(key))) {
            keysPressed.push_back(static_cast<KeyboardKey>(key));
        }
    }

    return keysPressed;
}
