#ifndef SERVER_H
#define SERVER_H

#include <unordered_map>
#include "SFML/Network/UdpSocket.hpp"
#include "network/protocol.hpp"
#include "utils/debug.hpp"


struct NetworkEventComplete{
    NetworkEvent event;
    Host host;
};


template <typename ClientTraits, typename Derived>
class Server{
public:
    using ServerHandler = void (Server::*)(const NetworkEventComplete &e);
    using DerivedHandler = void (Derived::*)(const NetworkEvent &e, ClientTraits &sender);
private:
    sf::UdpSocket socket_in;
    std::unordered_map<sf::Uint64,ClientTraits> clients;
    std::unordered_map<EngineProtocolCode,ServerHandler> server_dispatch;
    std::unordered_map<EngineProtocolCode,DerivedHandler> derived_dispatch;
public:
    Server(sf::Uint16 port);

    void handle_event(const NetworkEventComplete &e);
    void send(const Host& client, const NetworkEvent &e);
    void exclusive_send(const Host& exception, const NetworkEvent &e);
    void serve();

    void add_handler(EngineProtocolCode code, DerivedHandler func);
private:
    void setup_table();
    void connect(const NetworkEventComplete &e);
    void disconnect(const NetworkEventComplete &e);

};


template <typename ClientTraits, typename Derived>
Server<ClientTraits,Derived>::Server(sf::Uint16 port):
    clients()
{
    setup_table();

    if(socket_in.bind(port)==sf::Socket::Status::Error)
        Error("Server: can't bind to port " + std::to_string(port));
    Info("Server: trying to bind to :" + std::to_string(port));
    //Info("Server: working on :" + std::to_string(socket_in.getLocalPort()));
    socket_in.setBlocking(false);
}

template <typename ClientTraits, typename Derived>
void Server<ClientTraits,Derived>::handle_event(const NetworkEventComplete &e){
    sf::Clock c;
    auto sd_itr = server_dispatch.find((EngineProtocolCode)e.event.code);
    if(sd_itr!=server_dispatch.end()){
        (this->*sd_itr->second)(e);
    }else{
        auto dd_itr = derived_dispatch.find((EngineProtocolCode)e.event.code);
        if(dd_itr!=derived_dispatch.end()){
            auto &client_traits = clients.find(htoi(e.host))->second;
            (static_cast<Derived*>(this)->*dd_itr->second)(e.event,client_traits);
        }else{
            Info("Server: Unknown operation");
        }
    }
}

template <typename ClientTraits, typename Derived>
void Server<ClientTraits,Derived>::send(const Host& client, const NetworkEvent &e){
    if(socket_in.send(&e,sizeof(e),client.ip,client.port)!=sf::Socket::Done)
        Info("Server: can't send to " + client.ip.toString()+":"+std::to_string(client.port));
}

template <typename ClientTraits, typename Derived>
void Server<ClientTraits,Derived>::serve(){
    NetworkEventComplete e;
    size_t resived_size;
    socket_in.setBlocking(true);
    for(;;){
        socket_in.receive(&e.event,sizeof(e.event),resived_size,e.host.ip,e.host.port);
        handle_event(e);
        e.event.clear();
    }
}

template <typename ClientTraits, typename Derived>
void Server<ClientTraits,Derived>::add_handler(EngineProtocolCode code, DerivedHandler func){
    derived_dispatch.insert(std::pair<EngineProtocolCode,DerivedHandler>(code,func));
}

template <typename ClientTraits, typename Derived>
void Server<ClientTraits,Derived>::connect(const NetworkEventComplete &e){
    NetworkEvent event;
    if(clients.find(htoi(e.host))!=clients.end()){
        Info("Server: client " + e.host.to_string() +" is already connected");
        event.code = EngineProtocolCode::Fail;
        send(e.host,event);
    }else{
        clients.insert(std::pair<sf::Uint64,ClientTraits>(htoi(e.host),ClientTraits()));
        Info("Server: client " + e.host.to_string() + " connected");
        Info("ClientsCount: " + std::to_string(clients.size()));
        event.code = EngineProtocolCode::Success;
        send(e.host,event);
    }
}
template <typename ClientTraits, typename Derived>
void Server<ClientTraits,Derived>::disconnect(const NetworkEventComplete &e){
    NetworkEvent event;
    if(clients.find(htoi(e.host))==clients.end()){
        Info("Server: client " + e.host.to_string() +" is not connected");
        event.code = EngineProtocolCode::Fail;
        send(e.host,event);
    }else{
        clients.erase(htoi(e.host));
        Info("Server: client " + e.host.to_string() + " disconnected");
        Info("ClientsCount: " + std::to_string(clients.size()));
        event.code = EngineProtocolCode::Success;
        send(e.host,event);
    }
}
template <typename ClientTraits, typename Derived>
void Server<ClientTraits,Derived>::setup_table(){
    server_dispatch.insert(std::pair<EngineProtocolCode,ServerHandler>(EngineProtocolCode::Connect,&Server::connect));
    server_dispatch.insert(std::pair<EngineProtocolCode,ServerHandler>(EngineProtocolCode::Disconnect,&Server::disconnect));
    Info("Server: server dispatch table setted up");
}
#endif