#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.hpp"

class Block {
public:
  Block(); // constructor
  int id;
  std::map<int, std::vector<Position>> cells;
  void Draw(int offset_x, int offset_y);
  void Move(int x, int y);

  std::vector<Position> GetCellPositions();

  void Rotate();

private:
  int cellSize;
  int rotationState;
  std::vector<Color> colors;
  int rowOffset;
  int columnOffset;
};