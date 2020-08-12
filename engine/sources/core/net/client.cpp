#include "core/net/client.hpp"
#include "utils/debug.hpp"

Client::Client():
    server(),
    m_is_connected(false)
{

}

void Client::connect(const Host &serv){
    if(m_is_connected)
        disconnect();
    Info("Client: connecting to " + serv.to_string() + " server");

    server = serv;
    send(Request(protocol::RequestCode::Connect));
    socket.setBlocking(true);
    Info("Client: waiting for response");

    Response response;
    std::size_t size;
    socket.receive(&response,sizeof(Response),size,server.ip,server.port);

    if(response.code.response == protocol::ResponseCode::Success){
        Info("Client: connected to " + server.to_string());
        m_is_connected = true;
        socket.setBlocking(false);
    }else{
        server.ip = sf::IpAddress(0u);
        server.port = 0;
        Warning("Client: operation failed");
    }

}
void Client::send(const Datagram &datagram){
    ASSERT_WARRNING(server.port,"Network: can't send an event, no connection to the server");
    if(socket.send(&datagram,sizeof(Datagram),server.ip,server.port)!=sf::Socket::Status::Done)
        Info("Client: can't send a Datagram");
}

void Client::send(const Event &event){
    ASSERT_WARRNING(server.port,"Network: can't send an event, no connection to the server");
    if(socket.send(&event,sizeof(Event),server.ip,server.port)!=sf::Socket::Status::Done)
        Info("Client: can't send a Event");
}

void Client::send(const Request &request){
    ASSERT_WARRNING(server.port,"Network: can't send an event, no connection to the server");
    if(socket.send(&request,sizeof(Request),server.ip,server.port)!=sf::Socket::Status::Done)
        Info("Client: can't send a Request");
}

bool Client::is_connected(){
    return m_is_connected;
}

void Client::disconnect(){
    Info("Client: disconnecting from " + server.to_string() + " server");
    send(Request(protocol::RequestCode::Disconnect));
    socket.setBlocking(true);
    Info("Client: waiting for response");

    Response response;
    std::size_t size;
    socket.receive(&response,sizeof(Response),size,server.ip,server.port);

    if(response.code.response == protocol::ResponseCode::Success){
        Info("Client: disconnected from " + server.to_string());
        m_is_connected = false;
    }else{
        Warning("Client: operation failed");
        disconnect();
    }

    server.port = 0;
    server.ip = sf::IpAddress(0u);
}
