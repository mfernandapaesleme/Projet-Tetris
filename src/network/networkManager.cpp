#include "networkManager.hpp"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

// Definir o número de sockets
#define DEFAULT_PORT 4545

#pragma comment(lib, "ws2_32.lib")  // Necessário para Winsock

// A implementação privada (PImpl)
class NetworkManager:: Impl {
public:
    Impl(Mode mode, const std::string& address, int port)
        : mode(mode), address(address), port(port), serverSocket(INVALID_SOCKET) {}

    ~Impl() {
        closesocket(serverSocket);
        WSACleanup();
    }

    void start() {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Winsock initialization failed." << std::endl;
            return;
        }

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

        if (mode == Mode::Server) {
            // Server side
            serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (serverSocket == INVALID_SOCKET) {
                std::cerr << "Socket creation failed!" << std::endl;
                return;
            }

            addr.sin_addr.s_addr = INADDR_ANY;

            if (bind(serverSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
                std::cerr << "Binding failed!" << std::endl;
                return;
            }

            if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
                std::cerr << "Listen failed!" << std::endl;
                return;
            }

            std::cout << "Server started on port " << port << std::endl;
        } else {
            // Client side
            serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (serverSocket == INVALID_SOCKET) {
                std::cerr << "Socket creation failed!" << std::endl;
                return;
            }

            inet_pton(AF_INET, address.c_str(), &addr.sin_addr);

            if (connect(serverSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
                std::cerr << "Connection failed!" << std::endl;
                return;
            }

            std::cout << "Connected to " << address << ":" << port << std::endl;
        }
    }

    void send(const std::string& message) {
        if (serverSocket == INVALID_SOCKET) return;

        if (::send(serverSocket, message.c_str(), message.length(), 0) == SOCKET_ERROR) {
            std::cerr << "Send failed!" << std::endl;
        }
    }

    std::string receive() {
        if (serverSocket == INVALID_SOCKET) return "";

        char buffer[1024];
        int bytesReceived = recv(serverSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Receive failed!" << std::endl;
            return "";
        }

        return std::string(buffer, bytesReceived);
    }

private:
    Mode mode;
    std::string address;
    int port;
    SOCKET serverSocket;  // Renomeado para evitar conflito
};

// Construtor e destruidor da classe NetworkManager
NetworkManager::NetworkManager(Mode mode, const std::string& address, int port)
    : impl(new Impl(mode, address, port)) {}

NetworkManager::~NetworkManager() {
    delete impl;
}

void NetworkManager::start() {
    impl->start();
}

void NetworkManager::send(const std::string& message) {
    impl->send(message);
}

std::string NetworkManager::receive() {
    return impl->receive();
}   