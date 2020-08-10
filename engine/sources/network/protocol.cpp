#include "network/protocol.hpp"
#include "string.h"
NetworkEvent::NetworkEvent(){
    clear();
}

NetworkEvent::NetworkEvent(enum EngineProtocolCode c){
    clear();
    code = c;
}

void NetworkEvent::clear(){
    memset(&code,0,sizeof(NetworkEvent));
}

Host::Host():
    ip(0u),port(0)
{}
Host::Host(const sf::IpAddress& i, sf::Uint16 p):
    ip(i),port(p)
{}

std::string Host::to_string()const{
    return ip.toString()+":"+std::to_string(port);
}


sf::Uint64 htoi(const Host &host){
    sf::Uint64 res = host.port;
    res <<= 48;
    res |= host.ip.toInteger();
    return res;
}
Host itoh(sf::Uint64 i){
    Host res;
    res.ip = sf::IpAddress(i);
    res.port = i>>48;
    return res;
}