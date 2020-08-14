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
    Request r(protocol::RequestCode::Connect);
    send(&r,sizeof(r));
    socket.setBlocking(true);
    Info("Client: waiting for response");

    Response response;
    std::size_t size;
    if (socket.receive(&response, sizeof(Response), size, server.ip, server.port) == sf::Socket::Status::Done) {
        Info("Client: socket returned success");
    }
    else {
        Warning("Client: socket returned fail");
    }

    if(response.code.response == protocol::ResponseCode::Success){
        Info("Client: connected to " + server.to_string());
        m_is_connected = true;
        socket.setBlocking(false);
    }else{
        Info("Client: " + std::to_string(response.type) + " " + std::to_string(response.code.response));
        server.ip = sf::IpAddress(0u);
        server.port = 0;
        Warning("Client: operation failed");
    }

}
void Client::send(const void *data, std::size_t size){
    ASSERT_WARRNING(server.port,"Network: can't send an datagram, no connection to the server");
    if(socket.send(data,size,server.ip,server.port)!=sf::Socket::Status::Done)
        Info("Client: can't send a Datagram");
}

bool Client::is_connected(){
    return m_is_connected;
}

void Client::disconnect(){
    Info("Client: disconnecting from " + server.to_string() + " server");
    Request r(protocol::RequestCode::Disconnect);
    send(&r,sizeof(r));
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
