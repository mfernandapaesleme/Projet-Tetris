#include "game.h"
#include "raylib.h"
#include <string>
#include <random>
#include <iostream>


// Constructeur de la classe Game.
Game::Game() {
  grid = Grid();
  blocks = GetBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
  score = 0;
  }


// Destructeur de la classe Game.
Game::~Game()
{
}


// Méthode pour obtenir un bloc aléatoire parmi ceux disponibles.
Block Game::GetRandomBlock() {
  if(blocks.empty()) {
    blocks = GetBlocks();
  }

  int randomIndex = rand() % blocks.size();
  Block randomBlock = blocks[randomIndex];
  blocks.erase(blocks.begin() + randomIndex);
  return randomBlock;
}


// Méthode pour créer la liste initiale des blocs disponibles.
std::vector<Block> Game::GetBlocks() {
  return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

// Mise à jour de l'état du jeu.
void Game::Update() {
    if (gameOver) {
        return; // Não continuar atualizando o jogo se estiver no estado "Game Over"
    }
    
    currentBlock.Move(0, 1);
    if (CheckCollision()) {
        currentBlock.Move(0, -1);
        MergeBlock(); // Responsável por ativar Game Over
    }
}

// Dessin de l'état actuel du jeu.
void Game::Draw() {
  grid.Draw();
  currentBlock.Draw(0,0);
  nextBlock.Draw(270, 270);
}

// Vérifie s'il y a une collision entre le bloc et les limites ou autres blocs.
bool Game::CheckCollision() {   
  std::vector<Position> currentShape = currentBlock.GetCellPositions();
  for(Position item : currentShape) {
    if(item.x < 0 || item.x >= grid.GetWidth() || item.y >= grid.GetHeight() || grid.GetCell(item.x, item.y) != 0) {
      return true;
    }
  }
  return false;
}


// Gestion des entrées clavier.
void Game::HandleInput() {
  if((IsKeyPressed(KEY_R)) || (gameOver && IsKeyPressed(KEY_ENTER))) { 
    gameOver = false;
    Reset();
  }
  if(!gameOver) {
    if(IsKeyPressed(KEY_LEFT)) {
      currentBlock.Move(-1, 0);
      if(CheckCollision() || BlockFits() == false) {
        currentBlock.Move(1, 0);
      }
    }
    if(IsKeyPressed(KEY_RIGHT)) {
      currentBlock.Move(1, 0);
      if(CheckCollision() || BlockFits() == false) {
        currentBlock.Move(-1, 0);
      }
    }
    if(IsKeyPressed(KEY_DOWN)) {
      currentBlock.Move(0, 1);
      if(CheckCollision() || BlockFits() == false) {
        currentBlock.Move(0, -1);
        MergeBlock();
        UpdateScore(0, 1);
        currentBlock = nextBlock;
        nextBlock = GetRandomBlock();
      }
    }
    if(IsKeyPressed(KEY_UP)) {
      currentBlock.Rotate();
      if(CheckCollision() || BlockFits() == false) {
        currentBlock.Rotate();
      }
    }
  }
}


// Fusionne le bloc actuel dans la grille et vérifie les lignes complètes.
void Game::MergeBlock() {
    std::vector<Position> currentShape = currentBlock.GetCellPositions();
    for (Position item : currentShape) {
        grid.grid[item.y][item.x] = currentBlock.id;
    }

    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0) {
       // Mettre à jour le score
        UpdateScore(rowsCleared, 0);
    }

    // Préparer le bloc suivant
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();

    // Vérifiez si le bloc suivant convient
    if (!BlockFits()) {
        gameOver = true; // Activer Game Over
    }
}

bool Game::BlockFits() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        // Vérifiez s'il est hors grille ou s'il entre en collision avec un autre bloc
        if (item.x < 0 || item.x >= grid.GetWidth() || 
            item.y >= grid.GetHeight() || 
            (item.y >= 0 && grid.GetCell(item.x, item.y) != 0)) {
            return false;
        }
    }
    return true;
}

// Réinitialise l'état du jeu.
void Game::Reset()
{
    grid.Initialize();
    blocks = GetBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
    gameOver = false; // Assurez que l'état du jeu est réinitialisé
}


// Met à jour le score en fonction des lignes effacées et des points de déplacement.
void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score += 40;
        break;
    case 2:
        score += 100;
        break;
    case 3:
        score += 300;
        break;
    case 4:
        score += 1200;
        break;
    default:
        break;
    }

    score += moveDownPoints;
}