#include "menu.h"
#include "raylib.h"
#include <stdio.h>

// Constructeur de la classe Menu
Menu::Menu() {
    isSinglePlayer = false;
    isMultiplayer = false;
    isHost = false;
}

// Méthode qui met à jour l'état du menu en fonction des touches pressées
void Menu::Update() {
    // Logique de navigation dans les menus
    if (IsKeyPressed(KEY_ONE)) {
        isSinglePlayer = true;
        isMultiplayer = false;
    }
    if (IsKeyPressed(KEY_TWO)) {
        isMultiplayer = true;
        isSinglePlayer = false;
    }
}


// Méthode qui rend (affiche) le menu principal
void Menu::Render() {
    ClearBackground(BLACK);
    DrawText("TETRIS", 160, 150, 64, WHITE);
    DrawText("1 - Single Player", 100, 250, 38, WHITE);
    DrawText("2 - Multiplayer", 100, 300, 38, WHITE);
}


// Méthode qui affiche le menu de choix 
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


// Méthode qui affiche le score et l'état du jeu pour le mode solo
void Menu::SinglePlayer(int score, int gameOver) {
    const Color lightBlue = {59, 85, 162, 255};
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
    DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
    char scoreText[10];
    sprintf(scoreText, "%d", score);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
    DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
    DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
    if(gameOver) {
        DrawTextEx(font, "GAME OVER", {320, 450}, 28, 2, RED);
        DrawTextEx(font, "Press R to restart", {320, 500}, 16, 2, WHITE);
    }
}