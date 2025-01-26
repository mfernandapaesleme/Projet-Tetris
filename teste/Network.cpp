#include <iostream>
#include <winsock2.h>
#include <raylib.h>
#include <thread>
#include <chrono>

#pragma comment(lib, "ws2_32.lib")

class NetworkManager {
private:
    SOCKET socket;             // Socket para comunicação
    SOCKET listener;           // Socket para o servidor
    sockaddr_in serverAddr;    // Endereço do servidor
    sockaddr_in clientAddr;    // Endereço do cliente
    char buffer[1024];         // Buffer para comunicação
    unsigned short serverPort = 25564;
    WSADATA wsaData;           // Estrutura de dados para a inicialização da Winsock
    bool isServer = false;

public:
    NetworkManager() : socket(INVALID_SOCKET), listener(INVALID_SOCKET) {
        // Inicialização da Winsock
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Falha na inicialização da Winsock." << std::endl;
            exit(1);
        }
    }

    ~NetworkManager() {
        // Fecha o socket e a Winsock
        if (socket != INVALID_SOCKET) {
            closesocket(socket);
        }
        if (listener != INVALID_SOCKET) {
            closesocket(listener);
        }
        WSACleanup();
    }

    int listen() {
        listener = ::socket(AF_INET, SOCK_STREAM, 0);
        if (listener == INVALID_SOCKET) {
            std::cerr << "Erro ao criar o socket do servidor." << std::endl;
            return -1;
        }

        // Configura o endereço do servidor
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(listener, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Erro ao vincular o socket do servidor." << std::endl;
            return -1;
        }

        // Aguarda conexões
        if (listen(listener, SOMAXCONN) == SOCKET_ERROR) {
            std::cerr << "Erro ao escutar no socket." << std::endl;
            return -1;
        }

        std::cout << "Servidor iniciado, aguardando conexões..." << std::endl;
        return 0;
    }

    int accept() {
        int clientSize = sizeof(clientAddr);
        socket = ::accept(listener, (sockaddr*)&clientAddr, &clientSize);
        if (socket == INVALID_SOCKET) {
            std::cerr << "Erro ao aceitar conexão." << std::endl;
            return -1;
        }

        std::cout << "Conexão aceita do cliente." << std::endl;
        isServer = false;
        return 0;
    }

    int connectToServer(const std::string& ipAddress) {
        socket = ::socket(AF_INET, SOCK_STREAM, 0);
        if (socket == INVALID_SOCKET) {
            std::cerr << "Erro ao criar o socket do cliente." << std::endl;
            return -1;
        }

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort);
        serverAddr.sin_addr.s_addr = inet_addr(ipAddress.c_str());

        if (connect(socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Erro ao conectar ao servidor." << std::endl;
            return -1;
        }

        std::cout << "Conectado ao servidor." << std::endl;
        return 0;
    }

    int send(const char* message) {
        int bytesSent = ::send(socket, message, strlen(message), 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "Erro ao enviar mensagem." << std::endl;
            return -1;
        }
        return bytesSent;
    }

    int receive() {
        int bytesReceived = recv(socket, buffer, sizeof(buffer), 0);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Erro ao receber mensagem." << std::endl;
            return -1;
        }
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';  // Adiciona terminador de string
            std::cout << "Mensagem recebida: " << buffer << std::endl;
        }
        return bytesReceived;
    }

    bool isServerMode() const {
        return isServer;
    }

    void disconnect() {
        closesocket(socket);
        if (listener != INVALID_SOCKET) {
            closesocket(listener);
        }
        std::cout << "Desconectado." << std::endl;
    }
};

class TetrisServer {
private:
    NetworkManager networkManager;

public:
    TetrisServer() {
        // Inicializa o servidor
        if (networkManager.listen() != 0) {
            std::cerr << "Falha ao iniciar o servidor." << std::endl;
            exit(1);
        }
    }

    void run() {
        while (true) {
            networkManager.accept();  // Aguarda e aceita a conexão do cliente

            // Loop de comunicação
            while (true) {
                networkManager.receive();
                // Aqui você pode implementar a lógica do jogo, como mover peças ou enviar o estado
                networkManager.send("Comando para mover peça para a direita");

                // Simula o recebimento de comandos do cliente a cada 1 segundo
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }
};

class TetrisClient {
private:
    NetworkManager networkManager;

public:
    TetrisClient() {}

    void connectToServer(const std::string& ipAddress) {
        if (networkManager.connectToServer(ipAddress) != 0) {
            std::cerr << "Falha ao conectar-se ao servidor." << std::endl;
            exit(1);
        }
    }

    void run() {
        while (true) {
            networkManager.receive();
            // Aqui você pode processar as mensagens do servidor
            networkManager.send("Comando para mover peça para baixo");

            // Simula o envio de comandos do cliente a cada 1 segundo
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

// Função principal do servidor
void runServer() {
    TetrisServer server;
    server.run();
}

// Função principal do cliente
void runClient() {
    TetrisClient client;
    client.connectToServer("127.0.0.1");  // IP do servidor
    client.run();
}

int main() {
    const bool isServer = true; // Modifique conforme necessário

    if (isServer) {
        runServer();
    } else {
        runClient();
    }

    return 0;
}
