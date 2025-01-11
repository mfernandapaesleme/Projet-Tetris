#ifndef TETROMINO_H
#define TETROMINO_H

#include <vector>
using namespace std;

class Tetromino {
private:
    vector<vector<int>> shape;
    int x, y; // Position on the board

public:
    Tetromino(const vector<vector<int>>& initialShape, int startX, int startY);
    void rotate();
    void moveLeft();
    void moveRight();
    void moveDown();
    int getX() const;
    int getY() const;
    const vector<vector<int>>& getShape() const;
};

#endif // TETROMINO_H
