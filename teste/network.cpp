#include "network.h"
#include <iostream>
#include <thread>
#include <cstring> // Para usar memset e strlen

NetworkManager::NetworkManager() : isServer(false), connected(false) {
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    serverSocket = INVALID_SOCKET;
    clientSocket = INVALID_SOCKET;
}

NetworkManager::~NetworkManager() {
    if (serverSocket != INVALID_SOCKET) closesocket(serverSocket);
    if (clientSocket != INVALID_SOCKET) closesocket(clientSocket);
    WSACleanup();
}

bool NetworkManager::startServer(unsigned short port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Erro ao criar socket do servidor." << std::endl;
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Erro ao associar o socket." << std::endl;
        return false;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Erro ao iniciar escuta no servidor." << std::endl;
        return false;
    }

    std::cout << "Servidor iniciado na porta " << port << ". Aguardando conexões..." << std::endl;
    isServer = true;
    return true;
}

bool NetworkManager::connectToServer(const std::string& ip, unsigned short port) {
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Erro ao criar socket do cliente." << std::endl;
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Erro ao conectar ao servidor." << std::endl;
        return false;
    }

    std::cout << "Conectado ao servidor " << ip << ":" << port << std::endl;
    connected = true;
    return true;
}

void NetworkManager::waitForClients() {
    if (!isServer) return;

    int clientAddrSize = sizeof(clientAddr);
    while (true) {
        SOCKET newClient = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
        if (newClient != INVALID_SOCKET) {
            std::cout << "Novo cliente conectado!" << std::endl;
            clientSockets.push_back(newClient);
        }
    }
}

void NetworkManager::sendMessage(const std::string& message) {
    if (isServer) {
        for (SOCKET socket : clientSockets) {
            send(socket, message.c_str(), message.length(), 0);
        }
    } else if (connected) {
        send(clientSocket, message.c_str(), message.length(), 0);
    }
}

std::string NetworkManager::receiveMessage() {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    int bytesReceived;

    if (isServer) {
        for (SOCKET socket : clientSockets) {
            bytesReceived = recv(socket, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) {
                return std::string(buffer, bytesReceived);
            }
        }
    } else if (connected) {
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            return std::string(buffer, bytesReceived);
        }
    }

    return "";
}

void NetworkManager::closeConnections() {
    if (isServer) {
        for (SOCKET socket : clientSockets) {
            closesocket(socket);
        }
        clientSockets.clear();
    }

    if (clientSocket != INVALID_SOCKET) closesocket(clientSocket);
    if (serverSocket != INVALID_SOCKET) closesocket(serverSocket);
    connected = false;
    isServer = false;
}
