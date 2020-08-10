#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "core/typedefs.hpp"
#include "SFML/Network/UdpSocket.hpp"
#include "SFML/Network/IpAddress.hpp"

enum EngineProtocolCode : uint64{
    Fail        = 0,
    Success     = 1,
    Connect     = 2,
    Disconnect  = 3,
    EngineCodesCount
};

struct NetworkEvent{
    uint64 code;
    byte data[28];
    NetworkEvent();
    NetworkEvent(enum EngineProtocolCode c);
    void clear();
};

struct Host{
    sf::IpAddress ip;
    sf::Uint16 port;
    Host();
    Host(const sf::IpAddress& i, sf::Uint16 p);
    std::string to_string()const;
};

sf::Uint64 htoi(const Host &host);
Host itoh(sf::Uint64);
#endif