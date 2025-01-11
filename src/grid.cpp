#include "grid.h"
#include "colors.hpp"
#include <iostream>

Grid::Grid() {
  numRows = 20;
  numCols = 10;
  cellSize = 30;
  Initialize();
  colors = GetCellColors();
}

void Grid::Initialize() {  // i = rows, j = columns
  for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            grid[i][j] = 0;
        }
    }
}

void Grid::Print() {
  for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void Grid::Draw() {
  for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            int cellValue = grid[i][j];
            Color cellColor = colors[cellValue];
            DrawRectangle((j * cellSize) + 1, (i * cellSize) + 1, cellSize - 1, cellSize - 1, cellColor);
        }
    }
}

int Grid::GetWidth() {
  return numCols;
}

int Grid::GetHeight() {
  return numRows;
}

int Grid::GetCell(int x, int y) {
  return grid[y][x];
}