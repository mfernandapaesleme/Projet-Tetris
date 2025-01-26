#include "game.h"
#include "raylib.h"
#include <string>
#include <random>

Game::Game() {
  grid = Grid();
  blocks = GetBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
  score = 0;
}

Game::~Game()
{
  /*   UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice(); */
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
    if (gameOver) {
        return; // Não continuar atualizando o jogo se estiver no estado "Game Over"
    }

    currentBlock.Move(0, 1);
    if (CheckCollision()) {
        currentBlock.Move(0, -1);
        MergeBlock(); // Responsável por ativar Game Over
    }
}


void Game::Draw() {
  grid.Draw();
  currentBlock.Draw(0,0);
  const Color lightBlue = {59, 85, 162, 255};
  Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

  DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
  DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
  DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
  char scoreText[10];
  sprintf(scoreText, "%d", score);
  Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
  DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
  DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
  nextBlock.Draw(270, 270);
    if(gameOver) {
        DrawTextEx(font, "GAME OVER", {50, 300}, 64, 2, RED);
        DrawTextEx(font, "Press R to restart", {50, 400}, 32, 2, WHITE);
    }



  nextBlock.Draw(270, 270);
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

void Game::MergeBlock() {
    std::vector<Position> currentShape = currentBlock.GetCellPositions();
    for (Position item : currentShape) {
        grid.grid[item.y][item.x] = currentBlock.id;
    }

    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0) {
        // Atualizar a pontuação
        UpdateScore(rowsCleared, 0);
    }

    // Preparar próximo bloco
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();

    // Checar se o próximo bloco cabe
    if (!BlockFits()) {
        gameOver = true; // Ativar Game Over
    }
}

bool Game::BlockFits() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        // Verificar se está fora do grid ou se está colidindo com outro bloco
        if (item.x < 0 || item.x >= grid.GetWidth() || 
            item.y >= grid.GetHeight() || 
            (item.y >= 0 && grid.GetCell(item.x, item.y) != 0)) {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
    gameOver = false; // Garantir que o estado do jogo seja reiniciado
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }

    score += moveDownPoints;
}