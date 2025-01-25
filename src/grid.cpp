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

bool Grid::IsCellEmpty(int x, int y)
{
    if (grid[x][y] == 0)
    {
        return true;
    }
    return false;
}


int Grid::ClearFullRows()
{
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--)
    {
        if (IsRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if (completed > 0)
        {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::IsRowFull(int x)
{
    for (int y = 0; y < numCols; y++)
    {
        if (grid[x][y] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int x)
{
    for (int y = 0; y < numCols; y++)
    {
        grid[x][y] = 0;
    }
}
void Grid::MoveRowDown(int x, int numRows)
{
    for (int y = 0; y < numCols; y++)
    {
        grid[x + numRows][y] = grid[x][y];
        grid[x][y] = 0;
    }
}