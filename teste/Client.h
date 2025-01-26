#include <iostream>
#include <winsock2.h>
#include <raylib.h>
#include <thread>
#include <chrono>

class TetrisClient {
private:
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    char buffer[1024];  // Buffer para dados de comunicação

public:
    TetrisClient() : clientSocket(INVALID_SOCKET) {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    }

    ~TetrisClient() {
        if (clientSocket != INVALID_SOCKET) {
            closesocket(clientSocket);
        }
        WSACleanup();
    }

    bool connectToServer(const std::string& ipAddress) {
        clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Erro ao criar socket do cliente." << std::endl;
            return false;
        }

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(25564);

        // Usando inet_addr para converter o IP (IPv4) em formato numérico
        serverAddr.sin_addr.s_addr = inet_addr(ipAddress.c_str());

        if (serverAddr.sin_addr.s_addr == INADDR_NONE) {
            std::cerr << "Erro ao converter o endereço IP." << std::endl;
            return false;
        }

        if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Erro ao conectar ao servidor." << std::endl;
            return false;
        }

        std::cout << "Conectado ao servidor!" << std::endl;
        return true;
    }

    void receiveFromServer() {
        while (true) {
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived == SOCKET_ERROR) {
                std::cerr << "Erro ao receber dados do servidor." << std::endl;
                break;
            }
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';  // Adiciona terminador de string
                std::cout << "Mensagem do servidor: " << buffer << std::endl;
            }
        }
    }

    void sendToServer(const char* message) {
        send(clientSocket, message, strlen(message), 0);
    }

    void gameLoop() {
        // Configura o jogo com Raylib
        InitWindow(800, 600, "Tetris Multiplayer");
        SetTargetFPS(60);

        while (!WindowShouldClose()) {
            // Lógica do jogo aqui

            // Exemplo de envio de movimento do jogador
            sendToServer("Mover peça para a direita");

            // Receber estado do servidor
            receiveFromServer();

            // Desenhar o estado do jogo
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Jogo multiplayer de Tetris", 10, 10, 20, DARKGRAY);
            EndDrawing();

            // Aguarda um pouco para não sobrecarregar a rede
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        CloseWindow();
    }
};
