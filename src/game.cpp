#include "game.h"
#include <random>

Game::Game() {
  grid = Grid();
  blocks = GetBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
}

Block Game::GetRandomBlock() {
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

void Game::Update() {
  currentBlock.Move(0, 1);
  if(CheckCollision()) {
    currentBlock.Move(0, -1);
    MergeBlock();
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();
  }
}

void Game::Draw() {
  grid.Draw();
  currentBlock.Draw();
  //nextBlock.Draw();
}

bool Game::CheckCollision() {
  std::vector<Position> currentShape = currentBlock.GetCellPositions();
  for(Position item : currentShape) {
    if(item.x < 0 || item.x >= grid.GetWidth() || item.y >= grid.GetHeight() || grid.GetCell(item.x, item.y) != 0) {
      return true;
    }
  }
  return false;
}

void Game::HandleInput() {
  if(IsKeyPressed(KEY_LEFT)) {
    currentBlock.Move(-1, 0);
    if(CheckCollision()) {
      currentBlock.Move(1, 0);
    }
  }
  if(IsKeyPressed(KEY_RIGHT)) {
    currentBlock.Move(1, 0);
    if(CheckCollision()) {
      currentBlock.Move(-1, 0);
    }
  }
  if(IsKeyPressed(KEY_DOWN)) {
    currentBlock.Move(0, 1);
    if(CheckCollision()) {
      currentBlock.Move(0, -1);
      MergeBlock();
      currentBlock = nextBlock;
      nextBlock = GetRandomBlock();
    }
  }
  if(IsKeyPressed(KEY_UP)) {
    currentBlock.Rotate();
    if(CheckCollision()) {
      currentBlock.Rotate();
    }
  }
}

void Game::MergeBlock(){
  std::vector<Position> currentShape = currentBlock.GetCellPositions();
  for(Position item : currentShape) {
    grid.grid[item.y][item.x] = currentBlock.id;
  }
  currentBlock = nextBlock;
   if (BlockFits() == false)
    {
        //gameOver = true;
    }
  nextBlock = GetRandomBlock();

}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (CheckCollision() == false)
        {
            return false;
        }
    }
    return true;
}
