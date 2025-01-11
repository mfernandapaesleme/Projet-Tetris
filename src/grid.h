#pragma once
#include <vector>
#include <raylib.h>

class Grid {
public:
  Grid(); // constructor
  int grid[20][10] = {0}; // 20 rows, 10 columns
  void Initialize();
  void Print();
  void Draw();
  int GetWidth();
  int GetHeight();
  int GetCell(int x, int y);

private:
  int numRows;
  int numCols;
  int cellSize;
  std::vector<Color> colors;
};