#ifndef CLIENT_H
#define CLIENT_H

#include "SFML/Network/IpAddress.hpp"
#include "SFML/Network/UdpSocket.hpp"

#include "network/protocol.hpp"

class Client{
private:
    Host server;
    sf::UdpSocket socket;
public:
    Client();
    void connect(const Host& server);
    void send(const NetworkEvent &e);
    void disconnect();
};
#endif