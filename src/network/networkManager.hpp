/* #ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include <enet/enet.h>
#include <vector>
#include <string>


// Enumération des différents états du réseau
enum class NetworkState {
    DISCONNECTED,
    CONNECTING,
    CONNECTED,
    HOSTING
};


// Structure représentant un joueur ou une pièce dans le réseau
struct NetworkPlayer {
    int id;
    int x, y; // Posição do jogador ou da peça
};


// Classe principale pour gérer les opérations réseau
class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();

    // Initialisation et fermeture de la bibliothèque ENet
    bool initialize();
    void shutdown();
    bool isServer;

    // Fonctions pour le serveur
    bool startServer(int port);
    void waitForClients();
    void broadcastPlayerState(const NetworkPlayer& player);

    // Fonctions pour le client
    bool connectToServer(const std::string& address, int port);
    void sendPlayerState(const NetworkPlayer& player);
    std::vector<NetworkPlayer> receivePlayerStates();

    // Envoi et réception de messages   
    void sendMessage(const std::string& message);
    std::string receiveMessage();

    // Récupère l'état actuel du réseau
    NetworkState getState() const;

private:
    ENetHost* host;         // Hôte ENet (serveur ou client)
    ENetPeer* peer;         // Pair ENet pour les connexions client-serveur
    NetworkState state;
};

#endif // NETWORK_MANAGER_HPP */