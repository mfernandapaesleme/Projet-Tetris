#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <netinet/in.h>

class Server {
private:
    int serverSocket;
    int port;
    std::vector<int> clients;
    std::mutex clientsMutex;
    std::string gameState;

    void HandleClient(int clientSocket);
    void BroadcastGameState();

public:
    Server(int port);
    ~Server();
    void Start();
};

#endif
