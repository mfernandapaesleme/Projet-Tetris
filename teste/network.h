#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

class NetworkManager {
private:
    WSADATA wsaData;                 // Dados do Windows Sockets
    SOCKET serverSocket;             // Socket do servidor
    SOCKET clientSocket;             // Socket do cliente
    sockaddr_in clientAddr;          // Endereço do cliente
    std::vector<SOCKET> clientSockets; // Lista de sockets para clientes conectados
    bool isServer;                   // Flag para verificar se é servidor
    bool connected;                  // Flag para verificar se está conectado

public:
    NetworkManager();
    ~NetworkManager();

    // Inicialização do servidor
    bool startServer(unsigned short port);

    // Conexão a um servidor existente
    bool connectToServer(const std::string& ip, unsigned short port);

    void waitForClients(); // Espera por conexões de clientes (modo servidor) 

    // Envia uma mensagem para o cliente ou servidor
    void sendMessage(const std::string& message);

    // Recebe uma mensagem do cliente ou servidor
    std::string receiveMessage();

    // Fecha as conexões abertas
    void closeConnections();

    // Getters para verificar estado
    bool isServerMode() const { return isServer; }
    bool isConnected() const { return connected; }
};

#endif // NETWO
