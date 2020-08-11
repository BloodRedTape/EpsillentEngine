#ifndef SERVER_H
#define SERVER_H

#include <unordered_map>
#include <functional>
#include "SFML/Network/UdpSocket.hpp"
#include "core/net/protocol.hpp"
#include "utils/debug.hpp"

#define ServerHandler(function_pointer) std::bind(function_pointer,this,std::placeholders::_1,std::placeholders::_2)
//if you want for something to happen when client connected or disconnected
//you should do it in ClientData constructor
template <typename ClientData>
class Server{
public:
    struct ClientTraits{
        const Host  host;
        ClientData  data;
        ClientTraits(const Host &h):
            host(h)
        {}
    };
    using Handler = std::function<void(const Event &, ClientTraits &)>;

private:
    sf::UdpSocket m_socket_in;
    std::unordered_map<sf::Uint64,ClientTraits> m_clients;
    std::unordered_map<protocol::EventCode,Handler> m_event_dispatch_table;
public:
    Server(sf::Uint16 port);


    void send(const Host& client, const Datagram &d);
    void send(const Host& client, const Event &e);
    void send(const Host& client, const Response &r);

    void serve();

    void event_handler_add(protocol::EventCode code, Handler func);
private:
    void process(const Datagram &datagram, const Host &host);

    void handle_request(const Request &request, const Host &host);
    void handle_event(const Event &event, const Host &host);

    void connect(const Host &host);
    void disconnect(const Host &host);

};


template <typename ClientData>
Server<ClientData>::Server(sf::Uint16 port)
{
    if(m_socket_in.bind(port)==sf::Socket::Status::Error)
        Error("Server: can't bind to port " + std::to_string(port));
    Info("Server: trying to bind to :" + std::to_string(port));
    //Info("Server: working on :" + std::to_string(m_socket_in.getLocalPort()));
    m_socket_in.setBlocking(false);
}


template <typename ClientData>
_ALWAYS_INLINE_ void Server<ClientData>::send(const Host& client, const Datagram &d){
    if(m_socket_in.send(&d,sizeof(Datagram),client.ip,client.port)!=sf::Socket::Done)
        Info("Server: can't send to " + client.ip.toString()+":"+std::to_string(client.port));
}

template <typename ClientData>
_ALWAYS_INLINE_ void Server<ClientData>::send(const Host& client, const Response &r){
    if(m_socket_in.send(&r,sizeof(Response),client.ip,client.port)!=sf::Socket::Done)
        Info("Server: can't send to " + client.ip.toString()+":"+std::to_string(client.port));
}
template <typename ClientData>
_ALWAYS_INLINE_ void Server<ClientData>::send(const Host& client, const Event &e){
    if(m_socket_in.send(&e,sizeof(Event),client.ip,client.port)!=sf::Socket::Done)
        Info("Server: can't send to " + client.ip.toString()+":"+std::to_string(client.port));
}

template <typename ClientData>
void Server<ClientData>::serve(){
    Datagram datagram;
    Host source;
    size_t resived_size;
    m_socket_in.setBlocking(true);
    for(;;){
        m_socket_in.receive(&datagram,sizeof(Datagram),resived_size,source.ip,source.port);
        process(datagram,source);
        datagram.clear();
    }
}
template <typename ClientData>
void Server<ClientData>::event_handler_add(protocol::EventCode code, Handler func){
    m_event_dispatch_table.emplace(code,func);
}



template <typename ClientData>
void Server<ClientData>::process(const Datagram &datagram, const Host &host){
    switch (datagram.type)
    {
    case protocol::DatagramType::Request:
        handle_request(Request(datagram.code.request),host);
        break;
    case protocol::DatagramType::Event:
        handle_event(Event(datagram),host);
        break;
    default:
        Info("Server: Wrong Datagram from " + host.to_string());
        break;
    }
}

template <typename ClientData>
void Server<ClientData>::handle_request(const Request &request, const Host &host){
    switch (request.code.request)
    {
    case protocol::RequestCode::Connect:
        connect(host);
        break;
    case protocol::RequestCode::Disconnect:
        disconnect(host);
        break;
    default:
        Info("Server: Wrong Request from " + host.to_string());   
        break;
    }
}

template <typename ClientData>
void Server<ClientData>::handle_event(const Event &event, const Host &host){
    auto handler = m_event_dispatch_table.find(event.code.event);
    if(handler != m_event_dispatch_table.end()){
        auto &client = m_clients.find(htoi(host))->second;
        handler->second(event,client);
    }else{
        Info("Server: no dispatcher for event code " + std::to_string(event.code.event));
    }
}


template <typename ClientData>
_ALWAYS_INLINE_ void Server<ClientData>::connect(const Host &host){
    Info("Server: Connect request form " + host.to_string());
    m_clients.emplace(htoi(host),host); //implicit conversion of host to client traits to avoid messy object creation

    send(host,Response(protocol::ResponseCode::Success));
    Info("Server: " + host.to_string() + " connected");
    Info("Server: " + std::to_string(m_clients.size()) + " connections");
}
template <typename ClientData>
_ALWAYS_INLINE_ void Server<ClientData>::disconnect(const Host &host){
    Info("Server: Disconnect request form " + host.to_string());

    typename std::unordered_map<sf::Uint64,ClientTraits>::iterator itr = m_clients.find(htoi(host));
    if(itr == m_clients.end()){
        Info("Server: " + host.to_string() + " was not connected");
        return;
    }
    m_clients.erase(htoi(host));
    send(host,Response(protocol::ResponseCode::Success));
    Info("Server: " + host.to_string() + " disconnected");
    Info("Server: " + std::to_string(m_clients.size()) + " connections");
}

#endif