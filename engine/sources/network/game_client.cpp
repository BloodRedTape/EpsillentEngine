#include "network/game_client.hpp"
#include "network/network.hpp"
#include "network/objects_protocol.hpp"
#include "string.h"

GameClient::GameClient(){

}
GameClient::~GameClient(){
    if(m_is_connected){
        for(auto o: objects)
            o.second->destroy();
        disconnect();
    }
}

void GameClient::on_update(){
    Event event(EventCode(0));
    Host host;
    std::size_t size;
    if(socket.receive(&event,sizeof(Event),size,host.ip,host.port)==sf::Socket::Done){
        on_event(event);
    }
}
void GameClient::on_event(const Event &e){
    Info("Network: Event: " + std::to_string(e.code.event));
}

void GameClient::obj_create(NetworkObject *object){
    Event e(EventCode(Events::ObjectNew));
    *((GUID*)e.data) = object->m_guid;
    std::string name = object->network_class();
    memcpy(&e.data[16],name.c_str(),name.size()+1);
    Info("Network: new object " + name + " size " + std::to_string(name.size()));
    ASSERT_ERROR((name.size() + 1 + 16)<DATAGRAM_DATA_SIZE,"NetworkObject: has too big name");
    Network::event(e);
    objects.emplace(object->m_guid,object);
}
void GameClient::obj_destory(NetworkObject *object){
    if(object->originator){
        Event e(EventCode(Events::ObjectDel));
        *((GUID*)e.data) = object->m_guid;
        Network::event(e);
    }
    std::string name = object->network_class();
    Info("Network: deleted object " + name + " size " + std::to_string(name.size()));
    objects.erase(object->m_guid);
}