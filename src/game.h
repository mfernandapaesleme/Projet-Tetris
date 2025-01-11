#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game {

public:
  Game();
  Block GetRandomBlock();
  std::vector<Block> GetBlocks();
  void Update();
  void Draw();
  bool CheckCollision();
  void HandleInput();
  void MergeBlock();
  bool BlockFits();
  Grid grid;

private:
  std::vector<Block> blocks;
  Block currentBlock;
  Block nextBlock;
};