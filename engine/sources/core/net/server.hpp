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
    virtual ~Server() = default;

    std::size_t clients();

    void send(const Host& client,const void *data, std::size_t size);

    virtual void on_connect(ClientTraits &){};
    virtual void on_disconnect(ClientTraits &){};

    void serve();

    void event_handler_add(protocol::EventCode code, Handler func);

    void send_all(const void *data, std::size_t size);

    void send_except(const void *data, std::size_t size, const Host &exception);
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
    if(m_socket_in.bind(port)!=sf::Socket::Status::Done)
        Error("Server: can't bind to port " + std::to_string(port));
    Info("Server: trying to bind to :" + std::to_string(port));
    //Info("Server: working on :" + std::to_string(m_socket_in.getLocalPort()));
    m_socket_in.setBlocking(false);
}

template <typename ClientData>
_ALWAYS_INLINE_ std::size_t Server<ClientData>::clients(){
    return m_clients.size();
}

template <typename ClientData>
_ALWAYS_INLINE_ void Server<ClientData>::send(const Host& client,const void *data, std::size_t size){
    if(m_socket_in.send(data,size,client.ip,client.port)!=sf::Socket::Done)
        Info("Server: can't send to " + client.to_string());
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
void Server<ClientData>::send_all(const void *data, std::size_t size){
    for(auto &c : m_clients){
        send(c.second.host,data,size);
    }
}

template <typename ClientData>
void Server<ClientData>::send_except(const void *data, std::size_t size, const Host &exception){
    for(auto &c : m_clients){
        if(c.second.host!=exception){
            send(c.second.host,data,size);
        }
    }
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
    Response r;
    r.type = protocol::DatagramType::Response;
    r.code.response = protocol::ResponseCode::Success;
    send(host,&r,sizeof(Response));
    on_connect(m_clients.emplace(htoi(host),host).first->second); //implicit conversion of host to client traits to avoid messy object creation

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
    Response r;
    r.type = protocol::DatagramType::Response;
    r.code.response = protocol::ResponseCode::Success;
    send(host,&r,sizeof(Response));
    on_disconnect(m_clients.find(htoi(host))->second);
    m_clients.erase(htoi(host));
    Info("Server: " + host.to_string() + " disconnected");
    Info("Server: " + std::to_string(m_clients.size()) + " connections");
}

#endif