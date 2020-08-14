#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "config/config.hpp"
#include "core/typedefs.hpp"
#include "SFML/Network/UdpSocket.hpp"
#include "SFML/Network/IpAddress.hpp"

namespace protocol{
    enum DatagramType : uint8{
        NullType    = 0,
        Event       = 1,
        Response    = 2,
        Request     = 3
    };

    enum RequestCode : uint8{
        NullRequest = 0,
        Connect     = 1,
        Disconnect  = 2
    };

    enum ResponseCode : uint8{
        NullResponse    = 0,
        Success         = 1,
        Fail            = 2
    };
    enum EventCode: uint8{
        NullEvent   = 0
    };

    struct Header{
        DatagramType type;
        union Code{
            RequestCode   request;
            ResponseCode   response;
            EventCode     event;
        }code;
    };

}; // end of protocol::

struct Datagram: public protocol::Header{
    byte data[DATAGRAM_DATA_SIZE];
    Datagram();
    Datagram(enum protocol::DatagramType type, Datagram::Code code);
    void clear();
};

struct Request: public protocol::Header{
    Request();
    Request(protocol::RequestCode c);
};
struct Response: public protocol::Header{
    Response();
    Response(protocol::ResponseCode c);
};

struct Event: public Datagram{
    Event(protocol::EventCode code);
    explicit Event(const Datagram &);

    void set_data(byte *data, std::size_t size);
    void clear_data();
};


struct Host{
    sf::IpAddress ip;
    sf::Uint16 port;
    Host();
    Host(const sf::IpAddress& i, sf::Uint16 p);
    std::string to_string()const;

    bool operator==(const Host &other)const;
    bool operator!=(const Host &other)const;
};

sf::Uint64 htoi(const Host &host);
Host itoh(sf::Uint64);
#endif