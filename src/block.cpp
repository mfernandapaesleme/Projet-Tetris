#include "grid.h"
#include "block.h"
#include <iostream>

Block::Block(){
  cellSize = 30;
  rotationState = 0;
  colors = GetCellColors();
  id = 0;
  rowOffset = 0;
  columnOffset = 0;
}

void Block::Draw() {
  std::vector<Position> currentShape = GetCellPositions();
  for (Position item : currentShape) {
    DrawRectangle((item.x * cellSize) + 1, (item.y * cellSize) + 1, cellSize - 1, cellSize - 1, colors[id]);
  }
}

void Block::Move(int x, int y) {
  rowOffset += x;
  columnOffset += y;
}

std::vector<Position> Block::GetCellPositions() {
  std::vector<Position> currentShape = cells[rotationState];
  std::vector<Position> movedShape;  
  for(Position item : currentShape) {
    movedShape.push_back(Position(item.x + rowOffset, item.y + columnOffset));
  }
  return movedShape;
}

void Block::Rotate()
{
    rotationState++;
    if (rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
}
