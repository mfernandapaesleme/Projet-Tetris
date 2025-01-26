#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.hpp"

class Block {
public:
  Block(); // constructor
  int id;
  std::map<int, std::vector<Position>> cells;     // Une carte (map) qui associe un entier (état de la rotation) à un vecteur de positions représentant les cellules du bloc pour chaque état.
  void Draw(int offset_x, int offset_y);          // Fonction pour dessiner le bloc à l'écran avec un décalage.
  void Move(int x, int y);                        // Fonction pour déplacer le bloc selon les valeurs x et y.


 // Fonction pour obtenir les positions actuelles des cellules du bloc en tenant compte des décalages et de la rotation.
  std::vector<Position> GetCellPositions();

 // Fonction pour faire tourner le bloc (changer son état de rotation).
  void Rotate();

private:
  int cellSize;
  int rotationState;
  std::vector<Color> colors;            // Liste des couleurs associées aux cellules du bloc.
  int rowOffset;
  int columnOffset;
};