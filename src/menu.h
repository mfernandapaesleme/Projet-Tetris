#ifndef MENU_H
#define MENU_H

#include "raylib.h"

class Menu {
public:
    Menu();
    void Update();
    void Render();
    void Choice();
    void Update2();
    bool isSinglePlayer;
    bool isMultiplayer;
    bool isHost;
};

#endif // MENU_H
