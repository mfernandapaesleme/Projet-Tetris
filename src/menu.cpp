#include "menu.h"
#include "raylib.h"


// Constructeur du menu, initialise les options de jeu
Menu::Menu() {
    isSinglePlayer = false;     // Jeu en solo désactivé
    isMultiplayer = false;      // Jeu en multijoueur désactivé
    isHost = false;             // L'hôte du multijoueur désactivé
}

void Menu::Update() {
    // Met à jour l'état du menu en fonction des touches pressées
    if (IsKeyPressed(KEY_ONE)) {
        isSinglePlayer = true;
        isMultiplayer = false;
    }
    if (IsKeyPressed(KEY_TWO)) {
        isMultiplayer = true;
        isSinglePlayer = false;
    }
}

// Affiche le menu principal avec les choix disponibles
void Menu::Render() {
    ClearBackground(BLACK);
    DrawText("TETRIS", 160, 150, 64, WHITE);
    DrawText("1 - Single Player", 100, 250, 38, WHITE);
    DrawText("2 - Multiplayer", 100, 300, 38, WHITE);
}

// Affiche le menu de sélection du rôle pour le multijoueur
void Menu::Choice() {
    ClearBackground(BLACK);
    DrawText("YOU ARE", 160, 150, 64, WHITE);
    DrawText("1 - Host", 100, 250, 38, WHITE);
    DrawText("2 - Client", 100, 300, 38, WHITE);
}


// Met à jour l'état du rôle dans le menu multijoueur
void Menu::Update2() {
    if (IsKeyPressed(KEY_ONE)) {
        isHost = true;
    }
    if (IsKeyPressed(KEY_TWO)) {
        isHost = false;
    }
}