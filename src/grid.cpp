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

// Initialise la grille avec des cellules vides (valeur 0)
void Grid::Initialize() {  // i = rows, j = columns
  for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            grid[i][j] = 0;
        }
    }
}

// Affiche la grille dans la console
void Grid::Print() {
  for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


// Dessine la grille à l'écran avec les couleurs correspondantes
void Grid::Draw() {
  for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            int cellValue = grid[i][j];
            Color cellColor = colors[cellValue];
            DrawRectangle((j * cellSize) + 1, (i * cellSize) + 1, cellSize - 1, cellSize - 1, cellColor);
        }
    }
}

// Retourne la largeur de la grille (en nombre de colonnes)
int Grid::GetWidth() {
  return numCols;
}

// Retourne la hauteur de la grille (en nombre de lignes)
int Grid::GetHeight() {
  return numRows;
}

// Retourne la valeur de la cellule à la position (x, y)
int Grid::GetCell(int x, int y) {
  return grid[y][x];
}

// Vérifie si une cellule est vide (valeur 0)
bool Grid::IsCellEmpty(int x, int y)
{
    if (grid[x][y] == 0)
    {
        return true;
    }
    return false;
}


// Supprime les lignes complètes et déplace les autres lignes vers le bas
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

// Vérifie si une ligne est pleine (aucune cellule vide)
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


// Efface une ligne complète (remplace les cellules par des 0)
void Grid::ClearRow(int x)
{
    for (int y = 0; y < numCols; y++)
    {
        grid[x][y] = 0;
    }
}

// Déplace une ligne vers le bas après qu'une ligne ait été effacée
void Grid::MoveRowDown(int x, int numRows)
{
    for (int y = 0; y < numCols; y++)
    {
        grid[x + numRows][y] = grid[x][y];
        grid[x][y] = 0;
    }
}