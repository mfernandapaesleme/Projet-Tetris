#pragma once
#define NOCURSOR
#include <raylib.h>
#include <vector>


// Fonction inline qui retourne une liste des couleurs associées aux cellules du jeu.
inline std::vector<Color> GetCellColors() {
    return {
        BLACK,  // empty cell
        RED,    // I
        BLUE,   // J
        GREEN,  // L
        YELLOW, // O
        ORANGE, // S
        VIOLET, // T
        PINK    // Z
    };
}