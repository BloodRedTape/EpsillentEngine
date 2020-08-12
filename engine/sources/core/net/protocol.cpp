#include "core/net/protocol.hpp"
#include "string.h"
#include "utils/debug.hpp"
/*
NetworkEvent::NetworkEvent(){
    clear();
}

NetworkEvent::NetworkEvent(enum protocol::Code c){
    clear();
    code = c;
}

void NetworkEvent::clear(){
    memset(&code,0,sizeof(NetworkEvent));
}
*/
Datagram::Datagram()
{
    clear();
}
Datagram::Datagram(enum protocol::DatagramType t, Datagram::Code c)
{
    clear();
    type = t;
    code = c;
}
void Datagram::clear(){
    memset(this,0,sizeof(Datagram));
}
Request::Request(){
    type = protocol::DatagramType::Request;
    code.request = protocol::RequestCode::NullRequest;
}
Request::Request(protocol::RequestCode c){
    type = protocol::DatagramType::Request;
    code.request = c;
}
Response::Response(){
    type = protocol::DatagramType::Response;
    code.response = protocol::ResponseCode::NullResponse;
}
Response::Response(protocol::ResponseCode c){
    type = protocol::DatagramType::Response;
    code.response = c;
}


Event::Event(protocol::EventCode c){
    type = protocol::DatagramType::Event;
    code.event = c;
}
Event::Event(const Datagram &datagram){
    ASSERT_ERROR(datagram.type == protocol::DatagramType::Event, "can't convert non-event Datagram to an Event");
    memcpy(this,&datagram,sizeof(Datagram));
}
void Event::set_data(byte *d, std::size_t size){
    ASSERT_ERROR(size <= DATAGRAM_DATA_SIZE, "Event: failed to set data: size > " + std::to_string(DATAGRAM_DATA_SIZE) +" bytes"); 
    memcpy(data,d,size);
}
void Event::clear_data(){
    memset(data,0,DATAGRAM_DATA_SIZE);
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
    //Host res;
    //res.ip = sf::IpAddress(i);
    //res.port = i>>48;
    return Host(sf::IpAddress(i),i>>48);
}