#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game {

public:
  Game();
  ~Game();
  bool gameOver;
  int score;

  Block GetRandomBlock();
  std::vector<Block> GetBlocks();
  void Update();
  void Draw();
  bool CheckCollision();
  void HandleInput();
  void MergeBlock();
  bool BlockFits();
  void Reset();
  void UpdateScore(int linesCleared, int moveDownPoints);
  Grid grid;

private:
  std::vector<Block> blocks;
  Block currentBlock;
  Block nextBlock;
};