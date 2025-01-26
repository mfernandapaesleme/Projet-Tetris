#pragma once
#include "raylib.h"

class Menu {
public:
    Menu();
    void Update();
    void Render();
    void Choice();
    void Update2();
    void SinglePlayer(int score, int gameOver);
    bool isSinglePlayer;
    bool isMultiplayer;
    bool isHost;
};

