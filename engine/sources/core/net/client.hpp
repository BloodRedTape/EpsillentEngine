#ifndef CLIENT_H
#define CLIENT_H

#include "SFML/Network/IpAddress.hpp"
#include "SFML/Network/UdpSocket.hpp"

#include "core/net/protocol.hpp"

class Client{
private:
    Host server;
    sf::UdpSocket socket;
public:
    Client();
    void connect(const Host& server);

    void send(const Datagram &d);
    void send(const Event &e);
    void send(const Request &r);
    
    void disconnect();
};
#endif