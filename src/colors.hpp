#pragma once
#define NOCURSOR
#include <raylib.h>
#include <vector>

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