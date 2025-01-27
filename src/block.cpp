#include "grid.h"
#include "block.h"
#include <iostream>



// Constructeur de la classe Block, initialise les attributs par défaut.
Block::Block(){
  cellSize = 30;
  rotationState = 0;
  colors = GetCellColors();
  id = 0;
  rowOffset = 0;
  columnOffset = 0;
}


// Méthode pour dessiner le bloc sur l'écran.
void Block::Draw(int offset_x, int offset_y) {
  std::vector<Position> currentShape = GetCellPositions();
  for (Position item : currentShape) {
    DrawRectangle((item.x * cellSize + offset_x) + 1, (item.y * cellSize + offset_y) + 1, cellSize - 1, cellSize - 1, colors[id]);
  }
}

// Méthode pour déplacer le bloc en ajustant les décalages de ligne et de colonne.
void Block::Move(int x, int y) {
  rowOffset += x;
  columnOffset += y;
}


// Méthode pour obtenir les positions des cellules après application des transformations.
std::vector<Position> Block::GetCellPositions() {
  std::vector<Position> currentShape = cells[rotationState];
  std::vector<Position> movedShape;  
  for(Position item : currentShape) {
    movedShape.push_back(Position(item.x + rowOffset, item.y + columnOffset));
  }
  return movedShape;
}


// Méthode pour faire pivoter le bloc.
void Block::Rotate()
{
    rotationState++;
    if (rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
}
