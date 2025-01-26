#include "grid.h"
#include "block.h"
#include <iostream>

// Constructeur de la classe Block
Block::Block(){
  cellSize = 30;                    // Taille de chaque cellule du bloc
  rotationState = 0;                // État de la rotation initial (0)
  colors = GetCellColors();         // Récupération des couleurs des cellules du bloc
  id = 0;                           // Identifiant du bloc (initialisé à 0)
  rowOffset = 0;                    // Décalage initial des lignes et colonnes (0)
  columnOffset = 0;
}


// Fonction pour dessiner le bloc
void Block::Draw(int offset_x, int offset_y) {                   // Récupérer les positions actuelles des cellules du bloc
  std::vector<Position> currentShape = GetCellPositions();       // Dessiner chaque cellule du bloc avec la couleur correspondante
  for (Position item : currentShape) {                           // Dessin du rectangle représentant la cellule du bloc
    DrawRectangle((item.x * cellSize + offset_x) + 1, (item.y * cellSize + offset_y) + 1, cellSize - 1, cellSize - 1, colors[id]);
  }
}


// Fonction pour déplacer le bloc
void Block::Move(int x, int y) {
  rowOffset += x;                       // Modifier les offsets pour déplacer le bloc
  columnOffset += y;
}


// Fonction pour obtenir les positions des cellules du bloc en prenant en compte le décalage
std::vector<Position> Block::GetCellPositions() {
  std::vector<Position> currentShape = cells[rotationState];                       // Récupérer la forme actuelle du bloc (selon l'état de la rotation)
  std::vector<Position> movedShape;                                                // Appliquer les offsets aux positions des cellules
  for(Position item : currentShape) {
    movedShape.push_back(Position(item.x + rowOffset, item.y + columnOffset));
  }
  return movedShape;                                                               // Retourner les positions modifiées des cellules
}


// Fonction pour faire pivoter le bloc (rotation)
void Block::Rotate()
{
    rotationState++;                                       // Augmenter l'état de la rotation
    if (rotationState == (int)cells.size())                // Si l'état de la rotation dépasse le nombre total de formes, réinitialiser à 0
    {
        rotationState = 0;
    }
}
