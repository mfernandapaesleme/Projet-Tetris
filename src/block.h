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
  void Draw();
  void Move(int x, int y);

  std::vector<Position> GetCellPositions();

private:
  int cellSize;
  int rotationState;
  std::vector<Color> colors;
  int rowOffset;
  int columnOffset;

  //int x;
  //int y;
  //int color;
  //std::vector<std::vector<int>> shape;
  //std::vector<std::vector<int>> GetShape();
   // std::vector<Position> currentShape;
  //void Rotate();
  ///void MoveLeft();
  //void MoveRight();
  //void MoveDown();
  ///int GetX() const;
  //int GetY() const;
  //const std::vector<std::vector<int>>& GetShape() const;

};