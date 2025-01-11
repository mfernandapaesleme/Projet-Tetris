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

private:
  int numRows;
  int numCols;
  int cellSize;
  std::vector<Color> colors;
};