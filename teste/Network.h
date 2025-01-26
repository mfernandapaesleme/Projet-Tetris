#include <iostream>
#include <vector>
#include <winsock2.h>
#include <raylib.h>
#include <thread>
#include <chrono>

class TetrisServer {
private:
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    unsigned short serverPort;
    bool gameRunning;
    char buffer[1024];  // Buffer para dados de comunicação
    std::vector<SOCKET> clientSockets; // Múltiplos jogadores

public:
    TetrisServer() : serverPort(25564), gameRunning(false) {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        serverSocket = INVALID_SOCKET;
        clientSocket = INVALID_SOCKET;
    }

    ~TetrisServer() {
        if (serverSocket != INVALID_SOCKET) {
            closesocket(serverSocket);
        }
        if (clientSocket != INVALID_SOCKET) {
            closesocket(clientSocket);
        }
        WSACleanup();
    }

    bool startServer() {
        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (serverSocket == INVALID_SOCKET) {
            std::cerr << "Erro ao criar socket do servidor." << std::endl;
            return false;
        }

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Erro ao associar o socket." << std::endl;
            return false;
        }

        if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
            std::cerr << "Erro ao iniciar escuta." << std::endl;
            return false;
        }

        std::cout << "Servidor iniciado, aguardando conexões..." << std::endl;
        return true;
    }

    void waitForClients() {
        int clientAddrSize = sizeof(clientAddr);
        while (gameRunning) {
            clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
            if (clientSocket != INVALID_SOCKET) {
                std::cout << "Novo cliente conectado!" << std::endl;
                clientSockets.push_back(clientSocket);
            }
        }
    }

    void sendToAllClients(const char* message) {
        for (SOCKET socket : clientSockets) {
            send(socket, message, strlen(message), 0);
        }
    }

    void gameLoop() {
        while (gameRunning) {
            // Lógica do jogo vai aqui, exemplo: enviando estado do jogo
            sendToAllClients("Novo estado do jogo");

            // Aguarda um pouco para não sobrecarregar o servidor
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void stop() {
        gameRunning = false;
    }
};
