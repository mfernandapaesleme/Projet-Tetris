#define NOCURSOR
#include "game.h"
#include "raylib.h"
#include "./network/networkManager.hpp"
#include <string>
#include <random>
#include <iostream>

Game::Game() {
  grid = Grid();
  blocks = GetBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
  score = 0;
  NetworkManager networkManager;
  
   if (isServer) {
    if (!networkManager.startServer(25564)) {
      std::cout << "Erro ao iniciar o servidor!" << std::endl;
    }
    else {
      std::cout << "Servidor iniciado!" << std::endl;
      //networkManager.sendMessage("Estado do jogo");
    }
  } else {
    if (!networkManager.connectToServer("127.0.0.1", 25564)) { // Conecte ao servidor local para testes
      std::cout << "Erro ao conectar ao servidor!" << std::endl;
    }
    else {
      //std::string serverMessage = networkManager.receiveMessage();
      std::cout << "Conectado ao servidor!" << std::endl;
    }
  }
}

Game::~Game()
{
  //networkManager.closeConnections();

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

   /*  // Receber mensagem do outro jogador
    std::string message = networkManager.receiveMessage();
    if (!message.empty()) {
     std::cout << "Mensagem recebida: " << message << std::endl;
    // Enviar mensagem para o outro jogador
      std::string gameState = "Score:" + std::to_string(score);
      networkManager.sendMessage(gameState);
    } */
    
    currentBlock.Move(0, 1);
    if (CheckCollision()) {
        currentBlock.Move(0, -1);
        MergeBlock(); // Responsável por ativar Game Over
    }
}


void Game::Draw() {
  grid.Draw();
  currentBlock.Draw(0,0);
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