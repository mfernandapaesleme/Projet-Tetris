#pragma once
#include <raylib.h>
#include <vector>

// Fonction inline pour obtenir la liste des couleurs des cellules
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