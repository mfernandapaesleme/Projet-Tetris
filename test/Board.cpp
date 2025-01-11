#include "Board.h"
#include "Constants.h"

Board::Board() : grid(BOARD_HEIGHT, vector<int>(BOARD_WIDTH, 0)) {}

bool Board::checkCollision(const Tetromino& tetromino) {
    const auto& shape = tetromino.getShape();
    int x = tetromino.getX();
    int y = tetromino.getY();

    for (int i = 0; i < shape.size(); i++) {
        for (int j = 0; j < shape[i].size(); j++) {
            if (shape[i][j]) {
                int newX = x + j;
                int newY = y + i;
                if (newX < 0 || newX >= BOARD_WIDTH || newY >= BOARD_HEIGHT || (newY >= 0 && grid[newY][newX])) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::placeTetromino(const Tetromino& tetromino) {
    const auto& shape = tetromino.getShape();
    int x = tetromino.getX();
    int y = tetromino.getY();

    for (int i = 0; i < shape.size(); i++) {
        for (int j = 0; j < shape[i].size(); j++) {
            if (shape[i][j]) {
                grid[y + i][x + j] = shape[i][j];
            }
        }
    }
}

void Board::clearLines() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        if (all_of(grid[i].begin(), grid[i].end(), [](int cell) { return cell != 0; })) {
            grid.erase(grid.begin() + i);
            grid.insert(grid.begin(), vector<int>(BOARD_WIDTH, 0));
        }
    }
}

void Board::draw() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (grid[i][j]) {
                DrawRectangle(j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, GRAY);
            }
        }
    }
}