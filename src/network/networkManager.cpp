/* #include "networkManager.hpp"
#include <iostream>

// Constructeur de la classe NetworkManager qui initialise les membres
NetworkManager::NetworkManager() : host(nullptr), peer(nullptr), state(NetworkState::DISCONNECTED) {}

NetworkManager::~NetworkManager() {
    shutdown();
}

// Initialisation de la bibliothèque ENet
bool NetworkManager::initialize() {
    if (enet_initialize() != 0) {
        std::cerr << "Failed to initialize ENet.\n";
        return false;
    }
    return true;
}

// Fermeture et nettoyage des ressources
void NetworkManager::shutdown() {
    if (host) enet_host_destroy(host);
    enet_deinitialize();
}

// Démarre un serveur ENet avec le port donné
bool NetworkManager::startServer(int port) {
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = port;

    host = enet_host_create(&address, 2, 2, 0, 0);
    if (!host) {
        std::cerr << "Failed to start server.\n";
        return false;
    }

    state = NetworkState::HOSTING;
    return true;
}


// Attend les connexions des clients sur le serveur
void NetworkManager::waitForClients() {
    if (!host) return;

    ENetEvent event;
    while (enet_host_service(host, &event, 1000) > 0) {
        if (event.type == ENET_EVENT_TYPE_CONNECT) {
            std::cout << "Client connected.\n";
        }
    }
}


// Connexion à un serveur en utilisant l'adresse et le port donnés
bool NetworkManager::connectToServer(const std::string& address, int port) {
    ENetAddress enetAddress;
    enet_address_set_host(&enetAddress, address.c_str());
    enetAddress.port = port;

    host = enet_host_create(nullptr, 1, 2, 0, 0);
    if (!host) {
        std::cerr << "Failed to create client host.\n";
        return false;
    }

    peer = enet_host_connect(host, &enetAddress, 2, 0);
    if (!peer) {
        std::cerr << "Failed to connect to server.\n";
        return false;
    }

    state = NetworkState::CONNECTING;
    return true;
}



// Diffuse l'état d'un joueur à tous les clients
void NetworkManager::broadcastPlayerState(const NetworkPlayer& player) {
    if (!host) return;

    ENetPacket* packet = enet_packet_create(&player, sizeof(player), ENET_PACKET_FLAG_RELIABLE);
    enet_host_broadcast(host, 0, packet);
    enet_host_flush(host);
}


// Envoie l'état du joueur à un client spécifique
void NetworkManager::sendPlayerState(const NetworkPlayer& player) {
    if (!peer) return;

    ENetPacket* packet = enet_packet_create(&player, sizeof(player), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(host);
}


// Réception des états des joueurs à partir du serveur
std::vector<NetworkPlayer> NetworkManager::receivePlayerStates() {
    std::vector<NetworkPlayer> players;

    if (!host) return players;

    ENetEvent event;
    while (enet_host_service(host, &event, 0) > 0) {
        if (event.type == ENET_EVENT_TYPE_RECEIVE) {
            NetworkPlayer player;
            memcpy(&player, event.packet->data, sizeof(player));
            players.push_back(player);
            enet_packet_destroy(event.packet);
        }
    }

    return players;
}

// Retourne l'état actuel du réseau
NetworkState NetworkManager::getState() const {
    return state;
}
 */