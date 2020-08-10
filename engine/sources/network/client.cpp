#include "network/client.hpp"
#include "utils/debug.hpp"

Client::Client():
    server()
{

}

void Client::connect(const Host &serv){
    if(server.port)
        disconnect();
    
    NetworkEvent e;
    e.code = EngineProtocolCode::Connect;

    Info("Network: connecting to " + serv.ip.toString() + ":" +std::to_string(serv.port));

    if(socket.send(&e,sizeof(e),serv.ip,serv.port)!=sf::Socket::Done)
        Warning("Network: can't send connection request to " + serv.ip.toString() + ":" + std::to_string(serv.port));
    e.clear();
    socket.setBlocking(true);
    
    size_t size;
    socket.receive(&e,sizeof(e),size,server.ip,server.port);

    if(e.code == EngineProtocolCode::Success){
        Info("Network: Connected to the server");
        server.ip = serv.ip;
        server.port = serv.port;
    }else if(e.code == EngineProtocolCode::Fail){
        Warning("Network: Server denied");
    }else{
        Warning("Network: Unknown server response");
    }
}
void Client::send(const NetworkEvent &e){
    ASSERT_WARRNING(server.port,"Network: can't send an event, no connection to the server");
    if(socket.send(&e,sizeof(e),server.ip,server.port)!= sf::Socket::Done)
        Info("Network: can't send to " + server.ip.toString() + ":" + std::to_string(server.port));
}

void Client::disconnect(){
    if(!server.port)
        Info("Network: trying to disconnect from server without being connected");
    NetworkEvent e;
    e.code = EngineProtocolCode::Disconnect;
    socket.send(&e,sizeof(e),server.ip,server.port);
    
    e.clear();
    socket.setBlocking(true);
    
    size_t size;
    socket.receive(&e,sizeof(e),size,server.ip,server.port);

    if(e.code == EngineProtocolCode::Success){
        Info("Network: Disconnected from the server");
    }else if(e.code == EngineProtocolCode::Fail){
        Warning("Network: Server denied");
    }else{
        Warning("Network: Unknown server response");
    }
}
