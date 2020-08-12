#ifndef CLIENT_H
#define CLIENT_H

#include "SFML/Network/IpAddress.hpp"
#include "SFML/Network/UdpSocket.hpp"

#include "core/net/protocol.hpp"

class Client{
protected:
    Host server;
    sf::UdpSocket socket;
    bool m_is_connected;
public:
    Client();
    void connect(const Host& server);

    void send(const Datagram &d);
    void send(const Event &e);
    void send(const Request &r);
    
    bool is_connected();

    void disconnect();
};
#endif