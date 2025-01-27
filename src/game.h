#pragma once
#include "grid.h"
#include "blocks.cpp"
#include "raylib.h"

class Game {

public:
  Game();
  ~Game();
  bool gameOver;
  int score;
  bool isSinglePlayer;
  bool isServer;

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

private:
  std::vector<Block> blocks;
  Block currentBlock;
  Block nextBlock;
  Grid grid;
};