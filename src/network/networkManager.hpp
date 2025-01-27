/* #ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include <enet/enet.h>
#include <vector>
#include <string>

enum class NetworkState {
    DISCONNECTED,
    CONNECTING,
    CONNECTED,
    HOSTING
};

struct NetworkPlayer {
    int id;
    int x, y; // Posição do jogador ou da peça
};

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();

    bool initialize();
    void shutdown();
    bool isServer;

    // Servidor
    bool startServer(int port);
    void waitForClients();
    void broadcastPlayerState(const NetworkPlayer& player);

    // Cliente
    bool connectToServer(const std::string& address, int port);
    void sendPlayerState(const NetworkPlayer& player);
    std::vector<NetworkPlayer> receivePlayerStates();

    // Mensagens   
    void sendMessage(const std::string& message);
    std::string receiveMessage();

    NetworkState getState() const;

private:
    ENetHost* host;
    ENetPeer* peer;
    NetworkState state;
};

#endif // NETWORK_MANAGER_HPP */