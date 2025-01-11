#include "game.h"
#include <random>

Game::Game() {
  grid = Grid();
  blocks = GetBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();

  /* blocks.push_back(LBlock());
  blocks.push_back(JBlock());
  blocks.push_back(IBlock());
  blocks.push_back(OBlock());
  blocks.push_back(SBlock()); */
}

Block Game::GetRandomBlock() {
  /* std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, blocks.size() - 1);
  return blocks[dis(gen)]; */

  if(blocks.empty()) {
    blocks = GetBlocks();
  }

  int randomIndex = rand() % blocks.size();
  Block randomBlock = blocks[randomIndex];
  blocks.erase(blocks.begin() + randomIndex);
  return randomBlock;
}

std::vector<Block> Game::GetBlocks() {
  return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

/* void Game::Update() {
  currentBlock.Move(1, 0);
  if(CheckCollision()) {
    currentBlock.Move(-1, 0);
    MergeBlock();
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();
  }
} */

void Game::Draw() {
  grid.Draw();
  currentBlock.Draw();
  //nextBlock.Draw();
}