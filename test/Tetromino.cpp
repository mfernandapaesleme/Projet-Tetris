#include "Tetromino.h"

Tetromino::Tetromino(const vector<vector<int>>& initialShape, int startX, int startY)
    : shape(initialShape), x(startX), y(startY) {}

void Tetromino::rotate() {
    int n = shape.size();
    vector<vector<int>> rotated(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rotated[j][n - 1 - i] = shape[i][j];
        }
    }
    shape = rotated;
}

void Tetromino::moveLeft() { x--; }
void Tetromino::moveRight() { x++; }
void Tetromino::moveDown() { y++; }

int Tetromino::getX() const { return x; }
int Tetromino::getY() const { return y; }
const vector<vector<int>>& Tetromino::getShape() const { return shape; }