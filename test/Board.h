#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Tetromino.h"
#include "raylib.h"
#include "Constants.h"

using namespace std;

class Board {
private:
    vector<vector<int>> grid;

public:
    Board();
    bool checkCollision(const Tetromino& tetromino);
    void placeTetromino(const Tetromino& tetromino);
    void clearLines();
    void draw();
};

#endif // BOARD_H