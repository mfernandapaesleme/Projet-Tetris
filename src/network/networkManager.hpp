#ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include <string>

class NetworkManager {
public:
    enum class Mode { Server, Client };

    NetworkManager(Mode mode, const std::string& address, int port);
    ~NetworkManager();

    void start();
    void send(const std::string& message);
    std::string receive();

private:
    class Impl;
    Impl* impl; // PImpl idiom to hide implementation details
};

#endif // NETWORK_MANAGER_HPP