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

    void send(const void *data, std::size_t size);
    
    bool is_connected();

    void disconnect();
};
#endif