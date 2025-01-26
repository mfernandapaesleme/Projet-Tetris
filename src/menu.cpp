#include "menu.h"
#include "raylib.h"

Menu::Menu() {
    isSinglePlayer = false;
    isMultiplayer = false;
    isHost = false;
}

void Menu::Update() {
    // Lógica para navegação no menu
    if (IsKeyPressed(KEY_ONE)) {
        isSinglePlayer = true;
        isMultiplayer = false;
    }
    if (IsKeyPressed(KEY_TWO)) {
        isMultiplayer = true;
        isSinglePlayer = false;
    }
}

void Menu::Render() {
    ClearBackground(BLACK);
    DrawText("TETRIS", 160, 150, 64, WHITE);
    DrawText("1 - Single Player", 100, 250, 38, WHITE);
    DrawText("2 - Multiplayer", 100, 300, 38, WHITE);
}

void Menu::Choice() {
    ClearBackground(BLACK);
    DrawText("YOU ARE", 160, 150, 64, WHITE);
    DrawText("1 - Host", 100, 250, 38, WHITE);
    DrawText("2 - Client", 100, 300, 38, WHITE);
}

void Menu::Update2() {
    if (IsKeyPressed(KEY_ONE)) {
        isHost = true;
    }
    if (IsKeyPressed(KEY_TWO)) {
        isHost = false;
    }
}