#include "networkmanager.hpp"
#include <enet/enet.h>
#include <iostream>
#include <stdexcept>

class NetworkManager::Impl {
public:
    Impl(int mode, const std::string& address, int port)
        : mode(mode), address(address), port(port), host(nullptr), peer(nullptr) {}

    ~Impl() {
        if (peer) enet_peer_disconnect(peer, 0);
        if (host) enet_host_destroy(host);
        enet_deinitialize();
    }

    void start() {
        if (enet_initialize() != 0) {
            throw std::runtime_error("Failed to initialize ENet.");
        }

        if (mode == 0) {
            ENetAddress enetAddress;
            enet_address_set_host(&enetAddress, address.c_str());
            enetAddress.port = port;

            host = enet_host_create(&enetAddress, 32, 2, 0, 0);
            if (!host) {
                throw std::runtime_error("Failed to create ENet server.");
            }
        } else if (mode == 1) {
            host = enet_host_create(nullptr, 1, 2, 0, 0);
            if (!host) {
                throw std::runtime_error("Failed to create ENet client.");
            }

            ENetAddress enetAddress;
            enet_address_set_host(&enetAddress, address.c_str());
            enetAddress.port = port;

            peer = enet_host_connect(host, &enetAddress, 2, 0);
            if (!peer) {
                throw std::runtime_error("Failed to create ENet peer.");
            }
        }
    }

    void send(const std::string& message) {
        if (mode == 0) {
            if (!host) throw std::runtime_error("Server not initialized.");
        } else if (!peer) {
            throw std::runtime_error("Client not connected to a server.");
        }

        ENetPacket* packet = enet_packet_create(message.c_str(),
                                                message.size() + 1,
                                                ENET_PACKET_FLAG_RELIABLE);
        if (mode == 0) {
            enet_host_broadcast(host, 0, packet);
        } else {
            enet_peer_send(peer, 0, packet);
        }
    }

    std::string receive() {
        if (!host) throw std::runtime_error("Host not initialized.");

        ENetEvent event;
        if (enet_host_service(host, &event, 1000) > 0) {
            if (event.type == ENET_EVENT_TYPE_RECEIVE) {
                std::string receivedMessage(reinterpret_cast<char*>(event.packet->data));
                enet_packet_destroy(event.packet);
                return receivedMessage;
            }
        }
        return {};
    }

private:
    int mode;
    std::string address;
    int port;
    ENetHost* host;
    ENetPeer* peer;
};

NetworkManager::NetworkManager(int mode, const std::string& address, int port)
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